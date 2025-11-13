/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_SERVICE_WORKER_HOLDER_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_SERVICE_WORKER_HOLDER_H_

#include "base/memory/raw_ptr.h"
#include "v8/include/v8.h"

class GURL;

namespace blink {
class WebServiceWorkerContextProxy;
class ThreadSafeBrowserInterfaceBrokerProxy;
}  // namespace blink

namespace qorai_search {

class QoraiSearchServiceWorkerHolder {
 public:
  QoraiSearchServiceWorkerHolder();
  QoraiSearchServiceWorkerHolder(const QoraiSearchServiceWorkerHolder&) =
      delete;
  QoraiSearchServiceWorkerHolder& operator=(
      const QoraiSearchServiceWorkerHolder&) = delete;
  ~QoraiSearchServiceWorkerHolder();

  void SetBrowserInterfaceBrokerProxy(
      blink::ThreadSafeBrowserInterfaceBrokerProxy* broker);
  void WillEvaluateServiceWorkerOnWorkerThread(
      blink::WebServiceWorkerContextProxy* context_proxy,
      v8::Local<v8::Context> v8_context,
      int64_t service_worker_version_id,
      const GURL& service_worker_scope,
      const GURL& script_url);
  void WillDestroyServiceWorkerContextOnWorkerThread(
      v8::Local<v8::Context> v8_context,
      int64_t service_worker_version_id,
      const GURL& service_worker_scope,
      const GURL& script_url);

 private:
  raw_ptr<blink::ThreadSafeBrowserInterfaceBrokerProxy> broker_ =
      nullptr;  // not owned
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_SERVICE_WORKER_HOLDER_H_
