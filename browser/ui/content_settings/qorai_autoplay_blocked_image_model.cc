/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/content_settings/qorai_autoplay_blocked_image_model.h"

#include <memory>

#include "qorai/browser/ui/content_settings/qorai_autoplay_content_setting_bubble_model.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "components/content_settings/browser/page_specific_content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"

using content::WebContents;

QoraiAutoplayBlockedImageModel::QoraiAutoplayBlockedImageModel()
    : ContentSettingSimpleImageModel(ImageType::MEDIASTREAM,
                                     ContentSettingsType::AUTOPLAY) {}

bool QoraiAutoplayBlockedImageModel::UpdateAndGetVisibility(
    WebContents* web_contents) {
  if (!web_contents)
    return false;

  content_settings::PageSpecificContentSettings* content_settings =
      content_settings::PageSpecificContentSettings::GetForFrame(
          web_contents->GetPrimaryMainFrame());
  if (!content_settings)
    return false;
  if (!content_settings->IsContentBlocked(content_type()))
    return false;

  SetIcon(ContentSettingsType::AUTOPLAY, /*blocked=*/true);
  set_explanatory_string_id(IDS_BLOCKED_AUTOPLAY_TITLE);
  set_tooltip(l10n_util::GetStringUTF16(IDS_BLOCKED_AUTOPLAY_TITLE));
  return true;
}

std::unique_ptr<ContentSettingBubbleModel>
QoraiAutoplayBlockedImageModel::CreateBubbleModelImpl(
    ContentSettingBubbleModel::Delegate* delegate,
    content::WebContents* web_contents) {
  return std::make_unique<QoraiAutoplayContentSettingBubbleModel>(delegate,
                                                                  web_contents);
}
