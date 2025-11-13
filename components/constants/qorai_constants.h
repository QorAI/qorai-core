/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_CONSTANTS_QORAI_CONSTANTS_H_
#define QORAI_COMPONENTS_CONSTANTS_QORAI_CONSTANTS_H_

#include "base/files/file_path.h"
#include "qorai/components/ai_chat/core/common/buildflags/buildflags.h"

namespace qorai {

extern const base::FilePath::CharType kSessionProfileDir[];

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
// Path to create the AI Chat agent profile
extern const base::FilePath::CharType kAIChatAgentProfileDir[];
#endif

}  // namespace qorai

#endif  // QORAI_COMPONENTS_CONSTANTS_QORAI_CONSTANTS_H_
