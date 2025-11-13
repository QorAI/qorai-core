/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_QORAI_REWARDS_REWARDS_CLIENT_BRIDGE_H_
#define QORAI_IOS_BROWSER_API_QORAI_REWARDS_REWARDS_CLIENT_BRIDGE_H_

#import <Foundation/Foundation.h>

#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/mojom/rewards_engine.mojom.h"

NS_ASSUME_NONNULL_BEGIN

@protocol RewardsClientBridge
@required

- (void)onReconcileComplete:(qorai_rewards::mojom::Result)result
               contribution:
                   (qorai_rewards::mojom::ContributionInfoPtr)contribution;
- (void)onPanelPublisherInfo:(qorai_rewards::mojom::Result)result
               publisherInfo:
                   (qorai_rewards::mojom::PublisherInfoPtr)publisherInfo
                    windowId:(uint64_t)windowId;
- (void)
    fetchFavIcon:(const std::string&)url
      faviconKey:(const std::string&)faviconKey
        callback:
            (qorai_rewards::mojom::RewardsEngineClient::FetchFavIconCallback)
                callback;
- (void)loadUrl:(qorai_rewards::mojom::UrlRequestPtr)request
       callback:
           (qorai_rewards::mojom::RewardsEngineClient::LoadURLCallback)callback;
- (void)publisherListNormalized:
    (std::vector<qorai_rewards::mojom::PublisherInfoPtr>)list;
- (void)onPublisherRegistryUpdated;
- (void)onPublisherUpdated:(const std::string&)publisherId;
- (void)userPreferenceValue:(const std::string&)path
                   callback:(qorai_rewards::mojom::RewardsEngineClient::
                                 GetUserPreferenceValueCallback)callback;
- (void)setUserPreferenceValue:(const std::string&)path
                         value:(base::Value)value
                      callback:(qorai_rewards::mojom::RewardsEngineClient::
                                    SetUserPreferenceValueCallback)callback;
- (void)clearUserPreferenceValue:(const std::string&)path
                        callback:(qorai_rewards::mojom::RewardsEngineClient::
                                      ClearUserPreferenceValueCallback)callback;
- (void)showNotification:(const std::string&)type
                    args:(std::vector<std::string>)args
                callback:(qorai_rewards::mojom::RewardsEngineClient::
                              ShowNotificationCallback)callback;
- (void)reconcileStampReset;
- (void)runDbTransaction:(qorai_rewards::mojom::DBTransactionPtr)transaction
                callback:(qorai_rewards::mojom::RewardsEngineClient::
                              RunDBTransactionCallback)callback;
- (void)updateCreatorPrefixStore:
            (qorai_rewards::mojom::HashPrefixDataPtr)prefix_data
                        callback:(qorai_rewards::mojom::RewardsEngineClient::
                                      UpdateCreatorPrefixStoreCallback)callback;
- (void)creatorPrefixStoreContains:(const std::string&)value
                          callback:
                              (qorai_rewards::mojom::RewardsEngineClient::
                                   CreatorPrefixStoreContainsCallback)callback;
- (void)log:(const std::string&)file
            line:(int32_t)line
    verboseLevel:(int32_t)verboseLevel
         message:(const std::string&)message;
- (void)clearAllNotifications;
- (void)externalWalletConnected;
- (void)externalWalletLoggedOut;
- (void)externalWalletReconnected;
- (void)externalWalletDisconnected;
- (void)deleteLog:
    (qorai_rewards::mojom::RewardsEngineClient::DeleteLogCallback)callback;
- (void)
    encryptString:(const std::string&)value
         callback:
             (qorai_rewards::mojom::RewardsEngineClient::EncryptStringCallback)
                 callback;
- (void)
    decryptString:(const std::string&)value
         callback:
             (qorai_rewards::mojom::RewardsEngineClient::DecryptStringCallback)
                 callback;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_REWARDS_REWARDS_CLIENT_BRIDGE_H_
