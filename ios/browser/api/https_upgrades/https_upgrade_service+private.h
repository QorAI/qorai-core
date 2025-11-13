// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_HTTPS_UPGRADES_HTTPS_UPGRADE_SERVICE_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_HTTPS_UPGRADES_HTTPS_UPGRADE_SERVICE_PRIVATE_H_

#import <Foundation/Foundation.h>

#include "qorai/ios/browser/api/https_upgrades/https_upgrade_service.h"

class HttpsUpgradeService;

NS_ASSUME_NONNULL_BEGIN

@interface QoraiHttpsUpgradeService ()
- (instancetype)initWithHttpsUpgradeService:(HttpsUpgradeService*)service
    NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_HTTPS_UPGRADES_HTTPS_UPGRADE_SERVICE_PRIVATE_H_
