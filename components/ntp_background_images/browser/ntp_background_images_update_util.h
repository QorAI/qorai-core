/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_NTP_BACKGROUND_IMAGES_UPDATE_UTIL_H_
#define QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_NTP_BACKGROUND_IMAGES_UPDATE_UTIL_H_

#include <string>

namespace ntp_background_images {

void CheckAndUpdateSponsoredImagesComponent(const std::string& component_id);

}  // namespace ntp_background_images

#endif  // QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_BROWSER_NTP_BACKGROUND_IMAGES_UPDATE_UTIL_H_
