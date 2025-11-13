/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_WEB_IMAGE_WEB_IMAGE_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_WEB_IMAGE_WEB_IMAGE_PRIVATE_H_

#import <Foundation/Foundation.h>
#include "qorai/ios/browser/api/web_image/web_image.h"

class ProfileIOS;

@interface WebImageDownloader (Private)
- (instancetype)initWithBrowserState:(ProfileIOS*)profile;
@end

#endif  // QORAI_IOS_BROWSER_API_WEB_IMAGE_WEB_IMAGE_PRIVATE_H_
