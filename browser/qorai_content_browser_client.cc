/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_content_browser_client.h"

#include <algorithm>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "base/check_op.h"
#include "base/command_line.h"
#include "base/functional/bind.h"
#include "base/strings/strcat.h"
#include "base/strings/string_number_conversions.h"
#include "base/system/sys_info.h"
#include "qorai/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/browser/qorai_account/qorai_account_navigation_throttle.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_browser_features.h"
#include "qorai/browser/qorai_browser_main_extra_parts.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_search/backup_results_navigation_throttle.h"
#include "qorai/browser/qorai_search/backup_results_service_factory.h"
#include "qorai/browser/qorai_shields/qorai_farbling_service_factory.h"
#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/browser/qorai_shields/qorai_shields_web_contents_observer.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_provider_delegate_impl.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_tab_helper.h"
#include "qorai/browser/cosmetic_filters/cosmetic_filters_tab_helper.h"
#include "qorai/browser/debounce/debounce_service_factory.h"
#include "qorai/browser/ephemeral_storage/ephemeral_storage_service_factory.h"
#include "qorai/browser/ephemeral_storage/ephemeral_storage_tab_helper.h"
#include "qorai/browser/net/qorai_proxying_url_loader_factory.h"
#include "qorai/browser/net/qorai_proxying_web_socket.h"
#include "qorai/browser/profiles/qorai_renderer_updater.h"
#include "qorai/browser/profiles/qorai_renderer_updater_factory.h"
#include "qorai/browser/skus/skus_service_factory.h"
#include "qorai/browser/ui/qorai_ui_features.h"
#include "qorai/browser/ui/webui/ads_internals/ads_internals_ui.h"
#include "qorai/browser/ui/webui/ai_chat/ai_chat_ui.h"
#include "qorai/browser/ui/webui/ai_chat/ai_chat_untrusted_conversation_ui.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_page_ui.h"
#include "qorai/browser/ui/webui/skus_internals_ui.h"
#include "qorai/browser/updater/buildflags.h"
#include "qorai/browser/url_sanitizer/url_sanitizer_service_factory.h"
#include "qorai/components/ai_chat/content/browser/ai_chat_qorai_search_throttle.h"
#include "qorai/components/ai_chat/content/browser/ai_chat_throttle.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/bookmarks.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/common.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/customization_settings.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/history.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/settings_helper.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/tab_tracker.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/untrusted_frame.mojom.h"
#include "qorai/components/ai_rewriter/common/buildflags/buildflags.h"
#include "qorai/components/body_sniffer/body_sniffer_throttle.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_account/mojom/qorai_account.mojom.h"
#include "qorai/components/qorai_education/buildflags.h"
#include "qorai/components/qorai_origin/common/mojom/qorai_origin_settings.mojom.h"
#include "qorai/components/qorai_rewards/content/rewards_protocol_navigation_throttle.h"
#include "qorai/components/qorai_search/browser/backup_results_service.h"
#include "qorai/components/qorai_search/browser/qorai_search_default_host.h"
#include "qorai/components/qorai_search/browser/qorai_search_default_host_private.h"
#include "qorai/components/qorai_search/browser/qorai_search_fallback_host.h"
#include "qorai/components/qorai_search/common/qorai_search_default.mojom.h"
#include "qorai/components/qorai_search/common/qorai_search_fallback.mojom.h"
#include "qorai/components/qorai_search/common/qorai_search_utils.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_shields/content/browser/qorai_farbling_service.h"
#include "qorai/components/qorai_shields/content/browser/qorai_shields_util.h"
#include "qorai/components/qorai_shields/content/browser/domain_block_navigation_throttle.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/shields_settings.mojom.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_p3a_private.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/containers/buildflags/buildflags.h"
#include "qorai/components/cosmetic_filters/browser/cosmetic_filters_resources.h"
#include "qorai/components/cosmetic_filters/common/cosmetic_filters.mojom.h"
#include "qorai/components/de_amp/browser/de_amp_body_handler.h"
#include "qorai/components/debounce/content/browser/debounce_navigation_throttle.h"
#include "qorai/components/decentralized_dns/content/decentralized_dns_navigation_throttle.h"
#include "qorai/components/email_aliases/features.h"
#include "qorai/components/global_privacy_control/global_privacy_control_utils.h"
#include "qorai/components/google_sign_in_permission/google_sign_in_permission_throttle.h"
#include "qorai/components/google_sign_in_permission/google_sign_in_permission_util.h"
#include "qorai/components/ntp_background_images/browser/mojom/ntp_background_images.mojom.h"
#include "qorai/components/password_strength_meter/password_strength_meter.mojom.h"
#include "qorai/components/playlist/content/browser/playlist_background_web_contents_helper.h"
#include "qorai/components/playlist/content/browser/playlist_media_handler.h"
#include "qorai/components/playlist/core/common/buildflags/buildflags.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/playlist/core/common/mojom/playlist.mojom.h"
#include "qorai/components/request_otr/common/buildflags/buildflags.h"
#include "qorai/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "qorai/components/skus/common/features.h"
#include "qorai/components/skus/common/skus_internals.mojom.h"
#include "qorai/components/skus/common/skus_sdk.mojom.h"
#include "qorai/components/skus/common/skus_utils.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/translate/core/common/qorai_translate_switches.h"
#include "qorai/components/url_sanitizer/core/browser/url_sanitizer_service.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "qorai/third_party/blink/renderer/qorai_farbling_constants.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/chrome_browser_interface_binders.h"
#include "chrome/browser/chrome_browser_main.h"
#include "chrome/browser/chrome_content_browser_client.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_io_data.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "chrome/common/url_constants.h"
#include "chrome/grit/branded_strings.h"
#include "components/content_settings/browser/page_specific_content_settings.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/embedder_support/switches.h"
#include "components/prefs/pref_service.h"
#include "components/services/heap_profiling/public/mojom/heap_profiling_client.mojom.h"
#include "components/user_prefs/user_prefs.h"
#include "components/version_info/version_info.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/browser_url_handler.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle_registry.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/storage_partition.h"
#include "content/public/browser/weak_document_ptr.h"
#include "content/public/browser/web_ui_browser_interface_broker_registry.h"
#include "content/public/browser/web_ui_controller_interface_binder.h"
#include "content/public/common/content_client.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/url_constants.h"
#include "extensions/buildflags/buildflags.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "net/cookies/site_for_cookies.h"
#include "services/service_manager/public/cpp/binder_registry.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_registry.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/loader/url_loader_throttle.h"
#include "third_party/blink/public/common/switches.h"
#include "third_party/blink/public/mojom/webpreferences/web_preferences.mojom.h"
#include "third_party/widevine/cdm/buildflags.h"
#include "ui/base/l10n/l10n_util.h"

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "qorai/browser/request_otr/request_otr_service_factory.h"
#include "qorai/components/request_otr/browser/request_otr_navigation_throttle.h"
#include "qorai/components/request_otr/browser/request_otr_storage_tab_helper.h"
#endif

using blink::web_pref::WebPreferences;
using qorai_shields::QorAIShieldsWebContentsObserver;
using qorai_shields::ControlType;
using qorai_shields::GetQorAIShieldsEnabled;
using qorai_shields::GetFingerprintingControlType;
using content::BrowserThread;
using content::ContentBrowserClient;
using content::RenderFrameHost;
using content::WebContents;

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "chrome/browser/extensions/chrome_content_browser_client_extensions_part.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/common/constants.h"

