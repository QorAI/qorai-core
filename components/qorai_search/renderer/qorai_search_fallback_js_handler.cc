/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_search/renderer/qorai_search_fallback_js_handler.h"

#include <tuple>
#include <utility>

#include "base/no_destructor.h"
#include "content/public/renderer/render_frame.h"
#include "gin/arguments.h"
#include "gin/function_template.h"
#include "third_party/blink/public/common/thread_safe_browser_interface_broker_proxy.h"
#include "third_party/blink/public/platform/browser_interface_broker_proxy.h"
#include "third_party/blink/public/web/blink.h"
#include "third_party/blink/public/web/web_local_frame.h"
#include "third_party/blink/public/web/web_script_source.h"

namespace qorai_search {

QoraiSearchFallbackJSHandler::QoraiSearchFallbackJSHandler(
    v8::Local<v8::Context> v8_context,
    blink::ThreadSafeBrowserInterfaceBrokerProxy* broker)
    : broker_(broker),
      context_(v8::Isolate::GetCurrent(), v8_context),
      isolate_(v8::Isolate::GetCurrent()) {}

QoraiSearchFallbackJSHandler::~QoraiSearchFallbackJSHandler() = default;

bool QoraiSearchFallbackJSHandler::EnsureConnected() {
  if (!qorai_search_fallback_.is_bound() && broker_) {
    broker_->GetInterface(qorai_search_fallback_.BindNewPipeAndPassReceiver());
  }

  return qorai_search_fallback_.is_bound();
}

v8::Local<v8::Context> QoraiSearchFallbackJSHandler::Context() {
  return v8::Local<v8::Context>::New(isolate_, context_);
}

v8::Isolate* QoraiSearchFallbackJSHandler::GetIsolate() {
  return isolate_;
}

void QoraiSearchFallbackJSHandler::Invalidate() {
  context_.Reset();
}

void QoraiSearchFallbackJSHandler::AddJavaScriptObject() {
  v8::HandleScope handle_scope(isolate_);
  if (Context().IsEmpty())
    return;

  v8::Context::Scope context_scope(Context());
  v8::MicrotasksScope microtasks(isolate_, Context()->GetMicrotaskQueue(),
                                 v8::MicrotasksScope::kDoNotRunMicrotasks);

  BindFunctionsToObject();
}

void QoraiSearchFallbackJSHandler::BindFunctionsToObject() {
  v8::Local<v8::Object> global = Context()->Global();
  v8::Local<v8::Object> qorai_obj;
  v8::Local<v8::Value> qorai_value;
  if (!global->Get(Context(), gin::StringToV8(isolate_, "qorai"))
           .ToLocal(&qorai_value) ||
      !qorai_value->IsObject()) {
    qorai_obj = v8::Object::New(isolate_);
    global->Set(Context(), gin::StringToSymbol(isolate_, "qorai"), qorai_obj)
        .Check();
  } else {
    qorai_obj = qorai_value->ToObject(Context()).ToLocalChecked();
  }

  BindFunctionToObject(
      qorai_obj, "fetchBackupResults",
      base::BindRepeating(&QoraiSearchFallbackJSHandler::FetchBackupResults,
                          base::Unretained(this)));
}

template <typename Sig>
void QoraiSearchFallbackJSHandler::BindFunctionToObject(
    v8::Local<v8::Object> javascript_object,
    const std::string& name,
    const base::RepeatingCallback<Sig>& callback) {
  javascript_object
      ->Set(Context(), gin::StringToSymbol(isolate_, name),
            gin::CreateFunctionTemplate(isolate_, callback)
                ->GetFunction(Context())
                .ToLocalChecked())
      .Check();
}

v8::Local<v8::Promise> QoraiSearchFallbackJSHandler::FetchBackupResults(
    const std::string& query_string,
    const std::string& lang,
    const std::string& country,
    const std::string& geo,
    bool filter_explicit_results,
    int page_index,
    const std::string& cookie_header_value) {
  if (!EnsureConnected())
    return v8::Local<v8::Promise>();

  v8::MaybeLocal<v8::Promise::Resolver> resolver =
      v8::Promise::Resolver::New(Context());
  if (!resolver.IsEmpty()) {
    auto promise_resolver =
        std::make_unique<v8::Global<v8::Promise::Resolver>>();
    promise_resolver->Reset(isolate_, resolver.ToLocalChecked());
    qorai_search_fallback_->FetchBackupResults(
        query_string, lang, country, geo, filter_explicit_results, page_index,
        cookie_header_value.empty()
            ? std::nullopt
            : std::make_optional<std::string>(cookie_header_value),
        base::BindOnce(&QoraiSearchFallbackJSHandler::OnFetchBackupResults,
                       base::Unretained(this), std::move(promise_resolver)));

    return resolver.ToLocalChecked()->GetPromise();
  }

  return v8::Local<v8::Promise>();
}

void QoraiSearchFallbackJSHandler::OnFetchBackupResults(
    std::unique_ptr<v8::Global<v8::Promise::Resolver>> promise_resolver,
    const std::string& response) {
  v8::HandleScope handle_scope(isolate_);
  v8::Local<v8::Context> context = context_.Get(isolate_);
  v8::Context::Scope context_scope(context);
  v8::MicrotasksScope microtasks(isolate_, context->GetMicrotaskQueue(),
                                 v8::MicrotasksScope::kDoNotRunMicrotasks);

  v8::Local<v8::Promise::Resolver> resolver = promise_resolver->Get(isolate_);
  v8::Local<v8::String> result;
  result = v8::String::NewFromUtf8(isolate_, response.c_str()).ToLocalChecked();

  std::ignore = resolver->Resolve(context, result);
}

}  // namespace qorai_search
