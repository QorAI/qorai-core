/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/renderer/qorai_content_renderer_client.h"

#include <algorithm>
#include <utility>

#include "base/feature_list.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/ai_chat/renderer/page_content_extractor.h"
#include "qorai/components/ai_rewriter/common/buildflags/buildflags.h"
#include "qorai/components/qorai_search/common/qorai_search_utils.h"
#include "qorai/components/qorai_search/renderer/qorai_search_render_frame_observer.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/cosmetic_filters/renderer/cosmetic_filters_js_render_frame_observer.h"
#include "qorai/components/playlist/content/renderer/playlist_render_frame_observer.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/safe_builtins/renderer/safe_builtins.h"
#include "qorai/components/script_injector/renderer/script_injector_render_frame_observer.h"
#include "qorai/components/skus/common/features.h"
#include "qorai/components/skus/renderer/skus_render_frame_observer.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "qorai/renderer/qorai_render_frame_observer.h"
#include "qorai/renderer/qorai_render_thread_observer.h"
#include "qorai/renderer/qorai_wallet/qorai_wallet_render_frame_observer.h"
#include "chrome/common/chrome_isolated_world_ids.h"
#include "chrome/renderer/chrome_render_thread_observer.h"
#include "chrome/renderer/process_state.h"
#include "chrome/renderer/url_loader_throttle_provider_impl.h"
#include "components/feed/content/renderer/rss_link_reader.h"
#include "content/public/common/isolated_world_ids.h"
#include "content/public/renderer/render_thread.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/platform/web_runtime_features.h"
#include "third_party/blink/public/web/modules/service_worker/web_service_worker_context_proxy.h"
#include "third_party/blink/public/web/web_script_controller.h"
#include "third_party/widevine/cdm/buildflags.h"
#include "url/gurl.h"

#if BUILDFLAG(ENABLE_AI_REWRITER)
#include "qorai/components/ai_rewriter/common/features.h"
#include "qorai/components/ai_rewriter/renderer/ai_rewriter_agent.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/common/features.h"
#include "qorai/components/speedreader/renderer/speedreader_render_frame_observer.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#if BUILDFLAG(IS_ANDROID)
#include "qorai/components/qorai_mobile_subscription/renderer/android/subscription_render_frame_observer.h"
#endif  // BUILDFLAG(IS_ANDROID)
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "media/base/key_system_info.h"
#include "third_party/widevine/cdm/widevine_cdm_common.h"
#endif

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
#include "qorai/components/web_discovery/common/features.h"
#include "qorai/components/web_discovery/renderer/blink_document_extractor.h"
#endif

namespace {
void MaybeRemoveWidevineSupport(media::GetSupportedKeySystemsCB cb,
                                media::KeySystemInfos key_systems) {
#if BUILDFLAG(ENABLE_WIDEVINE)
  auto dynamic_params = QoraiRenderThreadObserver::GetDynamicParams();
  if (!dynamic_params.widevine_enabled) {
    auto to_remove = std::ranges::remove(
        key_systems, kWidevineKeySystem,
        [](const std::unique_ptr<media::KeySystemInfo>& key_system) {
          return key_system->GetBaseKeySystemName();
        });
    key_systems.erase(to_remove.begin(), to_remove.end());
  }
#endif
  cb.Run(std::move(key_systems));
}

}  // namespace

QoraiContentRendererClient::QoraiContentRendererClient() = default;

