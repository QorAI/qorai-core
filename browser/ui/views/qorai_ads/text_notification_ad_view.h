/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_TEXT_NOTIFICATION_AD_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_TEXT_NOTIFICATION_AD_VIEW_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "qorai/browser/ui/views/qorai_ads/notification_ad_view.h"

namespace views {
class Label;
class View;
}  // namespace views

namespace qorai_ads {

class NotificationAd;
class NotificationAdControlButtonsView;
class NotificationAdHeaderView;

class TextNotificationAdView final : public NotificationAdView {
 public:
  explicit TextNotificationAdView(const NotificationAd& notification_ad);

  TextNotificationAdView(const TextNotificationAdView&) = delete;
  TextNotificationAdView& operator=(const TextNotificationAdView&) = delete;

  ~TextNotificationAdView() override;

  // NotificationAdView:
  void UpdateContents(const NotificationAd& notification_ad) override;
  void OnThemeChanged() override;

 private:
  NotificationAd notification_ad_;

  void CreateView(const NotificationAd& notification_ad);

  std::unique_ptr<NotificationAdHeaderView> CreateHeaderView(
      const NotificationAd& notification_ad);

  std::unique_ptr<views::View> CreateBodyView(
      const NotificationAd& notification_ad);
  std::unique_ptr<views::Label> CreateBodyLabel(
      const NotificationAd& notification_ad);
  void UpdateBodyLabel();

  raw_ptr<views::Label> body_label_ = nullptr;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_TEXT_NOTIFICATION_AD_VIEW_H_
