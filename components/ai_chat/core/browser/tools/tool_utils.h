// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_TOOLS_TOOL_UTILS_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_TOOLS_TOOL_UTILS_H_

#include <string>
#include <vector>

#include "qorai/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "qorai/components/ai_chat/core/common/mojom/common.mojom.h"
#include "url/gurl.h"

namespace ai_chat {

std::vector<mojom::ContentBlockPtr> CreateContentBlocksForText(
    const std::string& text);

std::vector<mojom::ContentBlockPtr> CreateContentBlocksForImage(
    const GURL& image_url);

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_BROWSER_TOOLS_TOOL_UTILS_H_
