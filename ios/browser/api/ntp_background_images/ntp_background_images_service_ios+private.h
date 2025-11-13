/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_NTP_BACKGROUND_IMAGES_NTP_BACKGROUND_IMAGES_SERVICE_IOS_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_NTP_BACKGROUND_IMAGES_NTP_BACKGROUND_IMAGES_SERVICE_IOS_PRIVATE_H_

#include "qorai/ios/browser/api/ntp_background_images/ntp_background_images_service_ios.h"

#include <memory>

namespace qorai_ads {
class AdsService;
}  // namespace qorai_ads

namespace ntp_background_images {
class NTPBackgroundImagesService;
}  // namespace ntp_background_images

@interface NTPBackgroundImagesService (Private)

- (instancetype)
    initWithBackgroundImagesService:
        (std::unique_ptr<ntp_background_images::NTPBackgroundImagesService>)
            service
                        ads_service:(qorai_ads::AdsService*)ads_service;

@end

#endif  // QORAI_IOS_BROWSER_API_NTP_BACKGROUND_IMAGES_NTP_BACKGROUND_IMAGES_SERVICE_IOS_PRIVATE_H_
