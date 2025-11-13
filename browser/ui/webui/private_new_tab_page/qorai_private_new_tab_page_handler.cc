// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/private_new_tab_page/qorai_private_new_tab_page_handler.h"

#include <utility>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/strings/utf_string_conversions.h"
#include "base/time/time.h"
#include "qorai/components/qorai_private_new_tab_ui/common/pref_names.h"
#include "qorai/components/search_engines/qorai_prepopulated_engines.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/prefs/pref_service.h"
#include "components/search_engines/template_url.h"
#include "components/search_engines/template_url_data_util.h"
#include "components/search_engines/template_url_service.h"
#include "content/public/browser/page_navigator.h"
#include "content/public/browser/web_contents.h"

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/tor/tor_profile_service_factory.h"
#include "qorai/components/tor/pref_names.h"
#include "qorai/components/tor/tor_launcher_factory.h"
#include "chrome/browser/browser_process.h"
#endif

namespace {
constexpr auto kStuckPeriod = base::Seconds(45);
}

QoraiPrivateNewTabPageHandler::QoraiPrivateNewTabPageHandler(
    Profile* profile,
    content::WebContents* web_contents,
    mojo::PendingReceiver<qorai_private_new_tab::mojom::PageHandler> receiver)
    : profile_(profile),
      web_contents_(web_contents),
      receiver_(this, std::move(receiver)) {
#if BUILDFLAG(ENABLE_TOR)
  tor_launcher_factory_ = TorLauncherFactory::GetInstance();
  if (tor_launcher_factory_)
    tor_launcher_factory_->AddObserver(this);
#endif
}

QoraiPrivateNewTabPageHandler::~QoraiPrivateNewTabPageHandler() {
#if BUILDFLAG(ENABLE_TOR)
  if (tor_launcher_factory_)
    tor_launcher_factory_->RemoveObserver(this);
#endif
}

void QoraiPrivateNewTabPageHandler::SetClientPage(
    mojo::PendingRemote<qorai_private_new_tab::mojom::PrivateTabPage> page) {
  page_.Bind(std::move(page));
}

void QoraiPrivateNewTabPageHandler::SetDisclaimerDismissed(bool dismissed) {
  CHECK(profile_);

  profile_->GetOriginalProfile()->GetPrefs()->SetBoolean(
      profile_->IsTor()
          ? qorai_private_new_tab::prefs::kQoraiTorWindowDisclaimerDismissed
          : qorai_private_new_tab::prefs::
                kQoraiPrivateWindowDisclaimerDismissed,
      dismissed);
}

void QoraiPrivateNewTabPageHandler::GetDisclaimerDismissed(
    GetDisclaimerDismissedCallback callback) {
  CHECK(profile_);

  bool dismissed = profile_->GetOriginalProfile()->GetPrefs()->GetBoolean(
      profile_->IsTor()
          ? qorai_private_new_tab::prefs::kQoraiTorWindowDisclaimerDismissed
          : qorai_private_new_tab::prefs::
                kQoraiPrivateWindowDisclaimerDismissed);
  std::move(callback).Run(dismissed);
}

void QoraiPrivateNewTabPageHandler::GetIsTorConnected(
    GetIsTorConnectedCallback callback) {
  bool is_connected = false;
#if BUILDFLAG(ENABLE_TOR)
  if (tor_launcher_factory_)
    is_connected = tor_launcher_factory_->IsTorConnected();
#endif

  std::move(callback).Run(is_connected);
}

void QoraiPrivateNewTabPageHandler::GetIsTorDisabled(
    GetIsTorDisabledCallback callback) {
  CHECK(profile_);
#if BUILDFLAG(ENABLE_TOR)
  // For private new tab page, only check if Tor is explicitly
  // disabled by enterprise policy (managed and set to true)
  bool is_disabled = false;
  if (auto* prefs = g_browser_process->local_state()) {
    auto* pref = prefs->FindPreference(tor::prefs::kTorDisabled);
    is_disabled = pref && pref->IsManaged() && pref->GetValue()->GetBool();
  }
#else
  bool is_disabled = true;
#endif
  std::move(callback).Run(is_disabled);
}

