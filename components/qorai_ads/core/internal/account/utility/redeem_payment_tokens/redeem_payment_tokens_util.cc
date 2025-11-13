/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_util.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_feature.h"
#include "qorai/components/qorai_ads/core/internal/common/random/random_util.h"
#include "qorai/components/qorai_ads/core/internal/flags/debug/debug_flag_util.h"
#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

namespace qorai_ads {

namespace {

constexpr base::TimeDelta kDebugRedeemPaymentTokensAfter = base::Minutes(2);
constexpr base::TimeDelta kMinimumDelayBeforeRedeemingTokens = base::Minutes(1);

base::Time NextTokenRedemptionAt() {
  return GetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt);
}

bool HasPreviouslyRedeemedTokens() {
  return !NextTokenRedemptionAt().is_null();
}

bool ShouldHaveRedeemedTokensInThePast() {
  return NextTokenRedemptionAt() < base::Time::Now();
}

}  // namespace

void SetNextTokenRedemptionAt(base::Time next_payment_token_redemption_at) {
  SetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt,
                     next_payment_token_redemption_at);
}

base::Time ScheduleNextTokenRedemptionAt() {
  return base::Time::Now() +
         (ShouldDebug() ? kDebugRedeemPaymentTokensAfter
                        : RandTimeDelta(kRedeemPaymentTokensAfter.Get()));
}

base::TimeDelta CalculateDelayBeforeRedeemingTokens() {
  if (!HasPreviouslyRedeemedTokens()) {
    return ScheduleNextTokenRedemptionAt() - base::Time::Now();
  }

  if (ShouldHaveRedeemedTokensInThePast()) {
    return kMinimumDelayBeforeRedeemingTokens;
  }

  const base::TimeDelta delay = NextTokenRedemptionAt() - base::Time::Now();
  if (delay < kMinimumDelayBeforeRedeemingTokens) {
    return kMinimumDelayBeforeRedeemingTokens;
  }

  return delay;
}

}  // namespace qorai_ads