void QoraiContentRendererClient::
    SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() {
  ChromeContentRendererClient::
      SetRuntimeFeaturesDefaultsBeforeBlinkInitialization();

  blink::WebRuntimeFeatures::EnableFledge(false);
  blink::WebRuntimeFeatures::EnablePermissionElement(false);
  // Disable topics APIs because kBrowsingTopics feature is disabled
  blink::WebRuntimeFeatures::EnableTopicsAPI(false);
  blink::WebRuntimeFeatures::EnableTopicsDocumentAPI(false);
  blink::WebRuntimeFeatures::EnableWebGPUExperimentalFeatures(false);
  blink::WebRuntimeFeatures::EnableWebNFC(false);

  // These features don't have dedicated WebRuntimeFeatures wrappers.
  blink::WebRuntimeFeatures::EnableFeatureFromString("AdTagging", false);
  blink::WebRuntimeFeatures::EnableFeatureFromString("DigitalGoods", false);
  if (!base::FeatureList::IsEnabled(blink::features::kFileSystemAccessAPI)) {
    blink::WebRuntimeFeatures::EnableFeatureFromString("FileSystemAccessLocal",
                                                       false);
    blink::WebRuntimeFeatures::EnableFeatureFromString(
        "FileSystemAccessAPIExperimental", false);
  }
  blink::WebRuntimeFeatures::EnableFeatureFromString("FledgeMultiBid", false);
  blink::WebRuntimeFeatures::EnableFeatureFromString("PrivateStateTokens",
                                                     false);

#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
  if (base::FeatureList::IsEnabled(
          blink::features::kMiddleButtonClickAutoscroll)) {
    blink::WebRuntimeFeatures::EnableFeatureFromString("MiddleClickAutoscroll",
                                                       true);
  }
#endif  // BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
}

QoraiContentRendererClient::~QoraiContentRendererClient() = default;

void QoraiContentRendererClient::RenderThreadStarted() {
  ChromeContentRendererClient::RenderThreadStarted();

  qorai_observer_ = std::make_unique<QoraiRenderThreadObserver>();
  content::RenderThread::Get()->AddObserver(qorai_observer_.get());
  qorai_search_service_worker_holder_.SetBrowserInterfaceBrokerProxy(
      browser_interface_broker_.get());

  blink::WebScriptController::RegisterExtension(
      qorai::SafeBuiltins::CreateV8Extension());
}

void QoraiContentRendererClient::RenderFrameCreated(
    content::RenderFrame* render_frame) {
  ChromeContentRendererClient::RenderFrameCreated(render_frame);
  auto* rfo = new QoraiRenderFrameObserver(render_frame);
  auto* registry = rfo->registry();

  new feed::RssLinkReader(render_frame, registry);

  if (base::FeatureList::IsEnabled(
          qorai_shields::features::kQoraiAdblockCosmeticFiltering)) {
    auto dynamic_params_closure = base::BindRepeating([]() {
      auto dynamic_params = QoraiRenderThreadObserver::GetDynamicParams();
      return dynamic_params.de_amp_enabled;
    });

    new cosmetic_filters::CosmeticFiltersJsRenderFrameObserver(
        render_frame, ISOLATED_WORLD_ID_QORAI_INTERNAL, dynamic_params_closure);
  }

  if (base::FeatureList::IsEnabled(
          qorai_wallet::features::kNativeQoraiWalletFeature)) {
    new qorai_wallet::QoraiWalletRenderFrameObserver(
        render_frame,
        base::BindRepeating(&QoraiRenderThreadObserver::GetDynamicParams));
  }

  new script_injector::ScriptInjectorRenderFrameObserver(render_frame);

  if (qorai_search::IsDefaultAPIEnabled()) {
    new qorai_search::QoraiSearchRenderFrameObserver(
        render_frame, content::ISOLATED_WORLD_ID_GLOBAL);
  }

  if (base::FeatureList::IsEnabled(skus::features::kSkusFeature) &&
      !process_state::IsIncognitoProcess()) {
    skus::SkusRenderFrameObserver::Create(render_frame);
  }

#if BUILDFLAG(IS_ANDROID) && BUILDFLAG(ENABLE_QORAI_VPN)
  if (qorai_vpn::IsQoraiVPNFeatureEnabled() ||
      ai_chat::features::IsAIChatHistoryEnabled()) {
    new qorai_subscription::SubscriptionRenderFrameObserver(
        render_frame, content::ISOLATED_WORLD_ID_GLOBAL);
  }
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
  if (base::FeatureList::IsEnabled(
          speedreader::features::kSpeedreaderFeature)) {
    new speedreader::SpeedreaderRenderFrameObserver(
        render_frame, ISOLATED_WORLD_ID_QORAI_INTERNAL);
  }
#endif

  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist) &&
      !process_state::IsIncognitoProcess()) {
    new playlist::PlaylistRenderFrameObserver(
        render_frame, base::BindRepeating([] {
          return QoraiRenderThreadObserver::GetDynamicParams().playlist_enabled;
        }),
        ISOLATED_WORLD_ID_QORAI_INTERNAL);
  }

  if (ai_chat::features::IsAIChatEnabled() &&
      !process_state::IsIncognitoProcess()) {
    new ai_chat::PageContentExtractor(render_frame, registry,
                                      content::ISOLATED_WORLD_ID_GLOBAL,
                                      ISOLATED_WORLD_ID_QORAI_INTERNAL);
  }

