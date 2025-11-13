// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_DEFAULT_JS_HANDLER_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_DEFAULT_JS_HANDLER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_search/common/qorai_search_default.mojom.h"
#include "content/public/renderer/render_frame.h"
#include "content/public/renderer/render_frame_observer.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "v8/include/v8.h"

namespace qorai_search {

// TODO(petemill): rename this to QoraiSearchFrameJSHandler
class QoraiSearchDefaultJSHandler {
 public:
  QoraiSearchDefaultJSHandler(content::RenderFrame* render_frame,
                              bool can_always_set_default);
  QoraiSearchDefaultJSHandler(const QoraiSearchDefaultJSHandler&) = delete;
  QoraiSearchDefaultJSHandler& operator=(const QoraiSearchDefaultJSHandler&) =
      delete;
  ~QoraiSearchDefaultJSHandler();

  void AddJavaScriptObjectToFrame(v8::Local<v8::Context> context);
  void ResetRemote(content::RenderFrame* render_frame);

 private:
  // Adds a function to the provided object.
  template <typename Sig>
  void BindFunctionToObject(v8::Isolate* isolate,
                            v8::Local<v8::Object> javascript_object,
                            const std::string& name,
                            const base::RepeatingCallback<Sig>& callback);
  void BindFunctionsToObject(v8::Isolate* isolate,
                             v8::Local<v8::Context> context);
  bool EnsureConnected();

  // A function to be called from JS
  v8::Local<v8::Promise> GetCanSetDefaultSearchProvider(v8::Isolate* isolate);
  void SetIsDefaultSearchProvider(v8::Isolate* isolate);

  void OnCanSetDefaultSearchProvider(
      std::unique_ptr<v8::Global<v8::Promise::Resolver>> promise_resolver,
      v8::Isolate* isolate,
      std::unique_ptr<v8::Global<v8::Context>> context_old,
      const bool response);

  raw_ptr<content::RenderFrame> render_frame_ = nullptr;
  const bool can_always_set_default_ = false;
  mojo::Remote<qorai_search::mojom::QoraiSearchDefault> qorai_search_default_;
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_RENDERER_QORAI_SEARCH_DEFAULT_JS_HANDLER_H_
