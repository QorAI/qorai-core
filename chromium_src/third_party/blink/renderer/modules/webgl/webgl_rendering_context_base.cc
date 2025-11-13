/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <optional>

#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/html/canvas/canvas_rendering_context_host.h"
#include "third_party/blink/renderer/core/workers/worker_global_scope.h"
#include "third_party/blink/renderer/modules/webgl/webgl_rendering_context_base.h"

namespace {

bool AllowFingerprintingForHost(blink::CanvasRenderingContextHost* host) {
  if (!host)
    return true;
  return qorai::AllowFingerprinting(host->GetTopExecutionContext(),
                                    ContentSettingsType::QORAI_WEBCOMPAT_WEBGL);
}

}  // namespace

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_RETURN \
  if (!AllowFingerprintingForHost(Host()))        \
    return;

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_NULLPTR \
  if (!AllowFingerprintingForHost(Host()))         \
    return nullptr;

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_NULLOPT \
  if (!AllowFingerprintingForHost(Host()))         \
    return std::nullopt;

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_ZERO \
  if (!AllowFingerprintingForHost(Host()))      \
    return 0;

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_MINUS_ONE \
  if (!AllowFingerprintingForHost(Host()))           \
    return -1;

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_SCRIPT_VALUE \
  if (!AllowFingerprintingForHost(Host()))              \
    return ScriptValue::CreateNull(v8::Isolate::GetCurrent());

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_STRING \
  if (!AllowFingerprintingForHost(Host()))        \
    return String();

#define QORAI_WEBGL_RENDERING_CONTEXT_BASE_GETSHADERINFOLOG \
  if (!AllowFingerprintingForHost(Host())) {                \
    range[0] = 0;                                           \
    range[1] = 0;                                           \
    precision = 0;                                          \
  }

#define QORAI_WEBGL_GET_PARAMETER_UNMASKED_RENDERER     \
  if (ExtensionEnabled(kWebGLDebugRendererInfoName) &&  \
      !AllowFingerprintingForHost(Host()))              \
    return WebGLAny(                                    \
        script_state,                                   \
        String(qorai::QoraiSessionCache::From(          \
                   *(Host()->GetTopExecutionContext())) \
                   .GenerateRandomString("UNMASKED_RENDERER_WEBGL", 8)));

#define QORAI_WEBGL_GET_PARAMETER_UNMASKED_VENDOR       \
  if (ExtensionEnabled(kWebGLDebugRendererInfoName) &&  \
      !AllowFingerprintingForHost(Host()))              \
    return WebGLAny(                                    \
        script_state,                                   \
        String(qorai::QoraiSessionCache::From(          \
                   *(Host()->GetTopExecutionContext())) \
                   .GenerateRandomString("UNMASKED_VENDOR_WEBGL", 8)));

#define getExtension getExtension_ChromiumImpl
#define getSupportedExtensions getSupportedExtensions_ChromiumImpl
#include <third_party/blink/renderer/modules/webgl/webgl_rendering_context_base.cc>
#undef getSupportedExtensions
#undef getExtension

namespace blink {

// If fingerprinting is disallowed, claim that the only supported extension is
// WebGLDebugRendererInfo.
std::optional<Vector<String>>
WebGLRenderingContextBase::getSupportedExtensions() {
  std::optional<Vector<String>> real_extensions =
      getSupportedExtensions_ChromiumImpl();
  if (real_extensions == std::nullopt) {
    return real_extensions;
  }
  if (AllowFingerprintingForHost(Host()))
    return real_extensions;

  Vector<String> fake_extensions;
  fake_extensions.push_back(WebGLDebugRendererInfo::ExtensionName());
  return fake_extensions;
}

// If fingerprinting is disallowed and they're asking for information about any
// extension other than WebGLDebugRendererInfo, don't give it to them.
ScriptObject WebGLRenderingContextBase::getExtension(ScriptState* script_state,
                                                     const String& name) {
  if (!AllowFingerprintingForHost(Host())) {
    if (name != WebGLDebugRendererInfo::ExtensionName())
      return ScriptObject::CreateNull(v8::Isolate::GetCurrent());
  }
  return getExtension_ChromiumImpl(script_state, name);
}

}  // namespace blink

#undef QORAI_WEBGL_GET_PARAMETER_UNMASKED_VENDOR
#undef QORAI_WEBGL_GET_PARAMETER_UNMASKED_RENDERER
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_GETSHADERINFOLOG
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_STRING
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_SCRIPT_VALUE
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_MINUS_ONE
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_ZERO
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_NULLOPT
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_NULLPTR
#undef QORAI_WEBGL_RENDERING_CONTEXT_BASE_RETURN
