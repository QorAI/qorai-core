/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_CONTENT_SETTINGS_QORAI_AUTOPLAY_BLOCKED_IMAGE_MODEL_H_
#define QORAI_BROWSER_UI_CONTENT_SETTINGS_QORAI_AUTOPLAY_BLOCKED_IMAGE_MODEL_H_

#include <memory>

#include "chrome/browser/ui/content_settings/content_setting_image_model.h"

class QoraiAutoplayBlockedImageModel : public ContentSettingSimpleImageModel {
 public:
  QoraiAutoplayBlockedImageModel();
  QoraiAutoplayBlockedImageModel(const QoraiAutoplayBlockedImageModel&) =
      delete;
  QoraiAutoplayBlockedImageModel& operator=(
      const QoraiAutoplayBlockedImageModel&) = delete;
  bool UpdateAndGetVisibility(content::WebContents* web_contents) override;
  std::unique_ptr<ContentSettingBubbleModel> CreateBubbleModelImpl(
      ContentSettingBubbleModel::Delegate* delegate,
      content::WebContents* web_contents) override;
};

#endif  // QORAI_BROWSER_UI_CONTENT_SETTINGS_QORAI_AUTOPLAY_BLOCKED_IMAGE_MODEL_H_
