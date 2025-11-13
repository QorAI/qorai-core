// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "features.h"

#include "base/memory/raw_ptr.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_component_updater/browser/features.h"
#include "qorai/components/qorai_news/common/features.h"
#include "qorai/components/qorai_origin/features.h"
#include "qorai/components/qorai_rewards/core/features.h"
#include "qorai/components/qorai_search/common/features.h"
#include "qorai/components/qorai_search_conversion/features.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_sync/features.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "qorai/components/qorai_wallet/common/buildflags.h"
#include "qorai/components/qorai_wallet/common/features.h"
#include "qorai/components/de_amp/common/features.h"
#include "qorai/components/debounce/core/common/features.h"
#include "qorai/components/ntp_background_images/browser/features.h"
#include "qorai/components/p3a/features.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/skus/common/features.h"
#include "qorai/ios/browser/api/translate/features.h"
#include "qorai/ios/browser/qorai_wallet/features.h"
#include "qorai/ios/browser/ui/commerce/features.h"
#include "qorai/ios/browser/ui/tab_tray/features.h"
#include "qorai/ios/browser/ui/web_view/features.h"
#include "qorai/ios/browser/ui/webui/ai_chat/features.h"
#import "build/blink_buildflags.h"
#include "build/build_config.h"
#include "net/base/features.h"

@interface Feature () {
  raw_ptr<const base::Feature> _feature;
}
@end

@implementation Feature
- (instancetype)initWithFeature:(const base::Feature*)feature {
  if ((self = [super init])) {
    _feature = feature;
  }
  return self;
}

- (NSString*)name {
  return base::SysUTF8ToNSString(_feature->name);
}

- (bool)enabled {
  return base::FeatureList::IsEnabled(std::cref(*_feature));
}

//- (void)setEnabled:(bool)enabled {
//  std::vector<base::FeatureList::FeatureOverrideInfo> overrides = {
//    {
//        std::cref(*_value), enabled ?
//        base::FeatureList::OverrideState::OVERRIDE_ENABLE_FEATURE :
//        base::FeatureList::OverrideState::OVERRIDE_DISABLE_FEATURE
//    }
//  };
//  base::FeatureList::GetInstance()->RegisterExtraFeatureOverrides(overrides);
//}
@end

@implementation FeatureList

// MARK: - Qorai Features

+ (Feature*)kAIChat {
  return [[Feature alloc] initWithFeature:&ai_chat::features::kAIChat];
}

+ (Feature*)kAIChatHistory {
  return [[Feature alloc] initWithFeature:&ai_chat::features::kAIChatHistory];
}

+ (Feature*)kAdblockOverrideRegexDiscardPolicy {
  return
      [[Feature alloc] initWithFeature:&qorai_shields::features::
                                           kAdblockOverrideRegexDiscardPolicy];
}

+ (Feature*)kAllowUnsupportedWalletProvidersFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_rewards::features::
                          kAllowUnsupportedWalletProvidersFeature];
}

+ (Feature*)kQoraiAdblockCnameUncloaking {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiAdblockCnameUncloaking];
}

+ (Feature*)kQoraiAdblockCollapseBlockedElements {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::
                          kQoraiAdblockCollapseBlockedElements];
}

+ (Feature*)kQoraiAdblockCookieListDefault {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiAdblockCookieListDefault];
}

+ (Feature*)kQoraiAdblockCosmeticFiltering {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiAdblockCosmeticFiltering];
}

+ (Feature*)kQoraiAdblockCspRules {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiAdblockCspRules];
}

+ (Feature*)kQoraiAdblockDefault1pBlocking {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiAdblockDefault1pBlocking];
}

+ (Feature*)kQoraiAdblockMobileNotificationsListDefault {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::
                          kQoraiAdblockMobileNotificationsListDefault];
}

+ (Feature*)kQoraiAdblockScriptletDebugLogs {
  return [[Feature alloc] initWithFeature:&qorai_shields::features::
                                              kQoraiAdblockScriptletDebugLogs];
}

+ (Feature*)kQoraiDarkModeBlock {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiDarkModeBlock];
}

+ (Feature*)kQoraiDeAMP {
  return [[Feature alloc] initWithFeature:&de_amp::features::kQoraiDeAMP];
}

+ (Feature*)kQoraiDebounce {
  return [[Feature alloc] initWithFeature:&debounce::features::kQoraiDebounce];
}

+ (Feature*)kQoraiDomainBlock {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiDomainBlock];
}

+ (Feature*)kQoraiDomainBlock1PES {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiDomainBlock1PES];
}

+ (Feature*)kQoraiLocalhostAccessPermission {
  return [[Feature alloc] initWithFeature:&qorai_shields::features::
                                              kQoraiLocalhostAccessPermission];
}

+ (Feature*)kQoraiNTPBrandedWallpaper {
  return [[Feature alloc] initWithFeature:&ntp_background_images::features::
                                              kQoraiNTPBrandedWallpaper];
}

+ (Feature*)kQoraiNTPBrandedWallpaperSurveyPanelist {
  return [[Feature alloc]
      initWithFeature:&ntp_background_images::features::
                          kQoraiNTPBrandedWallpaperSurveyPanelist];
}

+ (Feature*)kQoraiNewsCardPeekFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_news::features::kQoraiNewsCardPeekFeature];
}

+ (Feature*)kQoraiNewsFeedUpdate {
  return [[Feature alloc]
      initWithFeature:&qorai_news::features::kQoraiNewsFeedUpdate];
}

+ (Feature*)kQoraiReduceLanguage {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiReduceLanguage];
}

