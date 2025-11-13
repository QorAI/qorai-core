/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_PASSWORD_QORAI_PASSWORD_API_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_PASSWORD_QORAI_PASSWORD_API_PRIVATE_H_

#import <Foundation/Foundation.h>

#include "qorai/ios/browser/api/password/qorai_password_api.h"

NS_ASSUME_NONNULL_BEGIN

namespace password_manager {
class PasswordStoreInterface;
}

@interface QoraiPasswordAPI (Private)
- (instancetype)initWithPasswordStore:
    (scoped_refptr<password_manager::PasswordStoreInterface>)passwordStore;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_PASSWORD_QORAI_PASSWORD_API_PRIVATE_H_
