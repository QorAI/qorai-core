/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_CAPTCHA_TOOLTIP_H_
#define QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_CAPTCHA_TOOLTIP_H_

#include <string>

#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_attributes.h"
#include "qorai/components/qorai_ads/browser/tooltips/ads_tooltips_delegate.h"

namespace qorai_ads {

inline constexpr char kScheduledCaptchaTooltipId[] = "scheduled-captcha";

class AdsCaptchaTooltip final : public qorai_tooltips::QoraiTooltip {
 public:
  AdsCaptchaTooltip(ShowScheduledCaptchaCallback show_captcha_callback,
                    SnoozeScheduledCaptchaCallback snooze_captcha_callback,
                    const qorai_tooltips::QoraiTooltipAttributes& attributes,
                    const std::string& payment_id,
                    const std::string& captcha_id);

  AdsCaptchaTooltip(const AdsCaptchaTooltip&) = delete;
  AdsCaptchaTooltip& operator=(const AdsCaptchaTooltip&) = delete;

  ~AdsCaptchaTooltip() override;

  const std::string& payment_id() const { return payment_id_; }
  const std::string& captcha_id() const { return captcha_id_; }

  // qorai_tooltips::QoraiTooltip:
  void PerformOkButtonAction() override;
  void PerformCancelButtonAction() override;

 private:
  ShowScheduledCaptchaCallback show_captcha_callback_;
  SnoozeScheduledCaptchaCallback snooze_captcha_callback_;
  std::string payment_id_;
  std::string captcha_id_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_TOOLTIPS_ADS_CAPTCHA_TOOLTIP_H_
