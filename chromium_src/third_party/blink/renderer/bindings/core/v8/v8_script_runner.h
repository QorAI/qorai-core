/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_BINDINGS_CORE_V8_V8_SCRIPT_RUNNER_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_BINDINGS_CORE_V8_V8_SCRIPT_RUNNER_H_

#include "v8/include/v8.h"

#define CompileScript(...)    \
  CompileScript(__VA_ARGS__); \
  static v8::MaybeLocal<v8::Script> CompileScript_ChromiumImpl(__VA_ARGS__)

#define CompileModule(...)    \
  CompileModule(__VA_ARGS__); \
  static v8::MaybeLocal<v8::Module> CompileModule_ChromiumImpl(__VA_ARGS__)

#include <third_party/blink/renderer/bindings/core/v8/v8_script_runner.h>  // IWYU pragma: export

#undef CompileModule
#undef CompileScript

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_BINDINGS_CORE_V8_V8_SCRIPT_RUNNER_H_
