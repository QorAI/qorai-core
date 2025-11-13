/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { getLocale } from '$web-common/locale'
import '$web-common/strings'

import { QoraiNewsStrings } from 'gen/components/grit/qorai_components_webui_strings'
import { QoraiNewTabPageStrings } from 'gen/components/grit/qorai_components_webui_strings'

declare global {
  interface Strings {
    QoraiNewTabPageStrings: typeof QoraiNewTabPageStrings
  }
}

export type StringKey =
  'rewardsAdsViewedTooltip' |
  'rewardsFeatureText1' |
  'rewardsFeatureText2' |
  'rewardsPayoutCompletedText' |
  'rewardsPayoutProcessingText' |
  'rewardsTosUpdateButtonLabel' |
  'rewardsTosUpdateText' |
  'rewardsTosUpdateTitle' |
  'searchAskQoraDescription'

export function getString(
  key: StringKey | QoraiNewTabPageStrings | QoraiNewsStrings
) {
  return getLocale(key)
}
