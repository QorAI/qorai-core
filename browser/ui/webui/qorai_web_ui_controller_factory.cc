/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_web_ui_controller_factory.h"

#include <memory>
#include <string>

#include "base/check.h"
#include "base/feature_list.h"
#include "base/memory/ptr_util.h"
#include "base/no_destructor.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_browser_features.h"
#include "qorai/browser/qorai_news/qorai_news_controller_factory.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/ntp_background/view_counter_service_factory.h"
#include "qorai/browser/ui/webui/ads_internals/ads_internals_ui.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_page_ui.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_web_ui_utils.h"
#include "qorai/browser/ui/webui/qorai_rewards_internals_ui.h"
#include "qorai/browser/ui/webui/skus_internals_ui.h"
#include "qorai/components/ai_chat/core/common/buildflags/buildflags.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/ai_rewriter/common/buildflags/buildflags.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/playlist/core/common/buildflags/buildflags.h"
#include "qorai/components/skus/common/features.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/url_constants.h"
#include "components/optimization_guide/core/optimization_guide_features.h"
#include "components/optimization_guide/optimization_guide_internals/webui/url_constants.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/url_utils.h"
#include "url/gurl.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/qorai_new_tab_page_ui.h"
#include "qorai/browser/ui/webui/qorai_news_internals/qorai_news_internals_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_page_ui.h"
#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_ui.h"
#include "qorai/browser/ui/webui/welcome_page/qorai_welcome_ui.h"
#include "qorai/components/qorai_news/common/features.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/commands/common/features.h"
#include "chrome/browser/regional_capabilities/regional_capabilities_service_factory.h"
#endif

#if BUILDFLAG(IS_ANDROID)
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/ui/webui/qorai_wallet/android/android_wallet_page_ui.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#endif

#include "qorai/browser/qorai_vpn/vpn_utils.h"

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
#include "qorai/browser/ui/webui/playlist_ui.h"
#include "qorai/components/playlist/core/common/features.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/ui/webui/tor_internals_ui.h"
#endif

#if BUILDFLAG(ENABLE_AI_REWRITER)
#include "qorai/browser/ui/webui/ai_rewriter/ai_rewriter_ui.h"
#include "qorai/components/ai_rewriter/common/features.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
#include "qorai/browser/ui/webui/ai_chat/ai_chat_agent_new_tab_page_ui.h"
#endif

using content::WebUI;
using content::WebUIController;

