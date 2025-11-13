// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_PREF_NAMES_H_

namespace qorai_adaptive_captcha {
namespace prefs {

inline constexpr char kScheduledCaptchaId[] =
    "qorai.rewards.scheduled_captcha.id";
inline constexpr char kScheduledCaptchaPaymentId[] =
    "qorai.rewards.scheduled_captcha.payment_id";
inline constexpr char kScheduledCaptchaSnoozeCount[] =
    "qorai.rewards.scheduled_captcha.snooze_count";
inline constexpr char kScheduledCaptchaFailedAttempts[] =
    "qorai.rewards.scheduled_captcha.failed_attempts";
inline constexpr char kScheduledCaptchaPaused[] =
    "qorai.rewards.scheduled_captcha.paused";

}  // namespace prefs
}  // namespace qorai_adaptive_captcha

#endif  // QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_PREF_NAMES_H_
