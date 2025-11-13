// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_DE_AMP_DE_AMP_PREFS_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_DE_AMP_DE_AMP_PREFS_PRIVATE_H_

#include "qorai/ios/browser/api/de_amp/de_amp_prefs.h"

class PrefService;

@interface DeAmpPrefs (Private)
- (instancetype)initWithProfileState:(PrefService*)profileState;
@end

#endif  // QORAI_IOS_BROWSER_API_DE_AMP_DE_AMP_PREFS_PRIVATE_H_
