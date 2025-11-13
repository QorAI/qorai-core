// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_FEATURES_FEATURES_H_
#define QORAI_IOS_BROWSER_API_FEATURES_FEATURES_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
@interface Feature : NSObject
@property(nonatomic, readonly) NSString* name;
@property(nonatomic, readonly) bool enabled;
@end

OBJC_EXPORT
@interface FeatureList : NSObject
// MARK: - Qorai Features

@property(class, nonatomic, readonly) Feature* kAIChat;
@property(class, nonatomic, readonly) Feature* kAIChatHistory;
@property(class, nonatomic, readonly)
    Feature* kAdblockOverrideRegexDiscardPolicy;
@property(class, nonatomic, readonly)
    Feature* kAllowUnsupportedWalletProvidersFeature;
@property(class, nonatomic, readonly) Feature* kQoraiAdblockCnameUncloaking;
@property(class, nonatomic, readonly)
    Feature* kQoraiAdblockCollapseBlockedElements;
@property(class, nonatomic, readonly) Feature* kQoraiAdblockCookieListDefault;
@property(class, nonatomic, readonly) Feature* kQoraiAdblockCosmeticFiltering;
@property(class, nonatomic, readonly) Feature* kQoraiAdblockCspRules;
@property(class, nonatomic, readonly) Feature* kQoraiAdblockDefault1pBlocking;
@property(class, nonatomic, readonly)
    Feature* kQoraiAdblockMobileNotificationsListDefault;
@property(class, nonatomic, readonly) Feature* kQoraiAdblockScriptletDebugLogs;
@property(class, nonatomic, readonly) Feature* kQoraiDarkModeBlock;
@property(class, nonatomic, readonly) Feature* kQoraiDeAMP;
@property(class, nonatomic, readonly) Feature* kQoraiDebounce;
@property(class, nonatomic, readonly) Feature* kQoraiDomainBlock;
@property(class, nonatomic, readonly) Feature* kQoraiDomainBlock1PES;
@property(class, nonatomic, readonly) Feature* kQoraiLocalhostAccessPermission;
@property(class, nonatomic, readonly) Feature* kQoraiNTPBrandedWallpaper;
@property(class, nonatomic, readonly)
    Feature* kQoraiNTPBrandedWallpaperSurveyPanelist;
@property(class, nonatomic, readonly) Feature* kQoraiNewsCardPeekFeature;
@property(class, nonatomic, readonly) Feature* kQoraiNewsFeedUpdate;
@property(class, nonatomic, readonly) Feature* kQoraiReduceLanguage;
@property(class, nonatomic, readonly) Feature* kQoraiSearchDefaultAPIFeature;
@property(class, nonatomic, readonly) Feature* kQoraiShredFeature;
@property(class, nonatomic, readonly) Feature* kQoraiShredCacheData;
@property(class, nonatomic, readonly) Feature* kQoraiShieldsContentSettings;
@property(class, nonatomic, readonly) Feature* kQoraiIOSDebugAdblock;
@property(class, nonatomic, readonly) Feature* kQoraiIOSEnableFarblingPlugins;
@property(class, nonatomic, readonly)
    Feature* kQoraiShowStrictFingerprintingMode;
@property(class, nonatomic, readonly) Feature* kQoraiSync;
@property(class, nonatomic, readonly) Feature* kQoraiWalletAnkrBalancesFeature;
@property(class, nonatomic, readonly) Feature* kQoraiWalletBitcoinFeature;
@property(class, nonatomic, readonly) Feature* kQoraiWalletZCashFeature;
@property(class, nonatomic, readonly) Feature* kConstellationEnclaveAttestation;
@property(class, nonatomic, readonly)
    Feature* kCosmeticFilteringExtraPerfMetrics;
@property(class, nonatomic, readonly) Feature* kCosmeticFilteringJsPerformance;
@property(class, nonatomic, readonly) Feature* kCosmeticFilteringSyncLoad;
@property(class, nonatomic, readonly) Feature* kQoraiAccount;
@property(class, nonatomic, readonly, nullable) Feature* kGeminiFeature;
@property(class, nonatomic, readonly) Feature* kNTP;
@property(class, nonatomic, readonly) Feature* kNativeQoraiWalletFeature;
@property(class, nonatomic, readonly) Feature* kSkusFeature;
@property(class, nonatomic, readonly) Feature* kUseDevUpdaterUrl;
@property(class, nonatomic, readonly) Feature* kVerboseLoggingFeature;
@property(class, nonatomic, readonly) Feature* kQoraiHttpsByDefault;
@property(class, nonatomic, readonly) Feature* kBlockAllCookiesToggle;
@property(class, nonatomic, readonly) Feature* kQoraiTranslateEnabled;
@property(class, nonatomic, readonly) Feature* kQoraiAppleTranslateEnabled;
@property(class, nonatomic, readonly) Feature* kUseQoraiUserAgent;
@property(class, nonatomic, readonly) Feature* kUseChromiumWebViews;
@property(class, nonatomic, readonly) Feature* kQoraiAllowExternalPurchaseLinks;
@property(class, nonatomic, readonly) Feature* kModernTabTrayEnabled;
@property(class, nonatomic, readonly) Feature* kQoraiWalletWebUIIOS;
@property(class, nonatomic, readonly) Feature* kAIChatWebUIEnabled;
@property(class, nonatomic, readonly) Feature* kQoraiSyncDefaultPasswords;
@property(class, nonatomic, readonly)
    Feature* kWebKitAdvancedPrivacyProtections;
@property(class, nonatomic, readonly) Feature* kQoraiOrigin;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_FEATURES_FEATURES_H_
