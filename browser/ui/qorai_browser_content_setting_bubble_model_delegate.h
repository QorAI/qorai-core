/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_BROWSER_CONTENT_SETTING_BUBBLE_MODEL_DELEGATE_H_
#define QORAI_BROWSER_UI_QORAI_BROWSER_CONTENT_SETTING_BUBBLE_MODEL_DELEGATE_H_

#include "base/memory/raw_ref.h"
#include "chrome/browser/ui/browser_content_setting_bubble_model_delegate.h"

class BrowserWindowInterface;

class QoraiBrowserContentSettingBubbleModelDelegate
    : public BrowserContentSettingBubbleModelDelegate {
 public:
  explicit QoraiBrowserContentSettingBubbleModelDelegate(
      BrowserWindowInterface* browser);
  QoraiBrowserContentSettingBubbleModelDelegate(
      const QoraiBrowserContentSettingBubbleModelDelegate&) = delete;
  QoraiBrowserContentSettingBubbleModelDelegate& operator=(
      const QoraiBrowserContentSettingBubbleModelDelegate&) = delete;
  ~QoraiBrowserContentSettingBubbleModelDelegate() override;

  void ShowWidevineLearnMorePage();
  void ShowLearnMorePage(ContentSettingsType type) override;

 private:
  const raw_ref<BrowserWindowInterface> browser_;
};

#endif  // QORAI_BROWSER_UI_QORAI_BROWSER_CONTENT_SETTING_BUBBLE_MODEL_DELEGATE_H_