namespace {

// A function for creating a new WebUI. The caller owns the return value, which
// may be NULL (for example, if the URL refers to an non-existent extension).
typedef WebUIController* (*WebUIFactoryFunction)(WebUI* web_ui,
                                                 const GURL& url);

WebUIController* NewWebUI(WebUI* web_ui, const GURL& url) {
  auto host = url.host_piece();
  Profile* profile = Profile::FromBrowserContext(
      web_ui->GetWebContents()->GetBrowserContext());
  CHECK(profile);
  if (host == kAdsInternalsHost) {
    return new AdsInternalsUI(
        web_ui, url.host(),
        qorai_ads::AdsServiceFactory::GetForProfile(profile),
        *profile->GetPrefs());
  } else if (host == kSkusInternalsHost) {
    return new SkusInternalsUI(web_ui, url.host());
  } else if (host == kRewardsPageHost &&
             // We don't want to check for supported profile type here because
             // we want private windows to redirect to the regular profile.
             // Additionally, if Rewards aren't supported because of the OFAC
             // sanctions we want to show the page with an appropriate error
             // message.
             // Guest session will just show an error page.
             qorai_rewards::IsSupported(
                 profile->GetPrefs(),
                 qorai_rewards::IsSupportedOptions::kSkipRegionCheck)) {
    return new qorai_rewards::RewardsPageUI(web_ui, url.host());
  } else if (host == kRewardsInternalsHost &&
             qorai_rewards::IsSupportedForProfile(profile)) {
    return new QoraiRewardsInternalsUI(web_ui, url.host());
#if !BUILDFLAG(IS_ANDROID)
  } else if (base::FeatureList::IsEnabled(
                 qorai_news::features::kQoraiNewsFeedUpdate) &&
             host == kQoraiNewsInternalsHost) {
    return new QoraiNewsInternalsUI(
        web_ui, url.host(),
        qorai_news::QoraiNewsControllerFactory::GetForBrowserContext(profile));
  } else if (host == kWelcomeHost && !profile->IsGuestSession()) {
    return new QoraiWelcomeUI(web_ui, url.host());
  } else if (host == chrome::kChromeUINewTabHost) {
    // For private profiles the webui handling kChromeUINewTabHost is configured
    // with RegisterChromeWebUIConfigs, so we should not get called here with a
    // private profile.
    DCHECK(!profile->IsIncognitoProfile() && !profile->IsTor() &&
           !profile->IsGuestSession());
    // We will need to follow up on transitioning QoraiNewTabUI to using
    // WebUIConfig. Currently, we can't add both QoraiPrivateNewTabUI and
    // QoraiNewTabUI configs in RegisterChromeWebUIConfigs because they use the
    // same origin (content::kChromeUIScheme + chrome::kChromeUINewTabHost).
#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
    if (base::FeatureList::IsEnabled(ai_chat::features::kAIChatAgentProfile) &&
        profile->IsAIChatAgent()) {
      return new AIChatAgentNewTabPageUI(web_ui);
    }
#endif
    if (base::FeatureList::IsEnabled(
            features::kQoraiNewTabPageRefreshEnabled)) {
      return new QoraiNewTabPageUI(web_ui);
    }
    return new QoraiNewTabUI(
        web_ui, url.host(),
        qorai_ads::AdsServiceFactory::GetForProfile(profile),
        ntp_background_images::ViewCounterServiceFactory::GetForProfile(
            profile),
        regional_capabilities::RegionalCapabilitiesServiceFactory::
            GetForProfile(profile));
#endif  // !BUILDFLAG(IS_ANDROID)
#if BUILDFLAG(ENABLE_TOR)
  } else if (host == kTorInternalsHost) {
    return new TorInternalsUI(web_ui, url.host());
#endif
#if BUILDFLAG(IS_ANDROID)
  } else if (url.is_valid() && url.host() == kWalletPageHost) {
    return new AndroidWalletPageUI(web_ui, url);
#endif
#if BUILDFLAG(ENABLE_AI_REWRITER)
  } else if (host == kRewriterUIHost) {
    if (ai_rewriter::features::IsAIRewriterEnabled()) {
      return new ai_rewriter::AIRewriterUI(web_ui);
    }
#endif
  }
  return nullptr;
}

// Returns a function that can be used to create the right type of WebUI for a
// tab, based on its URL. Returns NULL if the URL doesn't have WebUI associated
// with it.
WebUIFactoryFunction GetWebUIFactoryFunction(WebUI* web_ui,
                                             Profile* profile,
                                             const GURL& url) {
  // This will get called a lot to check all URLs, so do a quick check of other
  // schemes to filter out most URLs.
  //
  // This has a narrow scoper scope than content::HasWebUIScheme(url) which also
  // allows both `chrome-untrusted` and `chrome-devtools`.
  if (!url.SchemeIs(content::kQoraiUIScheme) &&
      !url.SchemeIs(content::kChromeUIScheme)) {
    return nullptr;
  }

  if ((url.host_piece() == kSkusInternalsHost &&
       base::FeatureList::IsEnabled(skus::features::kSkusFeature)) ||
#if BUILDFLAG(IS_ANDROID)
      (url.is_valid() && url.host_piece() == kWalletPageHost) ||
#else
      (base::FeatureList::IsEnabled(
           qorai_news::features::kQoraiNewsFeedUpdate) &&
       url.host_piece() == kQoraiNewsInternalsHost) ||
      // On Android New Tab is a native page implemented in Java, so no need
      // in WebUI.
      url.host_piece() == chrome::kChromeUINewTabHost ||
      url.host_piece() == chrome::kChromeUISettingsHost ||
      ((url.host_piece() == kWelcomeHost || url.host_piece() == kWelcomeURL) &&
       !profile->IsGuestSession()) ||
#endif  // BUILDFLAG(IS_ANDROID)
#if BUILDFLAG(ENABLE_TOR)
      url.host_piece() == kTorInternalsHost ||
#endif
#if BUILDFLAG(ENABLE_AI_REWRITER)
      (url.host_piece() == kRewriterUIHost &&
       ai_rewriter::features::IsAIRewriterEnabled()) ||
#endif
      url.host_piece() == kRewardsPageHost ||
      url.host_piece() == kRewardsInternalsHost ||
      (url.host_piece() == kAdsInternalsHost &&
       !profile->IsIncognitoProfile())) {
    return &NewWebUI;
  }

  return nullptr;
}

#if BUILDFLAG(IS_ANDROID)
bool ShouldBlockWalletWebUI(content::BrowserContext* browser_context,
                            const GURL& url) {
  if (!url.is_valid() || url.host() != kWalletPageHost) {
    return false;
  }
  Profile* profile = Profile::FromBrowserContext(browser_context);
  if (!profile) {
    return false;
  }
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(profile);
  if (!qorai_wallet_service) {
    return true;
  }
  // Support to unlock Wallet has been extended also through WebUI,
  // so we block only when Wallet hasn't been created yet, as onboarding
  // is offered only via native Andrioid UI.
  return !qorai_wallet_service->keyring_service()->IsWalletCreatedSync();
}
#endif  // BUILDFLAG(IS_ANDROID)
}  // namespace

