/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_RENDERER_QORAI_CONTENT_RENDERER_CLIENT_H_
#define QORAI_RENDERER_QORAI_CONTENT_RENDERER_CLIENT_H_

#include <memory>

#include "qorai/components/qorai_search/renderer/qorai_search_service_worker_holder.h"
#include "chrome/renderer/chrome_content_renderer_client.h"
#include "v8/include/v8.h"

class QoraiRenderThreadObserver;
class GURL;

namespace blink {
class WebServiceWorkerContextProxy;
}

class QoraiContentRendererClient : public ChromeContentRendererClient {
 public:
  QoraiContentRendererClient();
  QoraiContentRendererClient(const QoraiContentRendererClient&) = delete;
  QoraiContentRendererClient& operator=(const QoraiContentRendererClient&) =
      delete;
  ~QoraiContentRendererClient() override;

  void RenderThreadStarted() override;
  void SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() override;
  void RenderFrameCreated(content::RenderFrame* render_frame) override;
  std::unique_ptr<media::KeySystemSupportRegistration> GetSupportedKeySystems(
      content::RenderFrame* render_frame,
      media::GetSupportedKeySystemsCB cb) override;
  void RunScriptsAtDocumentStart(content::RenderFrame* render_frame) override;
  void RunScriptsAtDocumentEnd(content::RenderFrame* render_frame) override;
  void WillEvaluateServiceWorkerOnWorkerThread(
      blink::WebServiceWorkerContextProxy* context_proxy,
      v8::Local<v8::Context> v8_context,
      int64_t service_worker_version_id,
      const GURL& service_worker_scope,
      const GURL& script_url,
      const blink::ServiceWorkerToken& service_worker_token) override;
  void WillDestroyServiceWorkerContextOnWorkerThread(
      v8::Local<v8::Context> v8_context,
      int64_t service_worker_version_id,
      const GURL& service_worker_scope,
      const GURL& script_url) override;
  std::unique_ptr<blink::URLLoaderThrottleProvider>
  CreateURLLoaderThrottleProvider(
      blink::URLLoaderThrottleProviderType provider_type) override;

  bool IsOnionAllowed() const;

 private:
  std::unique_ptr<QoraiRenderThreadObserver> qorai_observer_;
  qorai_search::QoraiSearchServiceWorkerHolder
      qorai_search_service_worker_holder_;
};

#endif  // QORAI_RENDERER_QORAI_CONTENT_RENDERER_CLIENT_H_
