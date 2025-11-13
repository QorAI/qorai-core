// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_CONTENT_SETTINGS_DEFAULT_HOST_CONTENT_SETTINGS_INTERNAL_H_
#define QORAI_IOS_BROWSER_API_CONTENT_SETTINGS_DEFAULT_HOST_CONTENT_SETTINGS_INTERNAL_H_

#include "qorai/ios/browser/api/content_settings/default_host_content_settings.h"

class HostContentSettingsMap;

@interface DefaultHostContentSettings ()
- (instancetype)initWithSettingsMap:(HostContentSettingsMap*)settingsMap
    NS_DESIGNATED_INITIALIZER;
@end

#endif  // QORAI_IOS_BROWSER_API_CONTENT_SETTINGS_DEFAULT_HOST_CONTENT_SETTINGS_INTERNAL_H_