WebUI::TypeID QoraiWebUIControllerFactory::GetWebUIType(
    content::BrowserContext* browser_context,
    const GURL& url) {
  if (qorai_rewards::ShouldBlockRewardsWebUI(browser_context, url)) {
    return WebUI::kNoWebUI;
  }
#if BUILDFLAG(IS_ANDROID)
  if (ShouldBlockWalletWebUI(browser_context, url)) {
    return WebUI::kNoWebUI;
  }
#endif  // BUILDFLAG(IS_ANDROID)
#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    if (playlist::PlaylistUI::ShouldBlockPlaylistWebUI(browser_context, url)) {
      return WebUI::kNoWebUI;
    }
  }
#endif

  // Early return to prevent upstream create its WebUI.
  if (url.host_piece() == optimization_guide_internals::
                              kChromeUIOptimizationGuideInternalsHost &&
      !optimization_guide::features::IsOptimizationHintsEnabled()) {
    return WebUI::kNoWebUI;
  }

  Profile* profile = Profile::FromBrowserContext(browser_context);
  WebUIFactoryFunction function =
      GetWebUIFactoryFunction(nullptr, profile, url);
  if (function) {
    return reinterpret_cast<WebUI::TypeID>(function);
  }
  return ChromeWebUIControllerFactory::GetWebUIType(browser_context, url);
}

std::unique_ptr<WebUIController>
QoraiWebUIControllerFactory::CreateWebUIControllerForURL(WebUI* web_ui,
                                                         const GURL& url) {
  Profile* profile = Profile::FromWebUI(web_ui);
  WebUIFactoryFunction function = GetWebUIFactoryFunction(web_ui, profile, url);
  if (!function) {
    return ChromeWebUIControllerFactory::CreateWebUIControllerForURL(web_ui,
                                                                     url);
  }

  return base::WrapUnique((*function)(web_ui, url));
}

// static
QoraiWebUIControllerFactory* QoraiWebUIControllerFactory::GetInstance() {
  static base::NoDestructor<QoraiWebUIControllerFactory> instance;
  return instance.get();
}

QoraiWebUIControllerFactory::QoraiWebUIControllerFactory() = default;

QoraiWebUIControllerFactory::~QoraiWebUIControllerFactory() = default;
