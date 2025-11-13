// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_APP_QORAI_PROFILE_CONTROLLER_H_
#define QORAI_IOS_APP_QORAI_PROFILE_CONTROLLER_H_

#import <Foundation/Foundation.h>

@class QoraiBookmarksAPI, QoraiHistoryAPI, QoraiPasswordAPI, QoraiOpenTabsAPI,
    QoraiSendTabAPI, QoraiSyncAPI, QoraiSyncProfileServiceIOS, DeAmpPrefs,
    QoraiTabGeneratorAPI, QoraiWalletAPI, QoraiStats, AIChat,
    DefaultHostContentSettings, CWVWebViewConfiguration, WebImageDownloader,
    NTPBackgroundImagesService, QoraiWebViewConfiguration;
@protocol AIChatDelegate
, IpfsAPI, ProfileBridge;

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
@interface QoraiProfileController : NSObject
@property(readonly) id<ProfileBridge> profile;
@property(readonly) QoraiBookmarksAPI* bookmarksAPI;
@property(readonly) QoraiHistoryAPI* historyAPI;
@property(readonly) QoraiPasswordAPI* passwordAPI;
@property(readonly) QoraiOpenTabsAPI* openTabsAPI;
@property(readonly) QoraiSendTabAPI* sendTabAPI;
@property(readonly) QoraiSyncAPI* syncAPI;
@property(readonly) QoraiSyncProfileServiceIOS* syncProfileService;
@property(readonly) QoraiTabGeneratorAPI* tabGeneratorAPI;
@property(readonly) QoraiWalletAPI* qoraiWalletAPI;
@property(readonly) QoraiStats* qoraiStats;
@property(readonly) DeAmpPrefs* deAmpPrefs;
@property(readonly) id<IpfsAPI> ipfsAPI;
- (AIChat*)aiChatAPIWithDelegate:(id<AIChatDelegate>)delegate;
/// The default content settings for regular browsing windows
@property(readonly) DefaultHostContentSettings* defaultHostContentSettings;
@property(readonly) NTPBackgroundImagesService* backgroundImagesService;
@property(readonly) WebImageDownloader* webImageDownloader;

@property(readonly) QoraiWebViewConfiguration* defaultWebViewConfiguration;
@property(readonly)
    QoraiWebViewConfiguration* nonPersistentWebViewConfiguration;
- (void)notifyLastPrivateTabClosed;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_APP_QORAI_PROFILE_CONTROLLER_H_
