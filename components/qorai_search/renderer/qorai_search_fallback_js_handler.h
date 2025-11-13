/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_FALLBACK_JS_HANDLER_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_FALLBACK_JS_HANDLER_H_

#include <memory>
#include <string>

#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_search/common/qorai_search_fallback.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "v8/include/v8.h"

namespace blink {
class ThreadSafeBrowserInterfaceBrokerProxy;
}

namespace qorai_search {

// TODO(petemill): rename this to QoraiSearchWorkerJSHandler
class QoraiSearchFallbackJSHandler {
 public:
  QoraiSearchFallbackJSHandler(
      v8::Local<v8::Context> v8_context,
      blink::ThreadSafeBrowserInterfaceBrokerProxy* broker);
  QoraiSearchFallbackJSHandler(const QoraiSearchFallbackJSHandler&) = delete;
  QoraiSearchFallbackJSHandler& operator=(const QoraiSearchFallbackJSHandler&) =
      delete;
  ~QoraiSearchFallbackJSHandler();

  void AddJavaScriptObject();
  void Invalidate();
  v8::Local<v8::Context> Context();
  v8::Isolate* GetIsolate();

 private:
  // Adds a function to the provided object.
  template <typename Sig>
  void BindFunctionToObject(v8::Local<v8::Object> javascript_object,
                            const std::string& name,
                            const base::RepeatingCallback<Sig>& callback);
  void BindFunctionsToObject();
  bool EnsureConnected();

  // A function to be called from JS
  v8::Local<v8::Promise> FetchBackupResults(
      const std::string& query_string,
      const std::string& lang,
      const std::string& country,
      const std::string& geo,
      bool filter_explicit_results,
      int page_index,
      const std::string& cookie_header_value);
  void OnFetchBackupResults(
      std::unique_ptr<v8::Global<v8::Promise::Resolver>> promise_resolver,
      const std::string& response);

  raw_ptr<blink::ThreadSafeBrowserInterfaceBrokerProxy> broker_ =
      nullptr;  // not owned
  mojo::Remote<qorai_search::mojom::QoraiSearchFallback> qorai_search_fallback_;
  v8::Global<v8::Context> context_;
  raw_ptr<v8::Isolate> isolate_ = nullptr;
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_FALLBACK_JS_HANDLER_H_
