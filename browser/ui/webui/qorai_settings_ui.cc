/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_settings_ui.h"

#include <memory>
#include <string>
#include <utility>

#include "base/compiler_specific.h"
#include "base/feature_list.h"
#include "qorai/browser/ai_chat/ai_chat_settings_helper.h"
#include "qorai/browser/qorai_origin/qorai_origin_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/browser/email_aliases/email_aliases_service_factory.h"
#include "qorai/browser/resources/settings/grit/qorai_settings_resources.h"
#include "qorai/browser/resources/settings/grit/qorai_settings_resources_map.h"
#include "qorai/browser/shell_integrations/buildflags/buildflags.h"
#include "qorai/browser/ui/commands/accelerator_service_factory.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"
#include "qorai/browser/ui/webui/settings/qorai_account_settings_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_adblock_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_appearance_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_default_extensions_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_privacy_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_settings_qora_assistant_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_sync_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_wallet_handler.h"
#include "qorai/browser/ui/webui/settings/default_qorai_shields_handler.h"
#include "qorai/components/ai_chat/core/browser/customization_settings_handler.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_origin/qorai_origin_handler.h"
#include "qorai/components/qorai_origin/qorai_origin_utils.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/commander/common/features.h"
#include "qorai/components/commands/common/commands.mojom.h"
#include "qorai/components/commands/common/features.h"
#include "qorai/components/email_aliases/email_aliases.mojom.h"
#include "qorai/components/email_aliases/features.h"
#include "qorai/components/ntp_background_images/browser/features.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/playlist/core/common/pref_names.h"
#include "qorai/components/search_engines/qorai_prepopulated_engines.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/version_info/version_info.h"
#include "build/build_config.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/regional_capabilities/regional_capabilities_service_factory.h"
#include "chrome/browser/ui/webui/settings/metrics_reporting_handler.h"
#include "components/regional_capabilities/regional_capabilities_country_id.h"
#include "components/regional_capabilities/regional_capabilities_service.h"
#include "components/sync/base/command_line_switches.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/common/content_features.h"
#include "extensions/buildflags/buildflags.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"
#include "net/base/features.h"

#if BUILDFLAG(ENABLE_PIN_SHORTCUT)
#include "qorai/browser/ui/webui/settings/pin_shortcut_handler.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/common/features.h"
#include "qorai/components/speedreader/speedreader_pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#if BUILDFLAG(IS_WIN)
#include "qorai/browser/ui/webui/settings/qorai_vpn/qorai_vpn_handler.h"
#endif
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
#include "qorai/components/qorai_wayback_machine/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/ui/webui/settings/qorai_tor_handler.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "qorai/browser/extensions/manifest_v2/features.h"
#include "qorai/browser/ui/webui/settings/qorai_extensions_manifest_v2_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_tor_snowflake_extension_handler.h"
#endif

#if BUILDFLAG(ENABLE_CONTAINERS)
#include "qorai/components/containers/core/browser/containers_settings_handler.h"
#include "qorai/components/containers/core/common/features.h"
#endif

namespace {

bool IsLocaleJapan(Profile* profile) {
  if (auto* regional_capabilities = regional_capabilities::
          RegionalCapabilitiesServiceFactory::GetForProfile(profile)) {
    return regional_capabilities->GetCountryId() ==
           regional_capabilities::CountryIdHolder(
               country_codes::CountryId("JP"));
  }
  return false;
}

}  // namespace

QoraiSettingsUI::QoraiSettingsUI(content::WebUI* web_ui) : SettingsUI(web_ui) {
  web_ui->AddMessageHandler(
      std::make_unique<settings::MetricsReportingHandler>());
  web_ui->AddMessageHandler(std::make_unique<QoraiPrivacyHandler>());
  web_ui->AddMessageHandler(std::make_unique<DefaultQoraiShieldsHandler>());
  web_ui->AddMessageHandler(std::make_unique<QoraiDefaultExtensionsHandler>());
  web_ui->AddMessageHandler(std::make_unique<QoraiAppearanceHandler>());
  web_ui->AddMessageHandler(std::make_unique<QoraiSyncHandler>());
  web_ui->AddMessageHandler(std::make_unique<QoraiWalletHandler>());
  web_ui->AddMessageHandler(std::make_unique<QoraiAdBlockHandler>());
  web_ui->AddMessageHandler(
      std::make_unique<settings::QoraiQoraAssistantHandler>());

#if BUILDFLAG(ENABLE_TOR)
  web_ui->AddMessageHandler(std::make_unique<QoraiTorHandler>());
#endif
#if BUILDFLAG(ENABLE_EXTENSIONS)
  web_ui->AddMessageHandler(
      std::make_unique<QoraiTorSnowflakeExtensionHandler>());
  if (base::FeatureList::IsEnabled(
          extensions_mv2::features::kExtensionsManifestV2)) {
    web_ui->AddMessageHandler(
        std::make_unique<QoraiExtensionsManifestV2Handler>());
  }
#endif
#if BUILDFLAG(ENABLE_PIN_SHORTCUT)
  web_ui->AddMessageHandler(std::make_unique<PinShortcutHandler>());
#endif
#if BUILDFLAG(IS_WIN) && BUILDFLAG(ENABLE_QORAI_VPN)
  if (qorai_vpn::IsQoraiVPNEnabled(Profile::FromWebUI(web_ui))) {
    web_ui->AddMessageHandler(
        std::make_unique<QoraiVpnHandler>(Profile::FromWebUI(web_ui)));
  }
#endif
}

