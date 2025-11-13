/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/webui/chrome_web_ui_configs.h"

#include "qorai/browser/ui/webui/ai_chat/ai_chat_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_page_ui.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_education/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "content/public/browser/webui_config_map.h"

#define RegisterChromeWebUIConfigs RegisterChromeWebUIConfigs_ChromiumImpl

#include <chrome/browser/ui/webui/chrome_web_ui_configs.cc>
#undef RegisterChromeWebUIConfigs

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_desktop.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_page_top_ui.h"
#include "qorai/browser/ui/webui/qorai_settings_ui.h"
#include "qorai/browser/ui/webui/qorai_shields/shields_panel_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_panel_ui.h"
#include "qorai/browser/ui/webui/private_new_tab_page/qorai_private_new_tab_ui.h"
#include "qorai/browser/ui/webui/webcompat_reporter/webcompat_reporter_ui.h"
#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/ui/webui/speedreader/speedreader_toolbar_ui.h"
#endif

#else  // !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_android.h"
#include "qorai/browser/ui/webui/new_tab_takeover/android/new_tab_takeover_ui_config.h"
#endif  // !BUILDFLAG(IS_ANDROID)

#include "qorai/browser/ui/webui/qorai_adblock_internals_ui.h"
#include "qorai/browser/ui/webui/qorai_adblock_ui.h"

#if BUILDFLAG(ENABLE_QORAI_EDUCATION)
#include "qorai/browser/ui/webui/qorai_education/qorai_education_page_ui.h"
#endif

namespace {

#if !BUILDFLAG(IS_ANDROID)
const GURL GetWebUIConfigURL(const char* scheme, const char* host) {
  return GURL(base::StrCat({scheme, url::kStandardSchemeSeparator, host}));
}
#endif  // !BUILDFLAG(IS_ANDROID)

void RemoveOverridenWebUIs(content::WebUIConfigMap& map) {
#if !BUILDFLAG(IS_ANDROID)
  // Remove NewTabUIConfig. It will be replaced with QoraiPrivateNewTabUIConfig.
  // Note that this only handles new tab for private profiles (Private, Tor,
  // Guest). For regular profile the handling is still done in
  // QoraiWebUIControllerFactory. We will need to follow up on transitioning
  // QoraiNewTabUI to using WebUIConfig. Currently, we can't add both
  // QoraiPrivateNewTabUI and QoraiNewTabUI configs to the map because they
  // use the same origin (content::kChromeUIScheme +
  // chrome::kChromeUINewTabHost).
  map.RemoveConfig(
      GetWebUIConfigURL(content::kChromeUIScheme, chrome::kChromeUINewTabHost));
  // Remove SettingsUIConfig. It will be replaced with QoraiSettingsUIConfig.
  map.RemoveConfig(GetWebUIConfigURL(content::kChromeUIScheme,
                                     chrome::kChromeUISettingsHost));
#endif  // !BUILDFLAG(IS_ANDROID)
}

}  // namespace

void RegisterChromeWebUIConfigs() {
  RegisterChromeWebUIConfigs_ChromiumImpl();

  auto& map = content::WebUIConfigMap::GetInstance();
  // Remove configs for Chromium WebUIs that we replace with our own WebUIs.
  // The map doesn't allow for multiple entries for the same origin, so the
  // upstream configs must be removed before we can add our own configs.
  RemoveOverridenWebUIs(map);

#if !BUILDFLAG(IS_ANDROID)
  map.AddWebUIConfig(std::make_unique<qorai_rewards::RewardsPageTopUIConfig>());
  map.AddWebUIConfig(std::make_unique<QoraiPrivateNewTabUIConfig>());
  map.AddWebUIConfig(std::make_unique<QoraiSettingsUIConfig>());
  map.AddWebUIConfig(std::make_unique<ShieldsPanelUIConfig>());
#if BUILDFLAG(ENABLE_SPEEDREADER)
  map.AddWebUIConfig(std::make_unique<SpeedreaderToolbarUIConfig>());
#endif
  map.AddWebUIConfig(std::make_unique<WalletPageUIConfig>());
  map.AddWebUIConfig(std::make_unique<WalletPanelUIConfig>());
  map.AddWebUIConfig(
      std::make_unique<webcompat_reporter::WebcompatReporterUIConfig>());
  if (qorai_account::features::IsQoraiAccountEnabled()) {
    map.AddWebUIConfig(std::make_unique<QoraiAccountUIDesktopConfig>());
  }
#else   // !BUILDFLAG(IS_ANDROID)
  map.AddWebUIConfig(std::make_unique<NewTabTakeoverUIConfig>());
  if (qorai_account::features::IsQoraiAccountEnabled()) {
    map.AddWebUIConfig(std::make_unique<QoraiAccountUIAndroidConfig>());
  }
#endif  // !BUILDFLAG(IS_ANDROID)
  map.AddWebUIConfig(std::make_unique<QoraiAdblockUIConfig>());
  map.AddWebUIConfig(std::make_unique<QoraiAdblockInternalsUIConfig>());

  if (ai_chat::features::IsAIChatEnabled()) {
    map.AddWebUIConfig(std::make_unique<AIChatUIConfig>());
  }

#if BUILDFLAG(ENABLE_QORAI_EDUCATION)
  map.AddWebUIConfig(std::make_unique<QoraiEducationPageUIConfig>());
#endif
}
