/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_ENGINE_TEST_UTILS_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_ENGINE_TEST_UTILS_H_

#include <vector>

#include "qorai/components/ai_chat/core/browser/engine/engine_consumer.h"
#include "qorai/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/common.mojom.h"

namespace ai_chat {

// Returns the history with a modified server reply in edits.
std::vector<mojom::ConversationTurnPtr> GetHistoryWithModifiedReply();

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_ENGINE_TEST_UTILS_H_