using extensions::ChromeContentBrowserClientExtensionsPart;
#endif

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/ai_chat/utils.h"
#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_desktop.h"
#include "qorai/ui/webui/qorai_color_change_listener/qorai_color_change_handler.h"
#include "ui/webui/resources/cr_components/color_change_listener/color_change_listener.mojom.h"
#endif
#if BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_android.h"
#include "qorai/components/ai_chat/core/browser/android/ai_chat_iap_subscription_android.h"
#endif

#if BUILDFLAG(ENABLE_AI_REWRITER)
#include "qorai/browser/ui/webui/ai_rewriter/ai_rewriter_ui.h"
#include "qorai/components/ai_rewriter/common/features.h"
#include "qorai/components/ai_rewriter/common/mojom/ai_rewriter.mojom.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/tor/tor_profile_service_factory.h"
#include "qorai/components/tor/onion_location_navigation_throttle.h"
#include "qorai/components/tor/tor_navigation_throttle.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/speedreader/speedreader_service_factory.h"
#include "qorai/browser/ui/speedreader/speedreader_tab_helper.h"
#include "qorai/components/speedreader/speedreader_body_distiller.h"
#include "qorai/components/speedreader/speedreader_distilled_page_producer.h"
#include "qorai/components/speedreader/speedreader_util.h"
#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/webui/speedreader/speedreader_toolbar_ui.h"
#include "qorai/components/speedreader/common/speedreader_toolbar.mojom.h"
#endif
#endif

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "qorai/browser/qorai_drm_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/ui/webui/qorai_vpn/vpn_panel_ui.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#endif

#if BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/webui/qorai_wallet/android/android_wallet_page_ui.h"
#include "qorai/browser/ui/webui/new_tab_takeover/android/new_tab_takeover_ui.h"
#endif  // BUILDFLAG(IS_ANDROID)

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/new_tab/new_tab_shows_navigation_throttle.h"
#include "qorai/browser/ui/geolocation/qorai_geolocation_permission_tab_helper.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/qorai_new_tab_page.mojom.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/qorai_new_tab_page_ui.h"
#include "qorai/browser/ui/webui/qorai_news_internals/qorai_news_internals_ui.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_page_top_ui.h"
#include "qorai/browser/ui/webui/qorai_settings_ui.h"
#include "qorai/browser/ui/webui/qorai_shields/shields_panel_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_page_ui.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_panel_ui.h"
#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_ui.h"
#include "qorai/browser/ui/webui/private_new_tab_page/qorai_private_new_tab_ui.h"
#include "qorai/components/qorai_account/mojom/qorai_account_settings_handler.mojom.h"
#include "qorai/components/qorai_new_tab_ui/qorai_new_tab_page.mojom.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"
#include "qorai/components/qorai_news/common/features.h"
#include "qorai/components/qorai_private_new_tab_ui/common/qorai_private_new_tab.mojom.h"
#include "qorai/components/qorai_shields/core/common/qorai_shields_panel.mojom.h"
#include "qorai/components/commands/common/commands.mojom.h"
#include "qorai/components/commands/common/features.h"
#include "components/omnibox/browser/searchbox.mojom.h"
#endif

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
#include "qorai/browser/ui/webui/playlist_ui.h"
#endif  // BUILDFLAG(ENABLE_PLAYLIST_WEBUI)

#if BUILDFLAG(ENABLE_QORAI_EDUCATION)
#include "qorai/browser/ui/webui/qorai_education/qorai_education_page_ui.h"
#endif

#if BUILDFLAG(ENABLE_CONTAINERS)
#include "qorai/components/containers/core/common/features.h"
#include "qorai/components/containers/core/mojom/containers.mojom.h"
#endif

#if BUILDFLAG(IS_WIN)
#include "qorai/components/windows_recall/windows_recall.h"
#endif

#if BUILDFLAG(ENABLE_OMAHA4)
#include "qorai/browser/qorai_browser_main_extra_parts_p3a.h"
#endif

