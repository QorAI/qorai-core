/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_SYNC_DRIVER_QORAI_SYNC_PROFILE_SERVICE_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_SYNC_DRIVER_QORAI_SYNC_PROFILE_SERVICE_PRIVATE_H_

#import <Foundation/Foundation.h>

#import "qorai/ios/browser/api/sync/driver/qorai_sync_profile_service.h"

NS_ASSUME_NONNULL_BEGIN

namespace syncer {
class SyncService;
}

@interface QoraiSyncProfileServiceIOS (Private)
- (instancetype)initWithProfileSyncService:(syncer::SyncService*)syncService;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_SYNC_DRIVER_QORAI_SYNC_PROFILE_SERVICE_PRIVATE_H_
