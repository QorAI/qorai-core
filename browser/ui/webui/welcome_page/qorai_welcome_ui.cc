/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/welcome_page/qorai_welcome_ui.h"

#include <algorithm>
#include <memory>
#include <string>

#include "base/check.h"
#include "base/feature_list.h"
#include "base/memory/raw_ptr.h"
#include "base/task/single_thread_task_runner.h"
#include "qorai/browser/qorai_browser_features.h"
#include "qorai/browser/ui/webui/qorai_webui_source.h"
#include "qorai/browser/ui/webui/settings/qorai_import_bulk_data_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_search_engines_handler.h"
#include "qorai/browser/ui/webui/welcome_page/qorai_welcome_ui_prefs.h"
#include "qorai/browser/ui/webui/welcome_page/welcome_dom_handler.h"
#include "qorai/components/qorai_welcome/common/features.h"
#include "qorai/components/qorai_welcome/resources/grit/qorai_welcome_generated_map.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/p3a/pref_names.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/regional_capabilities/regional_capabilities_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/webui/settings/privacy_sandbox_handler.h"
#include "chrome/browser/ui/webui/settings/settings_default_browser_handler.h"
#include "chrome/browser/ui/webui/theme_source.h"
#include "chrome/common/pref_names.h"
#include "chrome/grit/branded_strings.h"
#include "components/country_codes/country_codes.h"
#include "components/grit/qorai_components_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "components/metrics/metrics_pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/regional_capabilities/regional_capabilities_prefs.h"
#include "content/public/browser/gpu_data_manager.h"
#include "content/public/browser/page_navigator.h"
#include "content/public/browser/url_data_source.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

constexpr webui::LocalizedString kLocalizedStrings[] = {
    {"headerText", IDS_WELCOME_HEADER},
    {"qoraiWelcomeTitle", IDS_QORAI_WELCOME_TITLE},
    {"qoraiWelcomeDesc", IDS_QORAI_WELCOME_DESC},
    {"qoraiWelcomeImportSettingsTitle",
     IDS_QORAI_WELCOME_IMPORT_SETTINGS_TITLE},
    {"qoraiWelcomeImportSettingsDesc", IDS_QORAI_WELCOME_IMPORT_SETTINGS_DESC},
    {"qoraiWelcomeSelectProfileLabel", IDS_QORAI_WELCOME_SELECT_PROFILE_LABEL},
    {"qoraiWelcomeSelectProfileDesc", IDS_QORAI_WELCOME_SELECT_PROFILE_DESC},
    {"qoraiWelcomeImportButtonLabel", IDS_QORAI_WELCOME_IMPORT_BUTTON_LABEL},
    {"qoraiWelcomeImportProfilesButtonLabel",
     IDS_QORAI_WELCOME_IMPORT_PROFILES_BUTTON_LABEL},
    {"qoraiWelcomeSkipButtonLabel", IDS_QORAI_WELCOME_SKIP_BUTTON_LABEL},
    {"qoraiWelcomeBackButtonLabel", IDS_QORAI_WELCOME_BACK_BUTTON_LABEL},
    {"qoraiWelcomeNextButtonLabel", IDS_QORAI_WELCOME_NEXT_BUTTON_LABEL},
    {"qoraiWelcomeFinishButtonLabel", IDS_QORAI_WELCOME_FINISH_BUTTON_LABEL},
    {"qoraiWelcomeSetDefaultButtonLabel",
     IDS_QORAI_WELCOME_SET_DEFAULT_BUTTON_LABEL},
    {"qoraiWelcomeSelectAllButtonLabel",
     IDS_QORAI_WELCOME_SELECT_ALL_BUTTON_LABEL},
    {"qoraiWelcomeHelpImproveQoraiTitle",
     IDS_QORAI_WELCOME_HELP_IMPROVE_QORAI_TITLE},
    {"qoraiWelcomeSendReportsLabel", IDS_QORAI_WELCOME_SEND_REPORTS_LABEL},
    {"qoraiWelcomeSendInsightsLabel", IDS_QORAI_WELCOME_SEND_INSIGHTS_LABEL},
    {"qoraiWelcomeSetupCompleteLabel", IDS_QORAI_WELCOME_SETUP_COMPLETE_LABEL},
    {"qoraiWelcomeChangeSettingsNote", IDS_QORAI_WELCOME_CHANGE_SETTINGS_NOTE},
    {"qoraiWelcomePrivacyPolicyNote", IDS_QORAI_WELCOME_PRIVACY_POLICY_NOTE},
    {"qoraiWelcomeSelectThemeLabel", IDS_QORAI_WELCOME_SELECT_THEME_LABEL},
    {"qoraiWelcomeSelectThemeNote", IDS_QORAI_WELCOME_SELECT_THEME_NOTE},
    {"qoraiWelcomeSelectThemeSystemLabel",
     IDS_QORAI_WELCOME_SELECT_THEME_SYSTEM_LABEL},
    {"qoraiWelcomeSelectThemeLightLabel",
     IDS_QORAI_WELCOME_SELECT_THEME_LIGHT_LABEL},
    {"qoraiWelcomeSelectThemeDarkLabel",
     IDS_QORAI_WELCOME_SELECT_THEME_DARK_LABEL},
    {"qoraiWelcomeHelpWDPTitle", IDS_QORAI_WELCOME_HELP_WDP_TITLE},
    {"qoraiWelcomeHelpWDPSubtitle", IDS_QORAI_WELCOME_HELP_WDP_SUBTITLE},
    {"qoraiWelcomeHelpWDPDescription", IDS_QORAI_WELCOME_HELP_WDP_DESCRIPTION},
    {"qoraiWelcomeHelpWDPLearnMore", IDS_QORAI_WELCOME_HELP_WDP_LEARN_MORE},
    {"qoraiWelcomeHelpWDPAccept", IDS_QORAI_WELCOME_HELP_WDP_ACCEPT},
    {"qoraiWelcomeHelpWDPReject", IDS_QORAI_WELCOME_HELP_WDP_REJECT}};