+ (Feature*)kQoraiSearchDefaultAPIFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_search::features::kQoraiSearchDefaultAPIFeature];
}

+ (Feature*)kQoraiShredFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiShredFeature];
}

+ (Feature*)kQoraiShredCacheData {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiShredCacheData];
}

+ (Feature*)kQoraiShieldsContentSettings {
  return [[Feature alloc] initWithFeature:&qorai_shields::features::
                                              kQoraiShieldsContentSettingsIOS];
}

+ (Feature*)kQoraiIOSDebugAdblock {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiIOSDebugAdblock];
}

+ (Feature*)kQoraiIOSEnableFarblingPlugins {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kQoraiIOSEnableFarblingPlugins];
}

+ (Feature*)kQoraiShowStrictFingerprintingMode {
  return
      [[Feature alloc] initWithFeature:&qorai_shields::features::
                                           kQoraiShowStrictFingerprintingMode];
}

+ (Feature*)kQoraiSync {
  return [[Feature alloc] initWithFeature:&qorai_sync::features::kQoraiSync];
}

+ (Feature*)kQoraiWalletAnkrBalancesFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_wallet::features::kQoraiWalletAnkrBalancesFeature];
}

+ (Feature*)kQoraiWalletBitcoinFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_wallet::features::kQoraiWalletBitcoinFeature];
}

+ (Feature*)kQoraiWalletZCashFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_wallet::features::kQoraiWalletZCashFeature];
}

+ (Feature*)kConstellationEnclaveAttestation {
  return [[Feature alloc]
      initWithFeature:&p3a::features::kConstellationEnclaveAttestation];
}

+ (Feature*)kCosmeticFilteringExtraPerfMetrics {
  return
      [[Feature alloc] initWithFeature:&qorai_shields::features::
                                           kCosmeticFilteringExtraPerfMetrics];
}

+ (Feature*)kCosmeticFilteringJsPerformance {
  return [[Feature alloc] initWithFeature:&qorai_shields::features::
                                              kCosmeticFilteringJsPerformance];
}

+ (Feature*)kCosmeticFilteringSyncLoad {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kCosmeticFilteringSyncLoad];
}

+ (Feature*)kQoraiAccount {
  return
      [[Feature alloc] initWithFeature:&qorai_account::features::kQoraiAccount];
}

#if BUILDFLAG(ENABLE_GEMINI_WALLET)
+ (Feature*)kGeminiFeature {
  return [[Feature alloc] initWithFeature:&kGeminiFeature];
}
#else
+ (Feature*)kGeminiFeature {
  return nil;
}
#endif

+ (Feature*)kNTP {
  return [[Feature alloc]
      initWithFeature:&qorai_search_conversion::features::kNTP];
}

+ (Feature*)kNativeQoraiWalletFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_wallet::features::kNativeQoraiWalletFeature];
}

+ (Feature*)kSkusFeature {
  return [[Feature alloc] initWithFeature:&skus::features::kSkusFeature];
}

+ (Feature*)kUseDevUpdaterUrl {
  return [[Feature alloc]
      initWithFeature:&qorai_component_updater::kUseDevUpdaterUrl];
}

+ (Feature*)kVerboseLoggingFeature {
  return [[Feature alloc]
      initWithFeature:&qorai_rewards::features::kVerboseLoggingFeature];
}

+ (Feature*)kQoraiHttpsByDefault {
  return [[Feature alloc] initWithFeature:&net::features::kQoraiHttpsByDefault];
}

+ (Feature*)kBlockAllCookiesToggle {
  return [[Feature alloc]
      initWithFeature:&qorai_shields::features::kBlockAllCookiesToggle];
}

+ (Feature*)kQoraiTranslateEnabled {
  return [[Feature alloc]
      initWithFeature:&qorai::features::kQoraiTranslateEnabled];
}

+ (Feature*)kQoraiAppleTranslateEnabled {
  return [[Feature alloc]
      initWithFeature:&qorai::features::kQoraiAppleTranslateEnabled];
}

+ (Feature*)kUseQoraiUserAgent {
  return [[Feature alloc]
      initWithFeature:&qorai_user_agent::features::kUseQoraiUserAgent];
}

+ (Feature*)kUseChromiumWebViews {
  return
      [[Feature alloc] initWithFeature:&qorai::features::kUseChromiumWebViews];
}

+ (Feature*)kQoraiAllowExternalPurchaseLinks {
  return [[Feature alloc]
      initWithFeature:&qorai::features::kQoraiAllowExternalPurchaseLinks];
}

+ (Feature*)kModernTabTrayEnabled {
  return
      [[Feature alloc] initWithFeature:&qorai::features::kModernTabTrayEnabled];
}

+ (Feature*)kQoraiWalletWebUIIOS {
  return [[Feature alloc]
      initWithFeature:&qorai_wallet::features::kQoraiWalletWebUIIOS];
}

+ (Feature*)kAIChatWebUIEnabled {
  return
      [[Feature alloc] initWithFeature:&ai_chat::features::kAIChatWebUIEnabled];
}

+ (Feature*)kQoraiSyncDefaultPasswords {
  return [[Feature alloc]
      initWithFeature:&qorai_sync::features::kQoraiSyncDefaultPasswords];
}

+ (Feature*)kWebKitAdvancedPrivacyProtections {
  return
      [[Feature alloc] initWithFeature:&qorai_shields::features::
                                           kWebKitAdvancedPrivacyProtections];
}

+ (Feature*)kQoraiOrigin {
  return
      [[Feature alloc] initWithFeature:&qorai_origin::features::kQoraiOrigin];
}

@end
