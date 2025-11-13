/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_UTILS_H_
#define QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_UTILS_H_

#include "base/component_export.h"

class GURL;

namespace ai_chat {

COMPONENT_EXPORT(AI_CHAT_COMMON)
bool IsQoraiSearchURL(const GURL& url);

COMPONENT_EXPORT(AI_CHAT_COMMON)
bool IsOpenAIChatButtonFromQoraiSearchURL(const GURL& url);

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CORE_COMMON_UTILS_H_