QoraiSettingsUI::~QoraiSettingsUI() = default;

// static
void QoraiSettingsUI::AddResources(content::WebUIDataSource* html_source,
                                   Profile* profile) {
  html_source->AddResourcePaths(kQoraiSettingsResources);

  html_source->AddBoolean("isSyncDisabled", !syncer::IsSyncAllowedByFlag());
  html_source->AddString(
      "qoraiProductVersion",
      version_info::GetQoraiVersionWithoutChromiumMajorVersion());
  NavigationBarDataProvider::Initialize(html_source, profile);
  html_source->AddBoolean(
      "isIdleDetectionFeatureEnabled",
      base::FeatureList::IsEnabled(features::kIdleDetection));
#if BUILDFLAG(ENABLE_QORAI_VPN)
  html_source->AddBoolean("isQoraiVPNEnabled",
                          qorai_vpn::IsQoraiVPNEnabled(profile));
#if BUILDFLAG(IS_MAC) && BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
  html_source->AddBoolean(
      "isQoraiVPNWireguardEnabledOnMac",
      base::FeatureList::IsEnabled(
          qorai_vpn::features::kQoraiVPNEnableWireguardForOSX));
#endif  // BUILDFLAG(IS_MAC) && BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)
#if BUILDFLAG(ENABLE_SPEEDREADER)
  html_source->AddBoolean(
      "isSpeedreaderAllowed",
      base::FeatureList::IsEnabled(
          speedreader::features::kSpeedreaderFeature) &&
          (profile->GetPrefs()->GetBoolean(speedreader::kSpeedreaderEnabled) ||
           !profile->GetPrefs()->IsManagedPreference(
               speedreader::kSpeedreaderEnabled)));
#endif
  html_source->AddBoolean(
      "isNativeQoraiWalletFeatureEnabled",
      base::FeatureList::IsEnabled(
          qorai_wallet::features::kNativeQoraiWalletFeature));
  html_source->AddBoolean("isCardanoDappSupportFeatureEnabled",
                          qorai_wallet::IsCardanoDAppSupportEnabled());
  html_source->AddBoolean("isQoraiWalletAllowed",
                          qorai_wallet::IsAllowedForContext(profile));
  html_source->AddBoolean("isForgetFirstPartyStorageFeatureEnabled",
                          base::FeatureList::IsEnabled(
                              net::features::kQoraiForgetFirstPartyStorage));
  html_source->AddBoolean("isQoraiRewardsSupported",
                          qorai_rewards::IsSupportedForProfile(profile));
  html_source->AddBoolean(
      "areShortcutsSupported",
      base::FeatureList::IsEnabled(commands::features::kQoraiCommands));

  html_source->AddBoolean("shouldExposeElementsForTesting",
                          ShouldExposeElementsForTesting());

  html_source->AddBoolean("enable_extensions", BUILDFLAG(ENABLE_EXTENSIONS));

  html_source->AddBoolean("extensionsManifestV2Feature",
                          base::FeatureList::IsEnabled(
                              extensions_mv2::features::kExtensionsManifestV2));

  html_source->AddBoolean("isQoraAssistantAllowed",
                          ai_chat::IsAIChatEnabled(profile->GetPrefs()));
  html_source->AddBoolean("isQoraAssistantHistoryAllowed",
                          ai_chat::features::IsAIChatHistoryEnabled());

  html_source->AddBoolean("isSurveyPanelistAllowed",
                          base::FeatureList::IsEnabled(
                              ntp_background_images::features::
                                  kQoraiNTPBrandedWallpaperSurveyPanelist));
  html_source->AddBoolean(
      "isPlaylistAllowed",
      base::FeatureList::IsEnabled(playlist::features::kPlaylist) &&
          profile->GetPrefs()->GetBoolean(playlist::kPlaylistEnabledPref));

  html_source->AddBoolean(
      "showCommandsInOmnibox",
      base::FeatureList::IsEnabled(features::kQoraiCommandsInOmnibox));
  html_source->AddBoolean(
      "isSharedPinnedTabsEnabled",
      base::FeatureList::IsEnabled(tabs::features::kQoraiSharedPinnedTabs));
  html_source->AddBoolean(
      "isEmailAliasesEnabled",
      base::FeatureList::IsEnabled(email_aliases::features::kEmailAliases));
#if BUILDFLAG(ENABLE_CONTAINERS)
  html_source->AddBoolean(
      "isContainersEnabled",
      base::FeatureList::IsEnabled(containers::features::kContainers));
#endif
  html_source->AddBoolean("isQoraiAccountEnabled",
                          qorai_account::features::IsQoraiAccountEnabled());
  html_source->AddBoolean("isOriginAllowed",
                          qorai_origin::IsQoraiOriginEnabled());
  html_source->AddBoolean(
      "isTreeTabsFlagEnabled",
      base::FeatureList::IsEnabled(tabs::features::kQoraiTreeTab));
  html_source->AddString("qoraiSearchEngineName",
                         TemplateURLPrepopulateData::qorai_search.name);
  html_source->AddBoolean("isLocaleJapan", IsLocaleJapan(profile));
  html_source->AddBoolean("isHideVerticalTabCompletelyFlagEnabled",
                          base::FeatureList::IsEnabled(
                              tabs::features::kQoraiVerticalTabHideCompletely));
}

