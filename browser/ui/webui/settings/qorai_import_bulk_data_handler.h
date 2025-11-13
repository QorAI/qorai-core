/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_IMPORT_BULK_DATA_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_IMPORT_BULK_DATA_HANDLER_H_

#include <memory>
#include <optional>

#include "base/containers/flat_set.h"
#include "base/functional/callback.h"
#include "base/memory/weak_ptr.h"
#include "qorai/browser/ui/webui/settings/qorai_import_data_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_importer_observer.h"
#include "build/build_config.h"

namespace settings {

// This class handles bulk requests to import multiple profiles to
// new target Qorai profiles.
class QoraiImportBulkDataHandler : public QoraiImportDataHandler {
 public:
  QoraiImportBulkDataHandler();
  ~QoraiImportBulkDataHandler() override;

  using ProfileReadyCallback = base::OnceCallback<void(Profile* profile)>;

  QoraiImportBulkDataHandler(const QoraiImportBulkDataHandler&) = delete;
  QoraiImportBulkDataHandler& operator=(const QoraiImportBulkDataHandler&) =
      delete;

 protected:
  void HandleImportDataBulk(const base::Value::List& args);

  std::optional<int> GetProfileIndex(
      const user_data_importer::SourceProfile& source_profile);

  void PrepareProfile(const std::u16string& name,
                      ProfileReadyCallback callback);

  void ProfileReadyForImport(
      const user_data_importer::SourceProfile& source_profile,
      uint16_t imported_items,
      Profile* profile);
  // QoraiImportDataHandler
  void NotifyImportProgress(
      const user_data_importer::SourceProfile& source_profile,
      const base::Value::Dict& info) override;
  void OnImportEnded(
      const user_data_importer::SourceProfile& source_profile) override;

  // SettingsPageUIHandler
  void RegisterMessages() override;

  // ImportDataHandler overrides:
  void StartImport(const user_data_importer::SourceProfile& source_profile,
                   uint16_t imported_items) override;

 private:
  base::flat_set<int> importing_profiles_;
  base::WeakPtrFactory<QoraiImportBulkDataHandler> weak_factory_{this};
};

}  // namespace settings

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_IMPORT_BULK_DATA_HANDLER_H_
