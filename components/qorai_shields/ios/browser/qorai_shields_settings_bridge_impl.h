// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_IOS_BROWSER_QORAI_SHIELDS_SETTINGS_BRIDGE_IMPL_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_IOS_BROWSER_QORAI_SHIELDS_SETTINGS_BRIDGE_IMPL_H_

#import <Foundation/Foundation.h>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_shields/ios/browser/qorai_shields_settings_bridge.h"
#include "qorai/components/qorai_shields/ios/common/shields_settings.mojom.objc.h"

NS_ASSUME_NONNULL_BEGIN

namespace qorai_shields {
class QoraiShieldsSettingsService;
}

@interface QoraiShieldsSettingsBridgeImpl
    : NSObject <QoraiShieldsSettingsBridge>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithQoraiShieldsSettings:
    (raw_ptr<qorai_shields::QoraiShieldsSettingsService>)qoraiShieldsSettings;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_IOS_BROWSER_QORAI_SHIELDS_SETTINGS_BRIDGE_IMPL_H_
