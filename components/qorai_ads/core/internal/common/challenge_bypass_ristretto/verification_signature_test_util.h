/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_SIGNATURE_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_SIGNATURE_TEST_UTIL_H_

namespace qorai_ads::cbr {

class VerificationSignature;

namespace test {

VerificationSignature GetVerificationSignature();
VerificationSignature GetInvalidVerificationSignature();

}  // namespace test

}  // namespace qorai_ads::cbr

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_VERIFICATION_SIGNATURE_TEST_UTIL_H_
