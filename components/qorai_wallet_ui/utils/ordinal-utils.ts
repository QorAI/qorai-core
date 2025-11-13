// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { getLocale } from '../../common/locale'
import { unbiasedRandom } from './random-utils'

export const ORDINALS = {
  0: getLocale('qoraiWalletOrdinalFirst'),
  1: getLocale('qoraiWalletOrdinalSecond'),
  2: getLocale('qoraiWalletOrdinalThird'),
  3: getLocale('qoraiWalletOrdinalFourth'),
  4: getLocale('qoraiWalletOrdinalFifth'),
  5: getLocale('qoraiWalletOrdinalSixth'),
  6: getLocale('qoraiWalletOrdinalSeventh'),
  7: getLocale('qoraiWalletOrdinalEighth'),
  8: getLocale('qoraiWalletOrdinalNinth'),
  9: getLocale('qoraiWalletOrdinalTenth'),
  10: getLocale('qoraiWalletOrdinalEleventh'),
  11: getLocale('qoraiWalletOrdinalTwelfth'),
  12: getLocale('qoraiWalletOrdinalThirteenth'),
  13: getLocale('qoraiWalletOrdinalFourteenth'),
  14: getLocale('qoraiWalletOrdinalFifteenth'),
  15: getLocale('qoraiWalletOrdinalSixteenth'),
  16: getLocale('qoraiWalletOrdinalSeventeenth'),
  17: getLocale('qoraiWalletOrdinalEighteenth'),
  18: getLocale('qoraiWalletOrdinalNineteenth'),
  19: getLocale('qoraiWalletOrdinalTwentieth'),
  20: getLocale('qoraiWalletOrdinalTwentyFirst'),
  21: getLocale('qoraiWalletOrdinalTwentySecond'),
  22: getLocale('qoraiWalletOrdinalTwentyThird'),
  23: getLocale('qoraiWalletOrdinalTwentyFourth'),
}

const suffixes = new Map([
  ['one', getLocale('qoraiWalletOrdinalSuffixOne')],
  ['two', getLocale('qoraiWalletOrdinalSuffixTwo')],
  ['few', getLocale('qoraiWalletOrdinalSuffixFew')],
  ['other', getLocale('qoraiWalletOrdinalSuffixOther')],
])

export const formatOrdinals = (n: number) => {
  const pr = new Intl.PluralRules(navigator.language, { type: 'ordinal' })
  const rule = pr.select(n)
  const suffix = suffixes.get(rule)
  return `${n}${suffix}`
}

export const getWordIndicesToVerify = (_wordsLength: number): number[] => {
  if (_wordsLength < 3) {
    // phrase is not long enough (must be longer than 3 words)
    return [-3, -2, -1]
  }

  // limit randomness to first 24 words
  const wordsLength = _wordsLength > 24 ? 24 : _wordsLength

  // get next random index
  const indicesSet = new Set<number>([])

  while (indicesSet.size < 3) {
    const nextIndex = unbiasedRandom(0, wordsLength - 1)
    indicesSet.add(nextIndex)
  }

  return Array.from(indicesSet).sort((a, b) => a - b) // verify in order
}
