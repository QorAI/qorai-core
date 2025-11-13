// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_IOS_BROWSER_QORAI_SHIELDS_SETTINGS_BRIDGE_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_IOS_BROWSER_QORAI_SHIELDS_SETTINGS_BRIDGE_H_

#ifdef __cplusplus
#include "qorai/components/qorai_shields/ios/common/shields_settings.mojom.objc.h"
#else
#import "shields_settings.mojom.objc.h"
#endif

NS_SWIFT_NAME(QoraiShieldsSettings)
@protocol QoraiShieldsSettingsBridge

- (BOOL)qoraiShieldsEnabledFor:(NSURL*)url
    NS_SWIFT_NAME(isQoraiShieldsEnabled(for:));
- (void)setQoraiShieldsEnabled:(BOOL)isEnabled forURL:(NSURL*)url;

@property(nonatomic) QoraiShieldsAdBlockMode defaultAdBlockMode;
- (QoraiShieldsAdBlockMode)adBlockModeForURL:(NSURL*)url
    NS_SWIFT_NAME(adBlockMode(for:));
- (void)setAdBlockMode:(QoraiShieldsAdBlockMode)adBlockMode forURL:(NSURL*)url;

@property(nonatomic, getter=isBlockScriptsEnabledByDefault)
    BOOL blockScriptsEnabledByDefault;
- (BOOL)blockScriptsEnabledForURL:(NSURL*)url
    NS_SWIFT_NAME(isBlockScriptsEnabled(for:));
- (void)setBlockScriptsEnabled:(BOOL)isEnabled forURL:(NSURL*)url;

@property(nonatomic) QoraiShieldsFingerprintMode defaultFingerprintMode;
- (QoraiShieldsFingerprintMode)fingerprintModeForURL:(NSURL*)url
    NS_SWIFT_NAME(fingerprintMode(for:));
- (void)setFingerprintMode:(QoraiShieldsFingerprintMode)fingerprintMode
                    forURL:(NSURL*)url;

@property(nonatomic) QoraiShieldsAutoShredMode defaultAutoShredMode;
- (QoraiShieldsAutoShredMode)autoShredModeForURL:(NSURL*)url
    NS_SWIFT_NAME(autoShredMode(for:));
- (void)setAutoShredMode:(QoraiShieldsAutoShredMode)autoShredMode
                  forURL:(NSURL*)url;
@end

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_IOS_BROWSER_QORAI_SHIELDS_SETTINGS_BRIDGE_H_
