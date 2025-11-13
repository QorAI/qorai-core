// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_APP_QORAI_PROFILE_CONTROLLER_PRIVATE_H_
#define QORAI_IOS_APP_QORAI_PROFILE_CONTROLLER_PRIVATE_H_

#include "base/memory/raw_ptr.h"
#include "qorai/ios/app/qorai_profile_controller.h"

class ScopedProfileKeepAliveIOS;

@interface QoraiProfileController (Private)
- (instancetype)initWithProfileKeepAlive:
    (ScopedProfileKeepAliveIOS)profileKeepAlive;
@end

#endif  // QORAI_IOS_APP_QORAI_PROFILE_CONTROLLER_PRIVATE_H_