namespace {

bool HandleURLReverseOverrideRewrite(GURL* url,
                                     content::BrowserContext* browser_context) {
  if (QorAIContentBrowserClient::HandleURLOverrideRewrite(url,
                                                          browser_context)) {
    return true;
  }

// For wallet pages, return true to update the displayed URL to react-routed
// URL rather than showing qorai://wallet for everything. This is needed
// because of a side effect from rewriting qorai:// to chrome:// in
// HandleURLRewrite handler which makes qorai://wallet the virtual URL here
// unless we return true to trigger an update of virtual URL here to the routed
// URL. For example, we will display qorai://wallet/send instead of
// qorai://wallet with this. This is Android only because currently both
// virtual and real URLs are chrome:// on desktop, so it doesn't have this
// issue.
#if BUILDFLAG(IS_ANDROID)
  if ((url->SchemeIs(content::kQorAIUIScheme) ||
       url->SchemeIs(content::kChromeUIScheme)) &&
      url->host() == kWalletPageHost) {
    if (url->SchemeIs(content::kChromeUIScheme)) {
      GURL::Replacements replacements;
      replacements.SetSchemeStr(content::kQorAIUIScheme);
      *url = url->ReplaceComponents(replacements);
    }
    return true;
  }
#endif

  return false;
}

bool HandleURLRewrite(GURL* url, content::BrowserContext* browser_context) {
  if (QorAIContentBrowserClient::HandleURLOverrideRewrite(url,
                                                          browser_context)) {
    return true;
  }

// For wallet pages, return true so we can handle it in the reverse handler.
// Also update the real URL from qorai:// to chrome://.
#if BUILDFLAG(IS_ANDROID)
  if ((url->SchemeIs(content::kQorAIUIScheme) ||
       url->SchemeIs(content::kChromeUIScheme)) &&
      url->host() == kWalletPageHost) {
    if (url->SchemeIs(content::kQorAIUIScheme)) {
      GURL::Replacements replacements;
      replacements.SetSchemeStr(content::kChromeUIScheme);
      *url = url->ReplaceComponents(replacements);
    }
    return true;
  }
#endif

  return false;
}

void BindCosmeticFiltersResourcesOnTaskRunner(
    mojo::PendingReceiver<cosmetic_filters::mojom::CosmeticFiltersResources>
        receiver) {
  mojo::MakeSelfOwnedReceiver(
      std::make_unique<cosmetic_filters::CosmeticFiltersResources>(
          g_qorai_browser_process->ad_block_service()),
      std::move(receiver));
}

void BindCosmeticFiltersResources(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<cosmetic_filters::mojom::CosmeticFiltersResources>
        receiver) {
  g_qorai_browser_process->ad_block_service()->GetTaskRunner()->PostTask(
      FROM_HERE, base::BindOnce(&BindCosmeticFiltersResourcesOnTaskRunner,
                                std::move(receiver)));
}

void MaybeBindWalletP3A(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<qorai_wallet::mojom::QorAIWalletP3A> receiver) {
  auto* context = frame_host->GetBrowserContext();
  if (qorai_wallet::IsAllowedForContext(frame_host->GetBrowserContext())) {
    qorai_wallet::QorAIWalletService* wallet_service =
        qorai_wallet::QorAIWalletServiceFactory::GetServiceForContext(context);
    DCHECK(wallet_service);
    wallet_service->GetQorAIWalletP3A()->Bind(std::move(receiver));
  } else {
    // Dummy API to avoid reporting P3A for OTR contexts
    mojo::MakeSelfOwnedReceiver(
        std::make_unique<qorai_wallet::QorAIWalletP3APrivate>(),
        std::move(receiver));
  }
}

void BindQorAISearchFallbackHost(
    content::ChildProcessId process_id,
    mojo::PendingReceiver<qorai_search::mojom::QorAISearchFallback> receiver) {
  content::RenderProcessHost* render_process_host =
      content::RenderProcessHost::FromID(process_id);
  if (!render_process_host) {
    return;
  }

  content::BrowserContext* context = render_process_host->GetBrowserContext();
  auto* backup_results_service =
      qorai_search::BackupResultsServiceFactory::GetForBrowserContext(context);
  if (!backup_results_service) {
    return;
  }
  mojo::MakeSelfOwnedReceiver(
      std::make_unique<qorai_search::QorAISearchFallbackHost>(
          backup_results_service),
      std::move(receiver));
}

void BindQorAISearchDefaultHost(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<qorai_search::mojom::QorAISearchDefault> receiver) {
  const GURL& frame_host_url = frame_host->GetLastCommittedURL();
  if (!qorai_search::IsAllowedHost(frame_host_url)) {
    return;
  }
  auto* context = frame_host->GetBrowserContext();
  auto* profile = Profile::FromBrowserContext(context);
  if (profile->IsRegularProfile()) {
    auto* template_url_service =
        TemplateURLServiceFactory::GetForProfile(profile);
    const std::string host = frame_host->GetLastCommittedURL().host();
    mojo::MakeSelfOwnedReceiver(
        std::make_unique<qorai_search::QorAISearchDefaultHost>(
            host, template_url_service, profile->GetPrefs()),
        std::move(receiver));
  } else {
    // Dummy API which always returns false for private contexts.
    mojo::MakeSelfOwnedReceiver(
        std::make_unique<qorai_search::QorAISearchDefaultHostPrivate>(),
        std::move(receiver));
  }
}

#if BUILDFLAG(IS_ANDROID)
void BindIAPSubscription(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<ai_chat::mojom::IAPSubscription> receiver) {
  const GURL& frame_host_url = frame_host->GetLastCommittedURL();
  if (!skus::IsSafeOrigin(frame_host_url)) {
    return;
  }
  auto* context = frame_host->GetBrowserContext();
  auto* profile = Profile::FromBrowserContext(context);
  mojo::MakeSelfOwnedReceiver(
      std::make_unique<ai_chat::AIChatIAPSubscription>(profile->GetPrefs()),
      std::move(receiver));
}
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
void MaybeBindQorAIVpnImpl(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler> receiver) {
  const GURL& frame_host_url = frame_host->GetLastCommittedURL();
  if (!skus::IsSafeOrigin(frame_host_url)) {
    return;
  }
  auto* context = frame_host->GetBrowserContext();
  qorai_vpn::QorAIVpnServiceFactory::BindForContext(context,
                                                    std::move(receiver));
}
#endif
void MaybeBindSkusSdkImpl(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<skus::mojom::SkusService> receiver) {
  const GURL& frame_host_url = frame_host->GetLastCommittedURL();
  if (!skus::IsSafeOrigin(frame_host_url)) {
    return;
  }
  auto* context = frame_host->GetBrowserContext();
  skus::SkusServiceFactory::BindForContext(context, std::move(receiver));
}

#if !BUILDFLAG(IS_ANDROID)
void MaybeBindColorChangeHandler(
    content::RenderFrameHost* const frame_host,
    mojo::PendingReceiver<color_change_listener::mojom::PageHandler> receiver) {
  const GURL& frame_host_url = frame_host->GetLastCommittedURL();

  // Only supported on chrome://, chrome-untrusted:// and chrome-extension://
  // urls
  if (!frame_host_url.SchemeIs(content::kChromeUIScheme) &&
      !frame_host_url.SchemeIs(content::kChromeUIUntrustedScheme) &&
      !frame_host_url.SchemeIs(extensions::kExtensionScheme)) {
    return;
  }

  ui::QorAIColorChangeHandler::BindInterface(
      content::WebContents::FromRenderFrameHost(frame_host),
      std::move(receiver));
}
#endif

bool IsJsBlockingEnforced(content::BrowserContext* browser_context,
                          const GURL& url) {
  Profile* profile = Profile::FromBrowserContext(browser_context);
  auto* settings_service =
      QorAIShieldsSettingsServiceFactory::GetForProfile(profile);
  if (!settings_service) {
    return false;
  }

  return settings_service->IsJsBlockingEnforced(url);
}

}  // namespace

QorAIContentBrowserClient::QorAIContentBrowserClient() = default;

QorAIContentBrowserClient::~QorAIContentBrowserClient() = default;

std::unique_ptr<content::BrowserMainParts>
QorAIContentBrowserClient::CreateBrowserMainParts(bool is_integration_test) {
  std::unique_ptr<content::BrowserMainParts> main_parts =
      ChromeContentBrowserClient::CreateBrowserMainParts(is_integration_test);
  ChromeBrowserMainParts* chrome_main_parts =
      static_cast<ChromeBrowserMainParts*>(main_parts.get());
  chrome_main_parts->AddParts(std::make_unique<QorAIBrowserMainExtraParts>());
#if BUILDFLAG(ENABLE_OMAHA4)
  chrome_main_parts->AddParts(
      std::make_unique<QorAIBrowserMainExtraPartsP3A>());
#endif
  return main_parts;
}

bool QorAIContentBrowserClient::AreIsolatedWebAppsEnabled(
    content::BrowserContext* browser_context) {
  return false;
}

void QorAIContentBrowserClient::BrowserURLHandlerCreated(
    content::BrowserURLHandler* handler) {
  handler->AddHandlerPair(&HandleURLRewrite, &HandleURLReverseOverrideRewrite);
  ChromeContentBrowserClient::BrowserURLHandlerCreated(handler);
}

void QorAIContentBrowserClient::RenderProcessWillLaunch(
    content::RenderProcessHost* host) {
  Profile* profile = Profile::FromBrowserContext(host->GetBrowserContext());
  // The QorAIRendererUpdater might be null for some irregular profiles, e.g.
  // the System Profile.
  if (QorAIRendererUpdater* service =
          QorAIRendererUpdaterFactory::GetForProfile(profile)) {
    service->InitializeRenderer(host);
  }

  ChromeContentBrowserClient::RenderProcessWillLaunch(host);
}

void QorAIContentBrowserClient::
    RegisterAssociatedInterfaceBindersForRenderFrameHost(
        content::RenderFrameHost& render_frame_host,                // NOLINT
        blink::AssociatedInterfaceRegistry& associated_registry) {  // NOLINT
#if BUILDFLAG(ENABLE_WIDEVINE)
  associated_registry.AddInterface<
      qorai_drm::mojom::QorAIDRM>(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<qorai_drm::mojom::QorAIDRM> receiver) {
        QorAIDrmTabHelper::BindQorAIDRM(std::move(receiver), render_frame_host);
      },
      &render_frame_host));
#endif  // BUILDFLAG(ENABLE_WIDEVINE)

#if !BUILDFLAG(IS_ANDROID)
  associated_registry.AddInterface<
      geolocation::mojom::QorAIGeolocationPermission>(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<
             geolocation::mojom::QorAIGeolocationPermission> receiver) {
        QorAIGeolocationPermissionTabHelper::BindQorAIGeolocationPermission(
            std::move(receiver), render_frame_host);
      },
      &render_frame_host));
#endif  // !BUILDFLAG(IS_ANDROID)

  associated_registry.AddInterface<
      qorai_shields::mojom::QorAIShieldsHost>(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<qorai_shields::mojom::QorAIShieldsHost>
             receiver) {
        qorai_shields::QorAIShieldsWebContentsObserver::BindQorAIShieldsHost(
            std::move(receiver), render_frame_host);
      },
      &render_frame_host));

