/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_TEST_UTIL_H_

namespace qorai_ads {

struct InlineContentAdInfo;

namespace test {

InlineContentAdInfo BuildInlineContentAd(bool should_generate_random_uuids);

InlineContentAdInfo BuildAndSaveInlineContentAd(
    bool should_generate_random_uuids);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_TEST_UTIL_H_
