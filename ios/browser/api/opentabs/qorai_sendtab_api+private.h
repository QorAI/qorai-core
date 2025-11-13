/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_OPENTABS_QORAI_SENDTAB_API_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_OPENTABS_QORAI_SENDTAB_API_PRIVATE_H_

#import <Foundation/Foundation.h>

#include "qorai/ios/browser/api/opentabs/qorai_sendtab_api.h"

NS_ASSUME_NONNULL_BEGIN

namespace send_tab_to_self {
class SendTabToSelfSyncService;
}  // namespace send_tab_to_self

@interface QoraiSendTabAPI (Private)
- (instancetype)initWithSyncService:
    (send_tab_to_self::SendTabToSelfSyncService*)syncService;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_OPENTABS_QORAI_SENDTAB_API_PRIVATE_H_