void OpenJapanWelcomePage(Profile* profile) {
  CHECK(profile);
  Browser* browser = chrome::FindBrowserWithProfile(profile);
  if (browser) {
    content::OpenURLParams open_params(
        GURL("https://qorai.com/ja/desktop-ntp-tutorial"), content::Referrer(),
        WindowOpenDisposition::NEW_BACKGROUND_TAB,
        ui::PAGE_TRANSITION_AUTO_TOPLEVEL, false);
    browser->OpenURL(open_params, /*navigation_handle_callback=*/{});
  }
}

}  // namespace

QoraiWelcomeUI::QoraiWelcomeUI(content::WebUI* web_ui, const std::string& name)
    : WebUIController(web_ui) {
  content::WebUIDataSource* source = CreateAndAddWebUIDataSource(
      web_ui, name, kQoraiWelcomeGenerated, IDR_QORAI_WELCOME_HTML,
      /*disable_trusted_types_csp=*/true);

  // Lottie animations tick on a worker thread and requires the document CSP to
  // be set to "worker-src blob: 'self';".
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::WorkerSrc,
      "worker-src blob: chrome://resources 'self';");

  web_ui->AddMessageHandler(
      std::make_unique<WelcomeDOMHandler>(Profile::FromWebUI(web_ui)));
  web_ui->AddMessageHandler(
      std::make_unique<settings::QoraiImportBulkDataHandler>());
  web_ui->AddMessageHandler(
      std::make_unique<settings::DefaultBrowserHandler>());  // set default
                                                             // browser

  Profile* profile = Profile::FromWebUI(web_ui);
  CHECK(profile);
  // added to allow front end to read/modify default search engine
  web_ui->AddMessageHandler(std::make_unique<
                            settings::QoraiSearchEnginesHandler>(
      profile,
      regional_capabilities::RegionalCapabilitiesServiceFactory::GetForProfile(
          profile)));

  // Open additional page in Japanese region
  country_codes::CountryId country_id =
      country_codes::CountryId::Deserialize(profile->GetPrefs()->GetInteger(
          regional_capabilities::prefs::kCountryIDAtInstall));
  const bool is_jpn = country_id == country_codes::CountryId("JP");
  if (!profile->GetPrefs()->GetBoolean(
          qorai::welcome_ui::prefs::kHasSeenQoraiWelcomePage)) {
    if (is_jpn) {
      base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
          FROM_HERE, base::BindOnce(&OpenJapanWelcomePage, profile),
          base::Seconds(3));
    }
  }

  for (const auto& str : kLocalizedStrings) {
    std::u16string l10n_str = l10n_util::GetStringUTF16(str.id);
    source->AddString(str.name, l10n_str);
  }

  // Variables considered when determining which onboarding cards to show
  source->AddString("countryString", country_id.CountryCode());
  source->AddBoolean(
      "showRewardsCard",
      base::FeatureList::IsEnabled(qorai_welcome::features::kShowRewardsCard));

  source->AddBoolean(
      "hardwareAccelerationEnabledAtStartup",
      content::GpuDataManager::GetInstance()->HardwareAccelerationEnabled());

  // Add managed state information for welcome flow logic
  PrefService* local_state = g_browser_process->local_state();
  source->AddBoolean(
      "isWebDiscoveryEnabledManaged",
#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
      profile->GetPrefs()->IsManagedPreference(kWebDiscoveryEnabled));
#else
      false);
#endif
  source->AddBoolean("isMetricsReportingEnabledManaged",
                     local_state->IsManagedPreference(
                         metrics::prefs::kMetricsReportingEnabled));
  source->AddBoolean("isP3AEnabledManaged",
                     local_state->IsManagedPreference(p3a::kP3AEnabled));

  profile->GetPrefs()->SetBoolean(
      qorai::welcome_ui::prefs::kHasSeenQoraiWelcomePage, true);

  AddBackgroundColorToSource(source, web_ui->GetWebContents());

  content::URLDataSource::Add(profile,
                              std::make_unique<ThemeSource>(profile, true));
}

QoraiWelcomeUI::~QoraiWelcomeUI() = default;
