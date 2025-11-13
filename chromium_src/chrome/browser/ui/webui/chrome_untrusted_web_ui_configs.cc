/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/webui/chrome_untrusted_web_ui_configs.h"

#include "base/feature_list.h"
#include "qorai/browser/ui/webui/ai_chat/ai_chat_untrusted_conversation_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/ledger/ledger_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/line_chart/line_chart_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/market/market_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/nft/nft_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/trezor/trezor_ui.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/playlist/core/common/buildflags/buildflags.h"
#include "build/build_config.h"
#include "content/public/browser/webui_config_map.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/webui/qorai_vpn/vpn_panel_ui.h"
#endif  // !BUILDFLAG(IS_ANDROID)
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
#include "qorai/browser/ui/webui/playlist_ui.h"
#include "qorai/components/playlist/core/common/features.h"
#endif

#define RegisterChromeUntrustedWebUIConfigs \
  RegisterChromeUntrustedWebUIConfigs_ChromiumImpl

#include <chrome/browser/ui/webui/chrome_untrusted_web_ui_configs.cc>

#undef RegisterChromeUntrustedWebUIConfigs

void RegisterChromeUntrustedWebUIConfigs() {
  RegisterChromeUntrustedWebUIConfigs_ChromiumImpl();
  content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
      std::make_unique<market::UntrustedMarketUIConfig>());
  content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
      std::make_unique<nft::UntrustedNftUIConfig>());
  content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
      std::make_unique<line_chart::UntrustedLineChartUIConfig>());
#if !BUILDFLAG(IS_ANDROID)
  content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
      std::make_unique<ledger::UntrustedLedgerUIConfig>());
  content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
      std::make_unique<trezor::UntrustedTrezorUIConfig>());
#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (qorai_vpn::IsQoraiVPNFeatureEnabled()) {
    content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
        std::make_unique<UntrustedVPNPanelUIConfig>());
  }
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)
#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
        std::make_unique<playlist::UntrustedPlaylistUIConfig>());
    content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
        std::make_unique<playlist::UntrustedPlaylistPlayerUIConfig>());
  }
#endif  // BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
#endif  // !BUILDFLAG(IS_ANDROID)

  if (ai_chat::features::IsAIChatEnabled()) {
    content::WebUIConfigMap::GetInstance().AddUntrustedWebUIConfig(
        std::make_unique<AIChatUntrustedConversationUIConfig>());
  }
}
