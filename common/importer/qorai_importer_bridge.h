/* Copyright 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMMON_IMPORTER_QORAI_IMPORTER_BRIDGE_H_
#define QORAI_COMMON_IMPORTER_QORAI_IMPORTER_BRIDGE_H_

#include <string>

class QoraiImporterBridge {
 public:
  virtual void SetCreditCard(const std::u16string& name_on_card,
                             const std::u16string& expiration_month,
                             const std::u16string& expiration_year,
                             const std::u16string& decrypted_card_number,
                             const std::string& origin) = 0;
};

#endif  // QORAI_COMMON_IMPORTER_QORAI_IMPORTER_BRIDGE_H_
