/* Copyright 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_IMPORTER_QORAI_IN_PROCESS_IMPORTER_BRIDGE_H_
#define QORAI_BROWSER_IMPORTER_QORAI_IN_PROCESS_IMPORTER_BRIDGE_H_

#include <string>

#include "qorai/common/importer/qorai_importer_bridge.h"
#include "chrome/browser/importer/in_process_importer_bridge.h"

class QoraiInProcessImporterBridge : public InProcessImporterBridge,
                                     public QoraiImporterBridge {
 public:
  using InProcessImporterBridge::InProcessImporterBridge;

  QoraiInProcessImporterBridge(const QoraiInProcessImporterBridge&) = delete;
  QoraiInProcessImporterBridge operator=(
      const QoraiInProcessImporterBridge&) = delete;

  // QoraiImporterBridge overrides:
  void SetCreditCard(const std::u16string& name_on_card,
                     const std::u16string& expiration_month,
                     const std::u16string& expiration_year,
                     const std::u16string& decrypted_card_number,
                     const std::string& origin) override;

 private:
  ~QoraiInProcessImporterBridge() override;
};

#endif  // QORAI_BROWSER_IMPORTER_QORAI_IN_PROCESS_IMPORTER_BRIDGE_H_
