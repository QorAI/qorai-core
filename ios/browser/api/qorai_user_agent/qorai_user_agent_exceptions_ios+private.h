// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_QORAI_USER_AGENT_QORAI_USER_AGENT_EXCEPTIONS_IOS_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_QORAI_USER_AGENT_QORAI_USER_AGENT_EXCEPTIONS_IOS_PRIVATE_H_

#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"
#include "qorai/ios/browser/api/qorai_user_agent/qorai_user_agent_exceptions_ios.h"

@interface QoraiUserAgentExceptionsIOS (Private)
- (instancetype)initWithQoraiUserAgentExceptions:
    (qorai_user_agent::QoraiUserAgentExceptions*)qoraiUserAgentExceptions;
@end

#endif  // QORAI_IOS_BROWSER_API_QORAI_USER_AGENT_QORAI_USER_AGENT_EXCEPTIONS_IOS_PRIVATE_H_