#if BUILDFLAG(ENABLE_SPEEDREADER)
  associated_registry.AddInterface<speedreader::mojom::SpeedreaderHost>(
      base::BindRepeating(
          [](content::RenderFrameHost* render_frame_host,
             mojo::PendingAssociatedReceiver<
                 speedreader::mojom::SpeedreaderHost> receiver) {
            speedreader::SpeedreaderTabHelper::BindSpeedreaderHost(
                std::move(receiver), render_frame_host);
          },
          &render_frame_host));
#endif

  associated_registry.AddInterface<playlist::mojom::PlaylistMediaResponder>(
      base::BindRepeating(
          &playlist::PlaylistMediaHandler::BindMediaResponderReceiver,
          &render_frame_host));

  associated_registry.AddInterface<
      cosmetic_filters::mojom::CosmeticFiltersHandler>(base::BindRepeating(
      &cosmetic_filters::CosmeticFiltersTabHelper::BindCosmeticFiltersHandler,
      &render_frame_host));

  ChromeContentBrowserClient::
      RegisterAssociatedInterfaceBindersForRenderFrameHost(render_frame_host,
                                                           associated_registry);
}

void QorAIContentBrowserClient::RegisterWebUIInterfaceBrokers(
    content::WebUIBrowserInterfaceBrokerRegistry& registry) {
  ChromeContentBrowserClient::RegisterWebUIInterfaceBrokers(registry);
#if !BUILDFLAG(IS_ANDROID)
  registry.AddGlobal<color_change_listener::mojom::PageHandler>(
      base::BindRepeating(&MaybeBindColorChangeHandler));
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN) && !BUILDFLAG(IS_ANDROID)
  if (qorai_vpn::IsQorAIVPNFeatureEnabled()) {
    registry.ForWebUI<VPNPanelUI>()
        .Add<qorai_vpn::mojom::PanelHandlerFactory>();
  }
#endif

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    registry.ForWebUI<playlist::PlaylistUI>()
        .Add<playlist::mojom::PageHandlerFactory>();
  }
#endif

  if (ai_chat::features::IsAIChatEnabled()) {
    registry.ForWebUI<AIChatUI>()
        .Add<ai_chat::mojom::AIChatUIHandler>()
        .Add<ai_chat::mojom::Service>()
        .Add<ai_chat::mojom::TabTrackerService>()
        .Add<ai_chat::mojom::BookmarksPageHandler>()
        .Add<ai_chat::mojom::HistoryUIHandler>();
    registry.ForWebUI<AIChatUntrustedConversationUI>()
        .Add<ai_chat::mojom::UntrustedUIHandler>();
  }

#if BUILDFLAG(ENABLE_AI_REWRITER)
  if (ai_rewriter::features::IsAIRewriterEnabled()) {
    registry.ForWebUI<ai_rewriter::AIRewriterUI>()
        .Add<ai_rewriter::mojom::AIRewriterPageHandler>();
  }
#endif

  registry.ForWebUI<AdsInternalsUI>().Add<bat_ads::mojom::AdsInternals>();

  if (base::FeatureList::IsEnabled(skus::features::kSkusFeature)) {
    registry.ForWebUI<SkusInternalsUI>().Add<skus::mojom::SkusInternals>();
  }

  registry.ForWebUI<qorai_rewards::RewardsPageUI>()
      .Add<qorai_rewards::mojom::RewardsPageHandler>();

#if !BUILDFLAG(IS_ANDROID)
  registry.ForWebUI<WalletPageUI>()
      .Add<qorai_wallet::mojom::PageHandlerFactory>()
      .Add<qorai_rewards::mojom::RewardsPageHandler>();

  registry.ForWebUI<WalletPanelUI>()
      .Add<qorai_wallet::mojom::PanelHandlerFactory>()
      .Add<qorai_rewards::mojom::RewardsPageHandler>();

  auto ntp_refresh_registration =
      registry.ForWebUI<QorAINewTabPageUI>()
          .Add<qorai_new_tab_page_refresh::mojom::NewTabPageHandler>()
          .Add<qorai_rewards::mojom::RewardsPageHandler>()
          .Add<qorai_news::mojom::QorAINewsController>()
          .Add<
              ntp_background_images::mojom::SponsoredRichMediaAdEventHandler>();

  auto ntp_registration =
      registry.ForWebUI<QorAINewTabUI>()
          .Add<qorai_new_tab_page::mojom::PageHandlerFactory>()
          .Add<qorai_news::mojom::QorAINewsController>();

#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (qorai_vpn::IsQorAIVPNFeatureEnabled()) {
    ntp_refresh_registration.Add<qorai_vpn::mojom::ServiceHandler>();
    ntp_registration.Add<qorai_vpn::mojom::ServiceHandler>();
  }
#endif

  if (base::FeatureList::IsEnabled(features::kQorAINtpSearchWidget)) {
    ntp_refresh_registration.Add<searchbox::mojom::PageHandler>();
    ntp_registration.Add<searchbox::mojom::PageHandler>();
  }

  if (base::FeatureList::IsEnabled(
          qorai_news::features::kQorAINewsFeedUpdate)) {
    registry.ForWebUI<QorAINewsInternalsUI>()
        .Add<qorai_news::mojom::QorAINewsController>()
        .Add<qorai_news::mojom::QorAINewsInternals>();
  }

  if (qorai_account::features::IsQorAIAccountEnabled()) {
    registry.ForWebUI<QorAIAccountUIDesktop>()
        .Add<qorai_account::mojom::Authentication>()
        .Add<password_strength_meter::mojom::PasswordStrengthMeter>();
  }
#else   // !BUILDFLAG(IS_ANDROID)
  registry.ForWebUI<NewTabTakeoverUI>()
      .Add<new_tab_takeover::mojom::NewTabTakeover>();

  if (qorai_account::features::IsQorAIAccountEnabled()) {
    registry.ForWebUI<QorAIAccountUIAndroid>()
        .Add<qorai_account::mojom::Authentication>()
        .Add<password_strength_meter::mojom::PasswordStrengthMeter>();
  }
#endif  // !BUILDFLAG(IS_ANDROID)
}

std::optional<base::UnguessableToken>
QorAIContentBrowserClient::GetEphemeralStorageToken(
    content::RenderFrameHost* render_frame_host,
    const url::Origin& origin) {
  DCHECK(render_frame_host);
  auto* wc = content::WebContents::FromRenderFrameHost(render_frame_host);
  if (!wc) {
    return std::nullopt;
  }

  auto* es_tab_helper =
      ephemeral_storage::EphemeralStorageTabHelper::FromWebContents(wc);
  if (!es_tab_helper) {
    return std::nullopt;
  }

  return es_tab_helper->GetEphemeralStorageToken(origin);
}

bool QorAIContentBrowserClient::CanThirdPartyStoragePartitioningBeDisabled(
    content::BrowserContext* browser_context,
    const url::Origin& origin) {
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(browser_context);
  if (!host_content_settings_map) {
    return false;
  }
  auto cookie_settings = CookieSettingsFactory::GetForProfile(
      Profile::FromBrowserContext(browser_context));
  if (!cookie_settings) {
    return false;
  }
  const auto url = origin.GetURL();
  return !qorai_shields::GetQorAIShieldsEnabled(host_content_settings_map,
                                                url) ||
         qorai_shields::GetCookieControlType(host_content_settings_map,
                                             cookie_settings.get(), url) ==
             qorai_shields::ControlType::ALLOW;
}

bool QorAIContentBrowserClient::AllowWorkerFingerprinting(
    const GURL& url,
    content::BrowserContext* browser_context) {
  return WorkerGetQorAIShieldSettings(url, browser_context)->farbling_level !=
         qorai_shields::mojom::FarblingLevel::MAXIMUM;
}