// static
bool& QoraiSettingsUI::ShouldExposeElementsForTesting() {
  static bool expose_elements = false;
  return expose_elements;
}

void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<commands::mojom::CommandsService> pending_receiver) {
  commands::AcceleratorServiceFactory::GetForContext(
      web_ui()->GetWebContents()->GetBrowserContext())
      ->BindInterface(std::move(pending_receiver));
}

void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<ai_chat::mojom::AIChatSettingsHelper>
        pending_receiver) {
  auto helper = std::make_unique<ai_chat::AIChatSettingsHelper>(
      web_ui()->GetWebContents()->GetBrowserContext());
  mojo::MakeSelfOwnedReceiver(std::move(helper), std::move(pending_receiver));
}

void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<ai_chat::mojom::CustomizationSettingsHandler>
        pending_receiver) {
  auto handler = std::make_unique<ai_chat::CustomizationSettingsHandler>(
      user_prefs::UserPrefs::Get(
          web_ui()->GetWebContents()->GetBrowserContext()));
  mojo::MakeSelfOwnedReceiver(std::move(handler), std::move(pending_receiver));
}

void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<qorai_account::mojom::QoraiAccountSettingsHandler>
        pending_receiver) {
  qorai_account_settings_handler_ =
      std::make_unique<qorai_account::QoraiAccountSettingsHandler>(
          std::move(pending_receiver), web_ui());
}

#if BUILDFLAG(ENABLE_CONTAINERS)
void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<containers::mojom::ContainersSettingsHandler>
        pending_receiver) {
  if (!base::FeatureList::IsEnabled(containers::features::kContainers)) {
    return;
  }
  auto handler = std::make_unique<containers::ContainersSettingsHandler>(
      user_prefs::UserPrefs::Get(
          web_ui()->GetWebContents()->GetBrowserContext()));
  mojo::MakeSelfOwnedReceiver(std::move(handler), std::move(pending_receiver));
}
#endif  // BUILDFLAG(ENABLE_CONTAINERS)

void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<email_aliases::mojom::EmailAliasesService> receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  email_aliases::EmailAliasesServiceFactory::BindForProfile(
      profile, std::move(receiver));
}

void QoraiSettingsUI::BindInterface(
    mojo::PendingReceiver<qorai_origin::mojom::QoraiOriginSettingsHandler>
        receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  auto* qorai_origin_service =
      qorai_origin::QoraiOriginServiceFactory::GetForProfile(profile);
  // Service may be null for Guest profiles
  if (qorai_origin_service) {
    auto handler =
        std::make_unique<qorai_origin::QoraiOriginSettingsHandlerImpl>(
            qorai_origin_service);
    mojo::MakeSelfOwnedReceiver(std::move(handler), std::move(receiver));
  }
}
