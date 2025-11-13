// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_AI_CHAT_AI_CHAT_SETTINGS_HELPER_H_
#define QORAI_IOS_BROWSER_AI_CHAT_AI_CHAT_SETTINGS_HELPER_H_

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#include "qorai/components/ai_chat/core/common/mojom/ios/ai_chat.mojom.objc.h"
#else
#include "ai_chat.mojom.objc.h"  // NOLINT
#endif

@protocol ProfileBridge;

NS_ASSUME_NONNULL_BEGIN

@protocol AIChatSettingsHelperDelegate
- (void)defaultModelChangedFromOldKey:(NSString*)oldKey toKey:(NSString*)toKey;
- (void)modelListUpdated;
@end

/// A helper which wraps access to methods that are used in the settings UI
@protocol AIChatSettingsHelper
/// A delegate to watch for updates to the models
@property(nonatomic, weak, nullable) id<AIChatSettingsHelperDelegate> delegate;
/// The set of available models
@property(readonly) NSArray<AiChatModel*>* models;
/// The current default model key being used
@property(nonatomic) NSString* defaultModelKey;
/// Fetch the premium status of the user
- (void)fetchPremiumStatus:(void (^)(AiChatPremiumStatus status,
                                     AiChatPremiumInfo* _Nullable info))handler;
@end

/// A concrete implementation of the AIChatSettingsHelper
OBJC_EXPORT
@interface AIChatSettingsHelperImpl : NSObject <AIChatSettingsHelper>
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithProfile:(id<ProfileBridge>)profile
    NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_AI_CHAT_AI_CHAT_SETTINGS_HELPER_H_
