/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_H_

#include <string>

#include "base/functional/callback.h"

namespace qorai_ads {

using ShowScheduledCaptchaCallback =
    base::OnceCallback<void(const std::string& payment_id,
                            const std::string& captcha_id)>;
using SnoozeScheduledCaptchaCallback = base::OnceCallback<void()>;

class AdsTooltipsDelegate {
 public:
  virtual ~AdsTooltipsDelegate() = default;

  // Called to show the captcha tooltip.
  virtual void ShowCaptchaTooltip(
      const std::string& payment_id,
      const std::string& captcha_id,
      bool include_cancel_button,
      ShowScheduledCaptchaCallback show_captcha_callback,
      SnoozeScheduledCaptchaCallback snooze_captcha_callback) = 0;

  // Called to close the captcha tooltip.
  virtual void CloseCaptchaTooltip() = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_TOOLTIPS_ADS_TOOLTIPS_DELEGATE_H_
