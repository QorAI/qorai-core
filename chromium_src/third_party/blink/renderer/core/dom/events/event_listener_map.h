/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_DOM_EVENTS_EVENT_LISTENER_MAP_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_DOM_EVENTS_EVENT_LISTENER_MAP_H_

#include "qorai/components/qorai_page_graph/common/buildflags.h"

#if BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH)
#define CopyEventListenersNotCreatedFromMarkupToTarget      \
  NotUsed();                                                \
  static bool AddListenerToVector(                          \
      EventListenerVector* vector, EventListener* listener, \
      const AddEventListenerOptionsResolved* options,       \
      RegisteredEventListener** registered_listener);       \
  void CopyEventListenersNotCreatedFromMarkupToTarget
#endif  // BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH)

#include <third_party/blink/renderer/core/dom/events/event_listener_map.h>  // IWYU pragma: export

#if BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH)
#undef CopyEventListenersNotCreatedFromMarkupToTarget
#endif  // BUILDFLAG(ENABLE_QORAI_PAGE_GRAPH)

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_DOM_EVENTS_EVENT_LISTENER_MAP_H_
