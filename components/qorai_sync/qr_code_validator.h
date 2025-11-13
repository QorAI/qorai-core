/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SYNC_QR_CODE_VALIDATOR_H_
#define QORAI_COMPONENTS_QORAI_SYNC_QR_CODE_VALIDATOR_H_

#include <string>

#include "base/time/time.h"

namespace qorai_sync {

enum class QrCodeDataValidationResult {
  kValid = 0,
  kNotWellFormed = 1,
  kVersionNotRecognized = 2,
  kVersionDeprecated = 3,
  kExpired = 4,
  kValidForTooLong = 5,
};

class QrCodeDataValidator {
 public:
  static QrCodeDataValidationResult ValidateQrDataJson(
      const std::string& qr_data_string);

  static base::Time GetQRv1SunsetDay();

 private:
  static bool IsValidSeedHex(const std::string& seed_hex);
  static base::Time qr_v1_sunset_day_;
};

}  // namespace qorai_sync

#endif  // QORAI_COMPONENTS_QORAI_SYNC_QR_CODE_VALIDATOR_H_
