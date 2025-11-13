/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_IMPORTER_QORAI_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
#define QORAI_BROWSER_IMPORTER_QORAI_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "qorai/common/importer/profile_import.mojom.h"
#include "chrome/browser/importer/external_process_importer_client.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

class QoraiExternalProcessImporterClient
    : public ExternalProcessImporterClient,
      public qorai::mojom::ProfileImportObserver {
 public:
  QoraiExternalProcessImporterClient(
      base::WeakPtr<ExternalProcessImporterHost> importer_host,
      const user_data_importer::SourceProfile& source_profile,
      uint16_t items,
      InProcessImporterBridge* bridge);

  QoraiExternalProcessImporterClient(
      const QoraiExternalProcessImporterClient&) = delete;
  QoraiExternalProcessImporterClient& operator=(
      const QoraiExternalProcessImporterClient&) = delete;

  // ExternalProcessImportClient overrides:
  void Start() override;
  void Cancel() override;
  void CloseMojoHandles() override;
  void OnImportItemFinished(
      user_data_importer::ImportItem import_item) override;

  // qorai::mojom::ProfileImportObserver overrides:
  void OnCreditCardImportReady(const std::u16string& name_on_card,
                               const std::u16string& expiration_month,
                               const std::u16string& expiration_year,
                               const std::u16string& decrypted_card_number,
                               const std::string& origin) override;

 protected:
  ~QoraiExternalProcessImporterClient() override;

 private:
  // Used to start and stop the actual qorai importer running in a different
  // process.
  mojo::Remote<qorai::mojom::ProfileImport> qorai_profile_import_;

  // Used to receive progress updates from the qorai importer.
  mojo::Receiver<qorai::mojom::ProfileImportObserver> qorai_receiver_{this};
};

#endif  // QORAI_BROWSER_IMPORTER_QORAI_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