using ConnectionStatus = qorai_private_new_tab::mojom::ConnectionStatus;

void QoraiPrivateNewTabPageHandler::GoToQoraiSearch(const std::string& input,
                                                    bool open_new_tab) {
  CHECK(profile_);

  auto provider_data = TemplateURLDataFromPrepopulatedEngine(
      profile_->IsTor() ? TemplateURLPrepopulateData::qorai_search_tor
                        : TemplateURLPrepopulateData::qorai_search);
  auto t_url = std::make_unique<TemplateURL>(*provider_data);
  SearchTermsData search_terms_data;

  auto url = GURL(t_url->url_ref().ReplaceSearchTerms(
      TemplateURLRef::SearchTermsArgs(base::UTF8ToUTF16(input)),
      search_terms_data));

  auto window_open_disposition = WindowOpenDisposition::CURRENT_TAB;

  if (open_new_tab) {
    window_open_disposition = WindowOpenDisposition::NEW_BACKGROUND_TAB;
  }

  web_contents_->OpenURL(
      content::OpenURLParams(url, content::Referrer(), window_open_disposition,
                             ui::PageTransition::PAGE_TRANSITION_FORM_SUBMIT,
                             false),
      /*navigation_handle_callback=*/{});
}

void QoraiPrivateNewTabPageHandler::GoToQoraiSupport() {
  Profile* profile = profile_;
  if (profile_->IsTor()) {
    profile = profile_->GetOriginalProfile();
  }

  content::WebContents* web_contents = nullptr;

  Browser* browser = chrome::FindBrowserWithProfile(profile);
  if (browser && browser->tab_strip_model()) {
    web_contents = browser->tab_strip_model()->GetActiveWebContents();
  }

  if (!web_contents)
    web_contents = web_contents_;

  web_contents->OpenURL(
      content::OpenURLParams(GURL("https://support.qorai.app/"),
                             content::Referrer(),
                             WindowOpenDisposition::NEW_FOREGROUND_TAB,
                             ui::PageTransition::PAGE_TRANSITION_LINK, false),
      /*navigation_handle_callback=*/{});
}

void QoraiPrivateNewTabPageHandler::OnTorCircuitEstablished(bool result) {
  stuck_timer_.Stop();
  if (page_) {
    page_.get()->OnTorCircuitStatus(result
                                        ? ConnectionStatus::kConnected
                                        : ConnectionStatus::kConnectionStuck);
    page_.get()->OnTorCircuitEstablished(result);
  }
}

void QoraiPrivateNewTabPageHandler::OnTorInitializing(
    const std::string& percentage,
    const std::string& message) {
  stuck_timer_.Start(
      FROM_HERE, kStuckPeriod,
      base::BindOnce(&QoraiPrivateNewTabPageHandler::OnTorCircuitTimer,
                     base::Unretained(this),
                     ConnectionStatus::kConnectionSlow));
  if (page_) {
    page_.get()->OnTorInitializing(percentage, message);
    page_.get()->OnTorCircuitStatus(ConnectionStatus::kConnecting);
  }
}

void QoraiPrivateNewTabPageHandler::OnTorCircuitTimer(ConnectionStatus status) {
  if (!page_)
    return;

  if (status == ConnectionStatus::kConnectionSlow) {
    // First time shot of stuck_timer_  means that 'connection is slow' we
    // take another chance to connect and then notify that we get stuck.
    stuck_timer_.Start(
        FROM_HERE, kStuckPeriod,
        base::BindOnce(&QoraiPrivateNewTabPageHandler::OnTorCircuitTimer,
                       base::Unretained(this),
                       ConnectionStatus::kConnectionStuck));
  }

  page_.get()->OnTorCircuitStatus(status);
}
