/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_DELEGATE_H_

#include <string>

namespace qorai_adaptive_captcha {

class QoraiAdaptiveCaptchaDelegate {
 public:
  virtual ~QoraiAdaptiveCaptchaDelegate() = default;

  virtual bool ShowScheduledCaptcha(const std::string& payment_id,
                                    const std::string& captcha_id) = 0;
};

}  // namespace qorai_adaptive_captcha

#endif  // QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_DELEGATE_H_
