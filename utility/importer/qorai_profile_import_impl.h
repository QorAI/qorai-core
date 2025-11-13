/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_UTILITY_IMPORTER_QORAI_PROFILE_IMPORT_IMPL_H_
#define QORAI_UTILITY_IMPORTER_QORAI_PROFILE_IMPORT_IMPL_H_

#include <memory>
#include <string>

#include "qorai/common/importer/profile_import.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"

class QoraiExternalProcessImporterBridge;
class Importer;

namespace base {
class Thread;
}  // namespace base

namespace importer {
struct SourceProfile;
}  // namespace importer

class QoraiProfileImportImpl : public qorai::mojom::ProfileImport {
 public:
  explicit QoraiProfileImportImpl(
      mojo::PendingReceiver<qorai::mojom::ProfileImport> receiver);
  ~QoraiProfileImportImpl() override;

  QoraiProfileImportImpl(const QoraiProfileImportImpl&) = delete;
  QoraiProfileImportImpl& operator=(const QoraiProfileImportImpl&) = delete;

 private:
  // qorai::mojom::ProfileImport overrides:
  void StartImport(
      const user_data_importer::SourceProfile& source_profile,
      uint16_t items,
      const base::flat_map<uint32_t, std::string>& localized_strings,
      mojo::PendingRemote<chrome::mojom::ProfileImportObserver> observer,
      mojo::PendingRemote<qorai::mojom::ProfileImportObserver> qorai_observer)
      override;
  void CancelImport() override;
  void ReportImportItemFinished(user_data_importer::ImportItem item) override;

  void ImporterCleanup();

  mojo::Receiver<qorai::mojom::ProfileImport> receiver_;
  std::unique_ptr<base::Thread> import_thread_;

  // Bridge object is passed to importer, so that it can send IPC calls
  // directly back to the ProfileImportProcessHost.
  scoped_refptr<QoraiExternalProcessImporterBridge> bridge_;

  // A bitmask of user_data_importer::ImportItem.
  uint16_t items_to_import_ = 0;

  // Importer of the appropriate type (Firefox, Safari, IE, etc.)
  scoped_refptr<Importer> importer_;
};

#endif  // QORAI_UTILITY_IMPORTER_QORAI_PROFILE_IMPORT_IMPL_H_