qorai_shields::mojom::ShieldsSettingsPtr
QorAIContentBrowserClient::WorkerGetQorAIShieldSettings(
    const GURL& url,
    content::BrowserContext* browser_context) {
  const qorai_shields::mojom::FarblingLevel farbling_level =
      qorai_shields::GetFarblingLevel(
          HostContentSettingsMapFactory::GetForProfile(browser_context), url);
  const base::Token farbling_token =
      farbling_level != qorai_shields::mojom::FarblingLevel::OFF
          ? qorai_shields::GetFarblingToken(
                HostContentSettingsMapFactory::GetForProfile(browser_context),
                url)
          : base::Token();

  PrefService* pref_service = user_prefs::UserPrefs::Get(browser_context);

  return qorai_shields::mojom::ShieldsSettings::New(
      farbling_level, farbling_token, std::vector<std::string>(),
      qorai_shields::IsReduceLanguageEnabledForProfile(pref_service),
      IsJsBlockingEnforced(browser_context, url));
}

content::ContentBrowserClient::AllowWebBluetoothResult
QorAIContentBrowserClient::AllowWebBluetooth(
    content::BrowserContext* browser_context,
    const url::Origin& requesting_origin,
    const url::Origin& embedding_origin) {
  if (!base::FeatureList::IsEnabled(blink::features::kQorAIWebBluetoothAPI)) {
    return ContentBrowserClient::AllowWebBluetoothResult::
        BLOCK_GLOBALLY_DISABLED;
  }
  return ChromeContentBrowserClient::AllowWebBluetooth(
      browser_context, requesting_origin, embedding_origin);
}

bool QorAIContentBrowserClient::CanCreateWindow(
    content::RenderFrameHost* opener,
    const GURL& opener_url,
    const GURL& opener_top_level_frame_url,
    const url::Origin& source_origin,
    content::mojom::WindowContainerType container_type,
    const GURL& target_url,
    const content::Referrer& referrer,
    const std::string& frame_name,
    WindowOpenDisposition disposition,
    const blink::mojom::WindowFeatures& features,
    bool user_gesture,
    bool opener_suppressed,
    bool* no_javascript_access) {
  // Check base implementation first
  bool can_create_window = ChromeContentBrowserClient::CanCreateWindow(
      opener, opener_url, opener_top_level_frame_url, source_origin,
      container_type, target_url, referrer, frame_name, disposition, features,
      user_gesture, opener_suppressed, no_javascript_access);

#if BUILDFLAG(ENABLE_REQUEST_OTR)
  // If the user has requested going off-the-record in this tab, don't allow
  // opening new windows via script
  if (content::WebContents* web_contents =
          content::WebContents::FromRenderFrameHost(opener)) {
    if (request_otr::
            RequestOTRStorageTabHelper* request_otr_storage_tab_helper =
                request_otr::RequestOTRStorageTabHelper::FromWebContents(
                    web_contents)) {
      if (request_otr_storage_tab_helper->has_requested_otr()) {
        *no_javascript_access = true;
      }
    }
  }
#endif

  return can_create_window && google_sign_in_permission::CanCreateWindow(
                                  opener, opener_url, target_url);
}

void QorAIContentBrowserClient::ExposeInterfacesToRenderer(
    service_manager::BinderRegistry* registry,
    blink::AssociatedInterfaceRegistry* associated_registry,
    content::RenderProcessHost* render_process_host) {
  ChromeContentBrowserClient::ExposeInterfacesToRenderer(
      registry, associated_registry, render_process_host);
  registry->AddInterface(base::BindRepeating(&BindQorAISearchFallbackHost,
                                             render_process_host->GetID()),
                         content::GetUIThreadTaskRunner({}));
}

void QorAIContentBrowserClient::RegisterBrowserInterfaceBindersForFrame(
    content::RenderFrameHost* render_frame_host,
    mojo::BinderMapWithContext<content::RenderFrameHost*>* map) {
  ChromeContentBrowserClient::RegisterBrowserInterfaceBindersForFrame(
      render_frame_host, map);
  map->Add<cosmetic_filters::mojom::CosmeticFiltersResources>(
      base::BindRepeating(&BindCosmeticFiltersResources));
  if (qorai_search::IsDefaultAPIEnabled()) {
    map->Add<qorai_search::mojom::QorAISearchDefault>(
        base::BindRepeating(&BindQorAISearchDefaultHost));
  }

  map->Add<qorai_wallet::mojom::QorAIWalletP3A>(
      base::BindRepeating(&MaybeBindWalletP3A));
  if (qorai_wallet::IsAllowedForContext(
          render_frame_host->GetBrowserContext())) {
    if (qorai_wallet::IsNativeWalletEnabled()) {
      map->Add<qorai_wallet::mojom::EthereumProvider>(base::BindRepeating(
          &qorai_wallet::QorAIWalletTabHelper::BindEthereumProvider));
      map->Add<qorai_wallet::mojom::SolanaProvider>(base::BindRepeating(
          &qorai_wallet::QorAIWalletTabHelper::BindSolanaProvider));
      if (qorai_wallet::IsCardanoDAppSupportEnabled()) {
        map->Add<qorai_wallet::mojom::CardanoProvider>(base::BindRepeating(
            &qorai_wallet::QorAIWalletTabHelper::BindCardanoProvider));
      }
    }
  }

  map->Add<skus::mojom::SkusService>(
      base::BindRepeating(&MaybeBindSkusSdkImpl));
#if BUILDFLAG(ENABLE_QORAI_VPN)
  map->Add<qorai_vpn::mojom::ServiceHandler>(
      base::BindRepeating(&MaybeBindQorAIVpnImpl));
#endif

#if BUILDFLAG(IS_ANDROID)
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_wallet::mojom::PageHandlerFactory, AndroidWalletPageUI>(map);
#endif

#if !BUILDFLAG(IS_ANDROID)
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_private_new_tab::mojom::PageHandler, QorAIPrivateNewTabUI>(map);
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_shields::mojom::PanelHandlerFactory, ShieldsPanelUI>(map);
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_rewards::mojom::RewardsPageHandler,
      qorai_rewards::RewardsPageTopUI>(map);
  if (base::FeatureList::IsEnabled(commands::features::kQorAICommands)) {
    content::RegisterWebUIControllerInterfaceBinder<
        commands::mojom::CommandsService, QorAISettingsUI>(map);
  }
  if (qorai_account::features::IsQorAIAccountEnabled()) {
    content::RegisterWebUIControllerInterfaceBinder<
        qorai_account::mojom::QorAIAccountSettingsHandler, QorAISettingsUI>(
        map);
  }

  if (base::FeatureList::IsEnabled(email_aliases::features::kEmailAliases)) {
    content::RegisterWebUIControllerInterfaceBinder<
        email_aliases::mojom::EmailAliasesService, QorAISettingsUI>(map);
  }

  map->Add<color_change_listener::mojom::PageHandler>(
      base::BindRepeating(&MaybeBindColorChangeHandler));
#endif

  auto* prefs =
      user_prefs::UserPrefs::Get(render_frame_host->GetBrowserContext());
  if (ai_chat::IsAIChatEnabled(prefs) &&
      Profile::FromBrowserContext(render_frame_host->GetBrowserContext())
          ->IsRegularProfile()) {
    // WebUI -> Browser interface
    content::RegisterWebUIControllerInterfaceBinder<
        ai_chat::mojom::AIChatUIHandler, AIChatUI>(map);
#if !BUILDFLAG(IS_ANDROID)
    content::RegisterWebUIControllerInterfaceBinder<
        ai_chat::mojom::AIChatSettingsHelper, QorAISettingsUI>(map);
    content::RegisterWebUIControllerInterfaceBinder<
        ai_chat::mojom::CustomizationSettingsHandler, QorAISettingsUI>(map);
#endif
  }
#if BUILDFLAG(IS_ANDROID)
  if (ai_chat::IsAIChatEnabled(prefs)) {
    map->Add<ai_chat::mojom::IAPSubscription>(
        base::BindRepeating(&BindIAPSubscription));
  }
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER) && !BUILDFLAG(IS_ANDROID)
  content::RegisterWebUIControllerInterfaceBinder<
      speedreader::mojom::ToolbarFactory, SpeedreaderToolbarUI>(map);
