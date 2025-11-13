/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_HISTORY_QORAI_HISTORY_API_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_HISTORY_QORAI_HISTORY_API_PRIVATE_H_

#import <Foundation/Foundation.h>

#include "qorai/ios/browser/api/history/qorai_history_api.h"

NS_ASSUME_NONNULL_BEGIN

class ProfileIOS;

@interface QoraiHistoryAPI (Private)
- (instancetype)initWithBrowserState:(ProfileIOS*)profile;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_HISTORY_QORAI_HISTORY_API_PRIVATE_H_
