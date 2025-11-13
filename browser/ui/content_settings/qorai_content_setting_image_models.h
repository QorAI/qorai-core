/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_CONTENT_SETTINGS_QORAI_CONTENT_SETTING_IMAGE_MODELS_H_
#define QORAI_BROWSER_UI_CONTENT_SETTINGS_QORAI_CONTENT_SETTING_IMAGE_MODELS_H_

#include <memory>
#include <vector>

class ContentSettingImageModel;

void QoraiGenerateContentSettingImageModels(
    std::vector<std::unique_ptr<ContentSettingImageModel>>*);

#endif  // QORAI_BROWSER_UI_CONTENT_SETTINGS_QORAI_CONTENT_SETTING_IMAGE_MODELS_H_
