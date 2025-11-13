/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/utility/importer/qorai_profile_import_impl.h"

#include <memory>
#include <utility>

#include "base/check.h"
#include "base/command_line.h"
#include "base/functional/bind.h"
#include "base/location.h"
#include "base/notreached.h"
#include "base/task/single_thread_task_runner.h"
#include "base/threading/thread.h"
#include "qorai/utility/importer/qorai_external_process_importer_bridge.h"
#include "qorai/utility/importer/chrome_importer.h"
#include "build/build_config.h"
#include "chrome/common/importer/profile_import.mojom.h"
#include "chrome/utility/importer/external_process_importer_bridge.h"
#include "chrome/utility/importer/importer.h"
#include "components/user_data_importer/common/importer_type.h"
#include "content/public/utility/utility_thread.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "mojo/public/cpp/bindings/shared_remote.h"

namespace {

scoped_refptr<Importer> CreateImporterByType(
    user_data_importer::ImporterType type) {
  switch (type) {
    case user_data_importer::TYPE_CHROME:
      return new ChromeImporter();
    case user_data_importer::TYPE_EDGE_CHROMIUM:
      return new ChromeImporter();
    case user_data_importer::TYPE_VIVALDI:
      return new ChromeImporter();
    case user_data_importer::TYPE_OPERA:
      return new ChromeImporter();
    case user_data_importer::TYPE_YANDEX:
      return new ChromeImporter();
    case user_data_importer::TYPE_WHALE:
      return new ChromeImporter();
    default:
      break;
  }
  NOTREACHED() << "All handled for supported types above.";
}

}  // namespace

QoraiProfileImportImpl::QoraiProfileImportImpl(
    mojo::PendingReceiver<qorai::mojom::ProfileImport> receiver)
    : receiver_(this, std::move(receiver)) {}

QoraiProfileImportImpl::~QoraiProfileImportImpl() = default;

void QoraiProfileImportImpl::StartImport(
    const user_data_importer::SourceProfile& source_profile,
    uint16_t items,
    const base::flat_map<uint32_t, std::string>& localized_strings,
    mojo::PendingRemote<chrome::mojom::ProfileImportObserver> observer,
    mojo::PendingRemote<qorai::mojom::ProfileImportObserver> qorai_observer) {
  // Signal change to OSCrypt password for importing from Chrome/Chromium
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (source_profile.importer_name.starts_with(u"Chrome")) {
    command_line->AppendSwitch("import-chrome");
  } else if (source_profile.importer_type ==
             user_data_importer::TYPE_EDGE_CHROMIUM) {
    command_line->AppendSwitch("import-edge");
  } else if (source_profile.importer_name.starts_with(u"Chromium")) {
    command_line->AppendSwitch("import-chromium");
  } else if (source_profile.importer_type == user_data_importer::TYPE_OPERA) {
    command_line->AppendSwitch("import-opera");
  } else if (source_profile.importer_type == user_data_importer::TYPE_YANDEX) {
    command_line->AppendSwitch("import-yandex");
  } else if (source_profile.importer_type == user_data_importer::TYPE_WHALE) {
    command_line->AppendSwitch("import-whale");
  } else if (source_profile.importer_type == user_data_importer::TYPE_VIVALDI) {
    command_line->AppendSwitch("import-vivaldi");
  }

  content::UtilityThread::Get()->EnsureBlinkInitialized();
  importer_ = CreateImporterByType(source_profile.importer_type);
  if (!importer_.get()) {
    mojo::Remote<chrome::mojom::ProfileImportObserver>(std::move(observer))
        ->OnImportFinished(false, "Importer could not be created.");
    return;
  }

  items_to_import_ = items;

  // Create worker thread in which importer runs.
  import_thread_ = std::make_unique<base::Thread>("import_thread");
#if BUILDFLAG(IS_WIN)
  import_thread_->init_com_with_mta(false);
#endif
  CHECK(import_thread_->Start());
  bridge_ = new QoraiExternalProcessImporterBridge(
      localized_strings,
      mojo::SharedRemote<chrome::mojom::ProfileImportObserver>(
          std::move(observer)),
      mojo::SharedRemote<qorai::mojom::ProfileImportObserver>(
          std::move(qorai_observer)));
  import_thread_->task_runner()->PostTask(
      FROM_HERE,
      base::BindOnce(&Importer::StartImport, importer_, source_profile, items,
                     base::RetainedRef(bridge_)));
}

void QoraiProfileImportImpl::CancelImport() {
  ImporterCleanup();
}

void QoraiProfileImportImpl::ReportImportItemFinished(
    user_data_importer::ImportItem item) {
  items_to_import_ ^= item;  // Remove finished item from mask.
  if (items_to_import_ == 0) {
    ImporterCleanup();
  }
}

void QoraiProfileImportImpl::ImporterCleanup() {
  importer_->Cancel();
  importer_.reset();
  bridge_.reset();
  import_thread_.reset();
}
