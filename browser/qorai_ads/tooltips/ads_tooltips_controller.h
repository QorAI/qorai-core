/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_TOOLTIPS_CONTROLLER_H_
#define QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_TOOLTIPS_CONTROLLER_H_

#include <string>

#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_delegate.h"
#include "qorai/components/qorai_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace qorai_ads {

class AdsTooltipsController final
    : public AdsTooltipsDelegate,
      public qorai_tooltips::QoraiTooltipDelegate {
 public:
  AdsTooltipsController();

  AdsTooltipsController(const AdsTooltipsController&) = delete;
  AdsTooltipsController& operator=(const AdsTooltipsController&) = delete;

  ~AdsTooltipsController() override;

  // AdsTooltipDelegate:
  void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) override;
  void CloseCaptchaTooltip() override;

 private:
  // qorai_tooltips::QoraiTooltipDelegate:
  void OnTooltipWidgetDestroyed(const std::string& tooltip_id) override;

  base::WeakPtr<qorai_tooltips::QoraiTooltipDelegate> AsWeakPtr() override;

  base::WeakPtrFactory<QoraiTooltipDelegate> weak_ptr_factory_{this};
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_TOOLTIPS_CONTROLLER_H_