#endif

#if BUILDFLAG(ENABLE_QORAI_EDUCATION)
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_education::mojom::PageHandlerFactory, QorAIEducationPageUI>(map);
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_browser_command::mojom::QorAIBrowserCommandHandlerFactory,
      QorAIEducationPageUI>(map);
#endif

#if BUILDFLAG(ENABLE_CONTAINERS)
  if (base::FeatureList::IsEnabled(containers::features::kContainers)) {
    content::RegisterWebUIControllerInterfaceBinder<
        containers::mojom::ContainersSettingsHandler, QorAISettingsUI>(map);
  }
#endif
#if !BUILDFLAG(IS_ANDROID)
  // Register QorAIOrigin handler for settings WebUI
  content::RegisterWebUIControllerInterfaceBinder<
      qorai_origin::mojom::QorAIOriginSettingsHandler, QorAISettingsUI>(map);
#endif
}

bool QorAIContentBrowserClient::HandleExternalProtocol(
    const GURL& url,
    content::WebContents::Getter web_contents_getter,
    content::FrameTreeNodeId frame_tree_node_id,
    content::NavigationUIData* navigation_data,
    bool is_primary_main_frame,
    bool is_in_fenced_frame_tree,
    network::mojom::WebSandboxFlags sandbox_flags,
    ui::PageTransition page_transition,
    bool has_user_gesture,
    const std::optional<url::Origin>& initiating_origin,
    content::RenderFrameHost* initiator_document,
    const net::IsolationInfo& isolation_info,
    mojo::PendingRemote<network::mojom::URLLoaderFactory>* out_factory) {
  return ChromeContentBrowserClient::HandleExternalProtocol(
      url, web_contents_getter, frame_tree_node_id, navigation_data,
      is_primary_main_frame, is_in_fenced_frame_tree, sandbox_flags,
      page_transition, has_user_gesture, initiating_origin, initiator_document,
      isolation_info, out_factory);
}

void QorAIContentBrowserClient::AppendExtraCommandLineSwitches(
    base::CommandLine* command_line,
    int child_process_id) {
  ChromeContentBrowserClient::AppendExtraCommandLineSwitches(command_line,
                                                             child_process_id);

  std::string process_type =
      command_line->GetSwitchValueASCII(switches::kProcessType);
  if (process_type == switches::kRendererProcess) {
#if BUILDFLAG(QORAI_V8_ENABLE_DRUMBRAKE)
    if (base::FeatureList::IsEnabled(features::kQorAIWebAssemblyJitless)) {
      content::RenderProcessHost* process =
          content::RenderProcessHost::FromID(child_process_id);
      if (process && process->IsJitDisabled()) {
        command_line->AppendSwitchASCII(blink::switches::kJavaScriptFlags,
                                        "--wasm-jitless");
      }
    }
#endif  // BUILDFLAG(QORAI_V8_ENABLE_DRUMBRAKE)
    // Command line parameters from the browser process are propagated to the
    // renderers *after* ContentBrowserClient::AppendExtraCommandLineSwitches()
    // is called from RenderProcessHostImpl::AppendRendererCommandLine(). This
    // means we have to inspect the main browser process' parameters for the
    // |switches::kTestType| as it will be too soon to find it on command_line.
    const base::CommandLine& browser_command_line =
        *base::CommandLine::ForCurrentProcess();
    if (!browser_command_line.HasSwitch(switches::kTestType)) {
      if (command_line->HasSwitch(switches::kEnableIsolatedWebAppsInRenderer)) {
        command_line->RemoveSwitch(switches::kEnableIsolatedWebAppsInRenderer);
      }
    }

    // Switches to pass to render processes.
    static const char* const kSwitchNames[] = {
        translate::switches::kQorAITranslateUseGoogleEndpoint,
    };
    command_line->CopySwitchesFrom(browser_command_line, kSwitchNames);
  }
}

std::vector<std::unique_ptr<blink::URLLoaderThrottle>>
QorAIContentBrowserClient::CreateURLLoaderThrottles(
    const network::ResourceRequest& request,
    content::BrowserContext* browser_context,
    const content::WebContents::Getter& wc_getter,
    content::NavigationUIData* navigation_ui_data,
    content::FrameTreeNodeId frame_tree_node_id,
    std::optional<int64_t> navigation_id) {
  auto result = ChromeContentBrowserClient::CreateURLLoaderThrottles(
      request, browser_context, wc_getter, navigation_ui_data,
      frame_tree_node_id, navigation_id);
  content::WebContents* contents = wc_getter.Run();

  if (contents) {
    const bool isMainFrame =
        request.resource_type ==
        static_cast<int>(blink::mojom::ResourceType::kMainFrame);

    auto body_sniffer_throttle =
        std::make_unique<body_sniffer::BodySnifferThrottle>(
            base::SingleThreadTaskRunner::GetCurrentDefault());

    // Speedreader
#if BUILDFLAG(ENABLE_SPEEDREADER)
    auto* tab_helper =
        speedreader::SpeedreaderTabHelper::FromWebContents(contents);
    if (tab_helper && isMainFrame) {
      auto* speedreader_service =
          speedreader::SpeedreaderServiceFactory::GetForBrowserContext(
              browser_context);
      CHECK(speedreader_service);

      auto producer =
          speedreader::SpeedreaderDistilledPageProducer::MaybeCreate(
              tab_helper->GetWeakPtr());
      if (producer) {
        body_sniffer_throttle->SetBodyProducer(std::move(producer));
      }

      auto handler = speedreader::SpeedreaderBodyDistiller::MaybeCreate(
          g_qorai_browser_process->speedreader_rewriter_service(),
          speedreader_service, tab_helper->GetWeakPtr());
      if (handler) {
        body_sniffer_throttle->AddHandler(std::move(handler));
      }
    }
#endif  // ENABLE_SPEEDREADER

    if (isMainFrame) {
      // De-AMP
      auto handler = de_amp::DeAmpBodyHandler::Create(request, wc_getter);
      if (handler) {
        body_sniffer_throttle->AddHandler(std::move(handler));
      }
    }

    result.push_back(std::move(body_sniffer_throttle));

    if (auto google_sign_in_permission_throttle =
            google_sign_in_permission::GoogleSignInPermissionThrottle::
                MaybeCreateThrottleFor(request, wc_getter)) {
      result.push_back(std::move(google_sign_in_permission_throttle));
    }
  }

  return result;
}

