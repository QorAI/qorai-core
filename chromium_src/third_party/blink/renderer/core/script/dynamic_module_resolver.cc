/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_page_graph/common/buildflags.h"
#include "qorai/v8/include/v8-isolate-page-graph-utils.h"
#include "third_party/blink/renderer/core/probe/core_probes.h"

#define QORAI_DYNAMIC_MODULE_RESOLVER_RESOLVE_DYNAMICALLY               \
  IF_BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH, {                               \
    if (CoreProbeSink::HasAgentsGlobal(CoreProbeSink::kPageGraph)) {    \
      options.SetDOMNodeId(referrer_info.GetDOMNodeId());               \
      options.SetParentScriptId(                                        \
          v8::page_graph::GetExecutingScript(v8::Isolate::GetCurrent()) \
              .script_id);                                              \
    }                                                                   \
  })

#include <third_party/blink/renderer/core/script/dynamic_module_resolver.cc>

#undef QORAI_DYNAMIC_MODULE_RESOLVER_RESOLVE_DYNAMICALLY
