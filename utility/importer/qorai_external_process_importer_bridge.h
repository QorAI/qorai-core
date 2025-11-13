/* Copyright 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_UTILITY_IMPORTER_QORAI_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_
#define QORAI_UTILITY_IMPORTER_QORAI_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_

#include <string>

#include "qorai/common/importer/qorai_importer_bridge.h"
#include "qorai/common/importer/profile_import.mojom.h"
#include "chrome/utility/importer/external_process_importer_bridge.h"

class QoraiExternalProcessImporterBridge : public ExternalProcessImporterBridge,
                                           public QoraiImporterBridge {
 public:
  QoraiExternalProcessImporterBridge(
      const base::flat_map<uint32_t, std::string>& localized_strings,
      mojo::SharedRemote<chrome::mojom::ProfileImportObserver> observer,
      mojo::SharedRemote<qorai::mojom::ProfileImportObserver> qorai_observer);

  QoraiExternalProcessImporterBridge(
      const QoraiExternalProcessImporterBridge&) = delete;
  QoraiExternalProcessImporterBridge& operator=(
      const QoraiExternalProcessImporterBridge&) = delete;

  void SetCreditCard(const std::u16string& name_on_card,
                     const std::u16string& expiration_month,
                     const std::u16string& expiration_year,
                     const std::u16string& decrypted_card_number,
                     const std::string& origin) override;

 private:
  ~QoraiExternalProcessImporterBridge() override;

  mojo::SharedRemote<qorai::mojom::ProfileImportObserver> qorai_observer_;
};

#endif  // QORAI_UTILITY_IMPORTER_QORAI_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_
