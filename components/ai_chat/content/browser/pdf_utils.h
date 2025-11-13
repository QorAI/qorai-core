/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_AI_CHAT_CONTENT_BROWSER_PDF_UTILS_H_
#define QORAI_COMPONENTS_AI_CHAT_CONTENT_BROWSER_PDF_UTILS_H_

namespace content {
class WebContents;
}  // namespace content

namespace ai_chat {

bool IsPdf(content::WebContents* web_contents);

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CONTENT_BROWSER_PDF_UTILS_H_
