// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/ai_chat/ai_chat_utils.h"

#include "base/apple/foundation_util.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/ios/components/prefs/pref_service_bridge_impl.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"

@implementation AIChatUtils

+ (BOOL)isAIChatEnabledForPrefService:(id<PrefServiceBridge>)prefService {
  PrefServiceBridgeImpl* holder =
      base::apple::ObjCCastStrict<PrefServiceBridgeImpl>(prefService);
  return ai_chat::IsAIChatEnabled(holder.prefService);
}

@end
