/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_NTP_BACKGROUND_IMAGES_NTP_BACKGROUND_IMAGE_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_NTP_BACKGROUND_IMAGES_NTP_BACKGROUND_IMAGE_PRIVATE_H_

#include "qorai/ios/browser/api/ntp_background_images/ntp_background_image.h"

NS_ASSUME_NONNULL_BEGIN

namespace ntp_background_images {
struct Background;
}  // namespace ntp_background_images

@interface NTPBackgroundImage (Private)
- (instancetype)initWithBackground:
    (const ntp_background_images::Background&)background;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_NTP_BACKGROUND_IMAGES_NTP_BACKGROUND_IMAGE_PRIVATE_H_
