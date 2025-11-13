/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/feature_override.h"
#include "qorai/browser/android/safe_browsing/features.h"
#include "qorai/browser/android/youtube_script_injector/features.h"
#include "qorai/browser/qorai_browser_features.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_feature.h"
#include "qorai/components/qorai_news/common/features.h"
#include "qorai/components/qorai_origin/features.h"
#include "qorai/components/qorai_rewards/core/features.h"
#include "qorai/components/qorai_search_conversion/features.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/debounce/core/common/features.h"
#include "qorai/components/google_sign_in_permission/features.h"
#include "qorai/components/ntp_background_images/browser/features.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/request_otr/common/features.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "qorai/components/webcompat/core/common/features.h"
#include "net/base/features.h"
#include "third_party/blink/public/common/features.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/features.h"
#endif

#define QORAI_AI_CHAT_FLAGS \
  &ai_chat::features::kAIChat, &ai_chat::features::kAIChatHistory,

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
#include "qorai/components/web_discovery/common/features.h"
#define QORAI_WEB_DISCOVERY_FLAG \
  &web_discovery::features::kQoraiWebDiscoveryNative,
#else
#define QORAI_WEB_DISCOVERY_FLAG
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#define QORAI_VPN_FLAG &qorai_vpn::features::kQoraiVPNLinkSubscriptionAndroidUI,
#else
#define QORAI_VPN_FLAG
#endif

// clang-format off
#define kForceWebContentsDarkMode kForceWebContentsDarkMode,                   \
    QORAI_AI_CHAT_FLAGS                                                        \
    QORAI_WEB_DISCOVERY_FLAG                                                   \
    QORAI_VPN_FLAG                                                             \
    &qorai_rewards::features::kQoraiRewards,                                   \
    &qorai_search_conversion::features::kOmniboxBanner,                        \
    &qorai_wallet::features::kNativeQoraiWalletFeature,                        \
    &playlist::features::kPlaylist,                                            \
    &download::features::kParallelDownloading,                                 \
    &preferences::features::kQoraiBackgroundVideoPlayback,                     \
    &preferences::features::kQoraiPictureInPictureForYouTubeVideos,            \
    &request_otr::features::kQoraiRequestOTRTab,                               \
    &safe_browsing::features::kQoraiAndroidSafeBrowsing,                       \
    &debounce::features::kQoraiDebounce,                                       \
    &webcompat::features::kQoraiWebcompatExceptionsService,                    \
    &net::features::kQoraiHttpsByDefault,                                      \
    &net::features::kQoraiFallbackDoHProvider,                                 \
    &google_sign_in_permission::features::kQoraiGoogleSignInPermission,        \
    &net::features::kQoraiForgetFirstPartyStorage,                             \
    &qorai_shields::features::kQoraiShowStrictFingerprintingMode,              \
    &qorai_shields::features::kQoraiLocalhostAccessPermission,                 \
    &qorai_shields::features::kBlockAllCookiesToggle,                          \
    &qorai_shields::features::kQoraiShieldsElementPicker,                      \
    &features::kQoraiAndroidDynamicColors,                                     \
    &features::kNewAndroidOnboarding,                                          \
    &features::kQoraiFreshNtpAfterIdleExpirement,                              \
    &qorai_ads::kNewTabPageAdFeature,                                          \
    &ntp_background_images::features::kQoraiNTPBrandedWallpaperSurveyPanelist, \
    &qorai_account::features::kQoraiAccount,                                   \
    &qorai_origin::features::kQoraiOrigin

// clang-format on

#include <chrome/browser/flags/android/chrome_feature_list.cc>
#undef kForceWebContentsDarkMode
#undef QORAI_AI_CHAT_FLAGS
#undef QORAI_WEB_DISCOVERY_FLAG
#undef QORAI_VPN_FLAG

namespace chrome {
namespace android {

OVERRIDE_FEATURE_DEFAULT_STATES({{
    {kMagicStackAndroid, base::FEATURE_DISABLED_BY_DEFAULT},
    {kAdaptiveButtonInTopToolbarCustomizationV2,
     base::FEATURE_DISABLED_BY_DEFAULT},
    {kClearBrowsingDataAndroidSurvey, base::FEATURE_DISABLED_BY_DEFAULT},
}});

}  // namespace android
}  // namespace chrome