void QorAIContentBrowserClient::WillCreateURLLoaderFactory(
    content::BrowserContext* browser_context,
    content::RenderFrameHost* frame,
    int render_process_id,
    URLLoaderFactoryType type,
    const url::Origin& request_initiator,
    const net::IsolationInfo& isolation_info,
    std::optional<int64_t> navigation_id,
    ukm::SourceIdObj ukm_source_id,
    network::URLLoaderFactoryBuilder& factory_builder,
    mojo::PendingRemote<network::mojom::TrustedURLLoaderHeaderClient>*
        header_client,
    bool* bypass_redirect_checks,
    bool* disable_secure_dns,
    network::mojom::URLLoaderFactoryOverridePtr* factory_override,
    scoped_refptr<base::SequencedTaskRunner> navigation_response_task_runner) {
  // TODO(iefremov): Skip proxying for certain requests?
  QorAIProxyingURLLoaderFactory::MaybeProxyRequest(
      browser_context, frame, factory_builder, navigation_response_task_runner);

  ChromeContentBrowserClient::WillCreateURLLoaderFactory(
      browser_context, frame, render_process_id, type, request_initiator,
      isolation_info, std::move(navigation_id), ukm_source_id, factory_builder,
      header_client, bypass_redirect_checks, disable_secure_dns,
      factory_override, navigation_response_task_runner);
}

bool QorAIContentBrowserClient::WillInterceptWebSocket(
    content::RenderFrameHost* frame) {
  return (frame != nullptr);
}

void QorAIContentBrowserClient::CreateWebSocket(
    content::RenderFrameHost* frame,
    content::ContentBrowserClient::WebSocketFactory factory,
    const GURL& url,
    const net::SiteForCookies& site_for_cookies,
    const std::optional<std::string>& user_agent,
    mojo::PendingRemote<network::mojom::WebSocketHandshakeClient>
        handshake_client) {
  auto* proxy = QorAIProxyingWebSocket::ProxyWebSocket(
      frame, std::move(factory), url, site_for_cookies, user_agent);

  if (ChromeContentBrowserClient::WillInterceptWebSocket(frame)) {
    ChromeContentBrowserClient::CreateWebSocket(
        frame, proxy->CreateWebSocketFactory(), url, site_for_cookies,
        user_agent, std::move(handshake_client));
  } else {
    proxy->Start(std::move(handshake_client));
  }
}

void QorAIContentBrowserClient::MaybeHideReferrer(
    content::BrowserContext* browser_context,
    const GURL& request_url,
    const GURL& document_url,
    blink::mojom::ReferrerPtr* referrer) {
  DCHECK(referrer && !referrer->is_null());
#if BUILDFLAG(ENABLE_EXTENSIONS)
  if (document_url.SchemeIs(extensions::kExtensionScheme) ||
      request_url.SchemeIs(extensions::kExtensionScheme)) {
    return;
  }
#endif
  if (document_url.SchemeIs(content::kChromeUIScheme) ||
      request_url.SchemeIs(content::kChromeUIScheme)) {
    return;
  }

  Profile* profile = Profile::FromBrowserContext(browser_context);
  const bool allow_referrers = qorai_shields::AreReferrersAllowed(
      HostContentSettingsMapFactory::GetForProfile(profile), document_url);
  const bool shields_up = qorai_shields::GetQorAIShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(profile), document_url);

  content::Referrer new_referrer;
  if (qorai_shields::MaybeChangeReferrer(allow_referrers, shields_up,
                                         (*referrer)->url, request_url,
                                         &new_referrer)) {
    (*referrer)->url = new_referrer.url;
    (*referrer)->policy = new_referrer.policy;
  }
}

std::optional<GURL> QorAIContentBrowserClient::GetEffectiveURL(
    content::BrowserContext* browser_context,
    const GURL& url) {
  Profile* profile = Profile::FromBrowserContext(browser_context);
  if (!profile) {
    return url;
  }

#if BUILDFLAG(ENABLE_EXTENSIONS)
  if (extensions::ChromeContentBrowserClientExtensionsPart::
          AreExtensionsDisabledForProfile(profile)) {
    return url;
  }
  return ChromeContentBrowserClientExtensionsPart::GetEffectiveURL(profile,
                                                                   url);
#else
  return url;
#endif
}

// [static]
bool QorAIContentBrowserClient::HandleURLOverrideRewrite(
    GURL* url,
    content::BrowserContext* browser_context) {
  // Some of these rewrites are for WebUI pages with URL that has moved.
  // After rewrite happens, GetWebUIFactoryFunction() will work as expected.
  // (see browser\ui\webui\qorai_web_ui_controller_factory.cc for more info)
  //
  // Scope of schema is intentionally narrower than content::HasWebUIScheme(url)
  // which also allows both `chrome-untrusted` and `chrome-devtools`.
  if (!url->SchemeIs(content::kQorAIUIScheme) &&
      !url->SchemeIs(content::kChromeUIScheme)) {
    return false;
  }

  // qorai://sync => qorai://settings/qoraiSync
  if (url->host() == chrome::kQorAIUISyncHost) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kChromeUIScheme);
    replacements.SetHostStr(chrome::kChromeUISettingsHost);
    replacements.SetPathStr(kQorAISyncPath);
    *url = url->ReplaceComponents(replacements);
    return true;
  }

#if !BUILDFLAG(IS_ANDROID)
  // qorai://adblock => qorai://settings/shields/filters
  if (url->host() == kAdblockHost) {
    GURL::Replacements replacements;
    replacements.SetSchemeStr(content::kChromeUIScheme);
    replacements.SetHostStr(chrome::kChromeUISettingsHost);
    replacements.SetPathStr(kContentFiltersPath);
    *url = url->ReplaceComponents(replacements);
    return false;
  }
#endif

  // no special win10 welcome page
  if (url->host() == kWelcomeHost) {
    *url = GURL(kWelcomeURL);
    return true;
  }

  return false;
}

void QorAIContentBrowserClient::CreateThrottlesForNavigation(
    content::NavigationThrottleRegistry& registry) {
  // inserting the navigation throttle at the fist position before any java
  // navigation happens
  qorai_rewards::RewardsProtocolNavigationThrottle::MaybeCreateAndAdd(registry);

  ChromeContentBrowserClient::CreateThrottlesForNavigation(registry);

  content::NavigationHandle& navigation_handle = registry.GetNavigationHandle();
  content::BrowserContext* context =
      navigation_handle.GetWebContents()->GetBrowserContext();

  QorAIAccountNavigationThrottle::MaybeCreateAndAdd(registry);

#if !BUILDFLAG(IS_ANDROID)
  NewTabShowsNavigationThrottle::MaybeCreateAndAdd(registry);
#endif

#if BUILDFLAG(ENABLE_TOR)
  tor::TorNavigationThrottle::MaybeCreateAndAdd(registry, context->IsTor());
  tor::OnionLocationNavigationThrottle::MaybeCreateAndAdd(
      registry, TorProfileServiceFactory::IsTorDisabled(context),
      context->IsTor());
#endif

  decentralized_dns::DecentralizedDnsNavigationThrottle::MaybeCreateAndAdd(
      registry, user_prefs::UserPrefs::Get(context),
      g_browser_process->local_state(),
      g_browser_process->GetApplicationLocale());

  // Debounce
  debounce::DebounceNavigationThrottle::MaybeCreateAndAdd(
      registry,
      debounce::DebounceServiceFactory::GetForBrowserContext(context));

  // The HostContentSettingsMap might be null for some irregular profiles, e.g.
  // the System Profile.
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(context);
  if (host_content_settings_map) {
    qorai_shields::DomainBlockNavigationThrottle::MaybeCreateAndAdd(
        registry, g_qorai_browser_process->ad_block_service(),
        g_qorai_browser_process->ad_block_service()->custom_filters_provider(),
        EphemeralStorageServiceFactory::GetForContext(context),
        host_content_settings_map, g_browser_process->GetApplicationLocale());
  }

#if BUILDFLAG(ENABLE_REQUEST_OTR)
  // Request Off-The-Record
  request_otr::RequestOTRNavigationThrottle::MaybeCreateAndAdd(
      registry,
      request_otr::RequestOTRServiceFactory::GetForBrowserContext(context),
      EphemeralStorageServiceFactory::GetForContext(context),
      Profile::FromBrowserContext(context)->GetPrefs(),
      g_browser_process->GetApplicationLocale());
#endif

  if (Profile::FromBrowserContext(context)->IsRegularProfile()) {
    ai_chat::AIChatThrottle::MaybeCreateAndAdd(registry);
  }

#if !BUILDFLAG(IS_ANDROID)
  ai_chat::AIChatQorAISearchThrottle::MaybeCreateAndAdd(
      base::BindOnce(&ai_chat::OpenAIChatForTab), registry,
      ai_chat::AIChatServiceFactory::GetForBrowserContext(context),
      user_prefs::UserPrefs::Get(context));
#endif

  qorai_search::BackupResultsNavigationThrottle::MaybeCreateAndAdd(registry);
}

