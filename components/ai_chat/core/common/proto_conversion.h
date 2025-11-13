// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_PROTO_CONVERSION_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_PROTO_CONVERSION_H_

#include "qorai/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/common.mojom.h"
#include "qorai/components/ai_chat/core/proto/store.pb.h"

namespace ai_chat {

COMPONENT_EXPORT(AI_CHAT_COMMON)
mojom::WebSourcesEventPtr DeserializeWebSourcesEvent(
    const store::WebSourcesEventProto& proto_event);

COMPONENT_EXPORT(AI_CHAT_COMMON)
void SerializeWebSourcesEvent(const mojom::WebSourcesEventPtr& mojom_event,
                              store::WebSourcesEventProto* proto_event);

COMPONENT_EXPORT(AI_CHAT_COMMON)
mojom::ToolUseEventPtr DeserializeToolUseEvent(
    const store::ToolUseEventProto& proto_event);

COMPONENT_EXPORT(AI_CHAT_COMMON)
bool SerializeToolUseEvent(const mojom::ToolUseEventPtr& mojom_event,
                           store::ToolUseEventProto* proto_event);

COMPONENT_EXPORT(AI_CHAT_COMMON)
mojom::SkillEntryPtr DeserializeSkillEntry(
    const store::SkillEntryProto& proto_entry);

COMPONENT_EXPORT(AI_CHAT_COMMON)
void SerializeSkillEntry(const mojom::SkillEntryPtr& mojom_entry,
                         store::SkillEntryProto* proto_entry);

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_PROTO_CONVERSION_H_
