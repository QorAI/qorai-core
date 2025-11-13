/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_PADDED_IMAGE_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_PADDED_IMAGE_BUTTON_H_

#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/button/image_button.h"

namespace views {
class InkDrop;
}  // namespace views

namespace qorai_ads {

// PaddedImageButtons are ImageButtons whose image can be padded within the
// button. This allows the creation of buttons whose clickable areas extend
// beyond their image areas without the need to create and maintain
// corresponding resource images with alpha padding.
class PaddedImageButton final : public views::ImageButton {
  METADATA_HEADER(PaddedImageButton, views::ImageButton)
 public:

  explicit PaddedImageButton(PressedCallback callback);

  PaddedImageButton(const PaddedImageButton&) = delete;
  PaddedImageButton& operator=(const PaddedImageButton&) = delete;

  ~PaddedImageButton() override = default;

  void AdjustBorderInsetToFitHeight(int height);

  // views::ImageButton:
  void OnThemeChanged() override;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_PADDED_IMAGE_BUTTON_H_