// Updates the global privacy control web preference and returns true if it is
// changed.
bool UpdateGlobalPrivacyControlWebPreference(WebContents* web_contents,
                                             WebPreferences* prefs) {
  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  CHECK(profile);

  const bool global_privacy_control_enabled =
      global_privacy_control::IsGlobalPrivacyControlEnabled(
          profile->GetPrefs());
  if (prefs->global_privacy_control_enabled == global_privacy_control_enabled) {
    return false;
  }

  prefs->global_privacy_control_enabled = global_privacy_control_enabled;
  return true;
}

bool PreventDarkModeFingerprinting(WebContents* web_contents,
                                   content::SiteInstance& main_frame_site,
                                   WebPreferences* prefs) {
  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  // The HostContentSettingsMap might be null for some irregular profiles, e.g.
  // the System Profile.
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(profile);
  if (!host_content_settings_map) {
    return false;
  }
  const GURL url = main_frame_site.GetSiteURL();
  const bool shields_up =
      qorai_shields::GetQorAIShieldsEnabled(host_content_settings_map, url);
  auto fingerprinting_type = qorai_shields::GetFingerprintingControlType(
      host_content_settings_map, url);
  // https://github.com/qorai/qorai-browser/issues/15265
  // Always use color scheme Light if fingerprinting mode strict
  if (base::FeatureList::IsEnabled(
          qorai_shields::features::kQorAIDarkModeBlock) &&
      shields_up && fingerprinting_type == ControlType::BLOCK &&
      prefs->preferred_color_scheme !=
          blink::mojom::PreferredColorScheme::kLight) {
    prefs->preferred_color_scheme = blink::mojom::PreferredColorScheme::kLight;
    return true;
  }
  return false;
}

std::vector<url::Origin>
QorAIContentBrowserClient::GetOriginsRequiringDedicatedProcess() {
  std::vector<url::Origin> isolated_origin_list;

  std::transform(skus::kSafeOrigins.cbegin(), skus::kSafeOrigins.cend(),
                 std::back_inserter(isolated_origin_list),
                 [](auto& url) { return url::Origin::Create(GURL(url)); });

  if (qorai_search::IsDefaultAPIEnabled()) {
    std::transform(qorai_search::kVettedHosts.cbegin(),
                   qorai_search::kVettedHosts.cend(),
                   std::back_inserter(isolated_origin_list),
                   [](auto& url) { return url::Origin::Create(GURL(url)); });
  }

  auto origins_from_chrome =
      ChromeContentBrowserClient::GetOriginsRequiringDedicatedProcess();
  std::move(std::begin(origins_from_chrome), std::end(origins_from_chrome),
            std::back_inserter(isolated_origin_list));

  return isolated_origin_list;
}

bool QorAIContentBrowserClient::OverrideWebPreferencesAfterNavigation(
    WebContents* web_contents,
    content::SiteInstance& main_frame_site,
    WebPreferences* prefs) {
  bool changed =
      ChromeContentBrowserClient::OverrideWebPreferencesAfterNavigation(
          web_contents, main_frame_site, prefs);

  return PreventDarkModeFingerprinting(web_contents, main_frame_site, prefs) ||
         UpdateGlobalPrivacyControlWebPreference(web_contents, prefs) ||
         changed;
}

void QorAIContentBrowserClient::OverrideWebPreferences(
    WebContents* web_contents,
    content::SiteInstance& main_frame_site,
    WebPreferences* web_prefs) {
  ChromeContentBrowserClient::OverrideWebPreferences(
      web_contents, main_frame_site, web_prefs);
  PreventDarkModeFingerprinting(web_contents, main_frame_site, web_prefs);
  UpdateGlobalPrivacyControlWebPreference(web_contents, web_prefs);

  if (playlist::PlaylistBackgroundWebContentsHelper::FromWebContents(
          web_contents)) {
    web_prefs->force_cosmetic_filtering = true;
  }
}

blink::UserAgentMetadata QorAIContentBrowserClient::GetUserAgentMetadata() {
  blink::UserAgentMetadata metadata =
      ChromeContentBrowserClient::GetUserAgentMetadata();
  // Expect the brand version lists to have brand version, chromium_version, and
  // greased version.
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(embedder_support::kUserAgent)) {
    return metadata;
  }
  DCHECK_EQ(3UL, metadata.brand_version_list.size());
  DCHECK_EQ(3UL, metadata.brand_full_version_list.size());
  // Zero out the last 3 version components in full version list versions.
  for (auto& brand_version : metadata.brand_full_version_list) {
    base::Version version(brand_version.version);
    brand_version.version =
        base::StrCat({base::NumberToString(version.components()[0]), ".0.0.0"});
  }
  // Zero out the last 3 version components in full version.
  base::Version version(metadata.full_version);
  metadata.full_version =
      base::StrCat({base::NumberToString(version.components()[0]), ".0.0.0"});
  return metadata;
}

std::optional<GURL> QorAIContentBrowserClient::SanitizeURL(
    content::RenderFrameHost* render_frame_host,
    const GURL& url) {
  if (!base::FeatureList::IsEnabled(features::kQorAICopyCleanLinkFromJs)) {
    return std::nullopt;
  }
  CHECK(render_frame_host);
  CHECK(render_frame_host->GetBrowserContext());
  auto* url_sanitizer_service =
      qorai::URLSanitizerServiceFactory::GetForBrowserContext(
          render_frame_host->GetBrowserContext());
  CHECK(url_sanitizer_service);
  if (!url_sanitizer_service->CheckJsPermission(
          render_frame_host->GetLastCommittedURL())) {
    return std::nullopt;
  }
  const GURL& sanitized_url = url_sanitizer_service->SanitizeURL(url);
  if (sanitized_url == url) {
    // No actual replacements were made.
    return std::nullopt;
  }
  return sanitized_url;
}

bool QorAIContentBrowserClient::IsWindowsRecallDisabled() {
#if BUILDFLAG(IS_WIN)
  return windows_recall::IsWindowsRecallDisabled(
      g_browser_process->local_state());
#else
  return false;
#endif
}

bool QorAIContentBrowserClient::AllowSignedExchange(
    content::BrowserContext* context) {
  // This override has been introduced due to the deletion of the flag
  // `features::kSignedHTTPExchange`, which was being used to disable signed
  // exchanges.
  return false;
}

bool QorAIContentBrowserClient::IsJitDisabledForSite(
    content::BrowserContext* browser_context,
    const GURL& site_url) {
  // When v8-jitless-mode flag is enabled, V8 optimizer
  // settings should disable JIT completely, not just optimizations
  if (AreV8OptimizationsDisabledForSite(browser_context, site_url) &&
      base::FeatureList::IsEnabled(features::kQorAIV8JitlessMode)) {
    return true;
  }

  return ChromeContentBrowserClient::IsJitDisabledForSite(browser_context,
                                                          site_url);
}
