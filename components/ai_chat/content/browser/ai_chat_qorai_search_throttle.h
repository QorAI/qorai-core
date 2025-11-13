/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_AI_CHAT_CONTENT_BROWSER_AI_CHAT_QORAI_SEARCH_THROTTLE_H_
#define QORAI_COMPONENTS_AI_CHAT_CONTENT_BROWSER_AI_CHAT_QORAI_SEARCH_THROTTLE_H_

#include <optional>
#include <string>

#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/navigation_throttle.h"

namespace blink {
namespace mojom {
enum class PermissionStatus : int32_t;
}  // namespace mojom
}  // namespace blink

namespace content {
class WebContents;
}

namespace content {
struct PermissionResult;
}  // namespace content

class PrefService;

namespace ai_chat {
class AIChatService;

// A network throttle which intercepts Qorai Search requests.
// Currently the only use case is to intercept requests to open Qora AI chat, so
// it is only created when navigating to open Qora button URL from Qorai Search.
// It could be extended to other Qorai Search URLs in the future.
//
// For Open Qora feature, we check:
// 1) If AI chat is enabled.
// 2) If the request is from Qorai Search and is trying to navigate to open Qora
// button URL.
// 3) If the nonce property in the a tag element is equal to the one in url ref.
// 4) If the user has granted permission to open Qora.
// The navigation to the specific Open Qora URL will be cancelled, and Qora AI
// chat will be opened only if all the above conditions are met.
class AIChatQoraiSearchThrottle : public content::NavigationThrottle {
 public:
  AIChatQoraiSearchThrottle(
      base::OnceCallback<void(content::WebContents*)> open_qora_delegate,
      content::NavigationThrottleRegistry& registry,
      AIChatService* ai_chat_service);
  ~AIChatQoraiSearchThrottle() override;

  static void MaybeCreateAndAdd(
      base::OnceCallback<void(content::WebContents*)> open_qora_delegate,
      content::NavigationThrottleRegistry& registry,
      AIChatService* ai_chat_service,
      PrefService* pref_service);

  ThrottleCheckResult WillStartRequest() override;
  const char* GetNameForLogging() override;

 private:
  void OnGetOpenAIChatButtonNonce(const std::optional<std::string>& nonce);
  void OnPermissionPromptResult(content::PermissionResult status);
  void OnOpenAIChat();

  void OpenAIChatWithStagedEntries();

  base::OnceCallback<void(content::WebContents*)> open_ai_chat_delegate_;
  const raw_ptr<AIChatService> ai_chat_service_ = nullptr;

  base::WeakPtrFactory<AIChatQoraiSearchThrottle> weak_factory_{this};
};

}  // namespace ai_chat

#endif  // QORAI_COMPONENTS_AI_CHAT_CONTENT_BROWSER_AI_CHAT_QORAI_SEARCH_THROTTLE_H_
