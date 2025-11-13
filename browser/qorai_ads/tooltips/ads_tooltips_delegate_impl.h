/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_IMPL_H_
#define QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_IMPL_H_

#include <string>

#include "qorai/browser/qorai_ads/tooltips/ads_tooltips_controller.h"
#include "qorai/components/qorai_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace qorai_ads {

class AdsTooltipsDelegateImpl : public AdsTooltipsDelegate {
 public:
  AdsTooltipsDelegateImpl();

  AdsTooltipsDelegateImpl(const AdsTooltipsDelegateImpl&) = delete;
  AdsTooltipsDelegateImpl& operator=(const AdsTooltipsDelegateImpl&) = delete;

  ~AdsTooltipsDelegateImpl() override = default;

  // AdsTooltipsDelegate:
  void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) override;
  void CloseCaptchaTooltip() override;

 private:
  AdsTooltipsController ads_tooltips_controller_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_IMPL_H_
