/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_V8_SRC_BUILTINS_BUILTINS_H_
#define QORAI_CHROMIUM_SRC_V8_SRC_BUILTINS_BUILTINS_H_

#include <v8/src/builtins/builtins.h>  // IWYU pragma: export

#include "qorai/components/qorai_page_graph/common/buildflags.h"

namespace v8 {
namespace internal {

#if BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH_WEBAPI_PROBES)
class BuiltinArguments;

void ReportBuiltinCallAndResponse(Isolate* isolate,
                                  const char* builtin_name,
                                  const BuiltinArguments& builtin_args,
                                  const Tagged<Object>& builtin_result);
#endif  // BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH_WEBAPI_PROBES)

}  // namespace internal
}  // namespace v8

#endif  // QORAI_CHROMIUM_SRC_V8_SRC_BUILTINS_BUILTINS_H_