#if BUILDFLAG(ENABLE_AI_REWRITER)
  if (ai_rewriter::features::IsAIRewriterEnabled()) {
    new ai_rewriter::AIRewriterAgent(render_frame, registry);
  }
#endif

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  if (base::FeatureList::IsEnabled(
          web_discovery::features::kQoraiWebDiscoveryNative) &&
      !process_state::IsIncognitoProcess()) {
    new web_discovery::BlinkDocumentExtractor(render_frame, registry);
  }
#endif
}

std::unique_ptr<media::KeySystemSupportRegistration>
QoraiContentRendererClient::GetSupportedKeySystems(
    content::RenderFrame* render_frame,
    media::GetSupportedKeySystemsCB cb) {
  return ChromeContentRendererClient::GetSupportedKeySystems(
      render_frame, base::BindRepeating(&MaybeRemoveWidevineSupport, cb));
}

void QoraiContentRendererClient::RunScriptsAtDocumentStart(
    content::RenderFrame* render_frame) {
  auto* observer =
      cosmetic_filters::CosmeticFiltersJsRenderFrameObserver::Get(render_frame);
  // Run this before any extensions
  if (observer) {
    observer->RunScriptsAtDocumentStart();
  }

  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    if (auto* playlist_observer =
            playlist::PlaylistRenderFrameObserver::Get(render_frame)) {
      playlist_observer->RunScriptsAtDocumentStart();
    }
  }

  ChromeContentRendererClient::RunScriptsAtDocumentStart(render_frame);
}

void QoraiContentRendererClient::RunScriptsAtDocumentEnd(
    content::RenderFrame* render_frame) {
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    if (auto* playlist_observer =
            playlist::PlaylistRenderFrameObserver::Get(render_frame)) {
      playlist_observer->RunScriptsAtDocumentEnd();
    }
  }

  ChromeContentRendererClient::RunScriptsAtDocumentEnd(render_frame);
}

void QoraiContentRendererClient::WillEvaluateServiceWorkerOnWorkerThread(
    blink::WebServiceWorkerContextProxy* context_proxy,
    v8::Local<v8::Context> v8_context,
    int64_t service_worker_version_id,
    const GURL& service_worker_scope,
    const GURL& script_url,
    const blink::ServiceWorkerToken& service_worker_token) {
  qorai_search_service_worker_holder_.WillEvaluateServiceWorkerOnWorkerThread(
      context_proxy, v8_context, service_worker_version_id,
      service_worker_scope, script_url);
  ChromeContentRendererClient::WillEvaluateServiceWorkerOnWorkerThread(
      context_proxy, v8_context, service_worker_version_id,
      service_worker_scope, script_url, service_worker_token);
}

void QoraiContentRendererClient::WillDestroyServiceWorkerContextOnWorkerThread(
    v8::Local<v8::Context> v8_context,
    int64_t service_worker_version_id,
    const GURL& service_worker_scope,
    const GURL& script_url) {
  qorai_search_service_worker_holder_
      .WillDestroyServiceWorkerContextOnWorkerThread(
          v8_context, service_worker_version_id, service_worker_scope,
          script_url);
  ChromeContentRendererClient::WillDestroyServiceWorkerContextOnWorkerThread(
      v8_context, service_worker_version_id, service_worker_scope, script_url);
}

std::unique_ptr<blink::URLLoaderThrottleProvider>
QoraiContentRendererClient::CreateURLLoaderThrottleProvider(
    blink::URLLoaderThrottleProviderType provider_type) {
  return URLLoaderThrottleProviderImpl::Create(provider_type, this,
                                               browser_interface_broker_.get());
}

bool QoraiContentRendererClient::IsOnionAllowed() const {
  return qorai_observer_->IsOnionAllowed();
}
