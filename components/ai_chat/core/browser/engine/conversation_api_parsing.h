// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_ENGINE_CONVERSATION_API_PARSING_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_ENGINE_CONVERSATION_API_PARSING_H_

#include "base/values.h"
#include "qorai/components/ai_chat/core/browser/engine/conversation_api_client.h"

namespace ai_chat {

// Convert Content variant to appropriate JSON representation for sending to
// the Conversation API.
base::Value ContentBlocksToJson(const ConversationAPIClient::Content& content);

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_ENGINE_CONVERSATION_API_PARSING_H_
