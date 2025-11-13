// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_BRIDGE_H_
#define QORAI_IOS_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_BRIDGE_H_

#import <Foundation/Foundation.h>

#include "keyed_service_factory_wrapper.h"  // NOLINT

@protocol QoraiShieldsSettingsBridge;

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
NS_SWIFT_NAME(QoraiShieldsSettingsServiceFactory)
@interface QoraiShieldsSettingsServiceFactoryBridge
    : KeyedServiceFactoryWrapper <id <QoraiShieldsSettingsBridge>>
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_BRIDGE_H_
