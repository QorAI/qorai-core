/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/importer/qorai_external_process_importer_host.h"

#include "base/check.h"
#include "qorai/browser/importer/qorai_importer_p3a.h"
#include "qorai/browser/importer/extensions_import_helpers.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/importer/importer_lock_dialog.h"

QoraiExternalProcessImporterHost::QoraiExternalProcessImporterHost()
    : weak_ptr_factory_(this) {}
QoraiExternalProcessImporterHost::~QoraiExternalProcessImporterHost() = default;

void QoraiExternalProcessImporterHost::NotifyImportEnded() {
  if (!cancelled_) {
    RecordImporterP3A(source_profile_.importer_type);
  }

  // If user chooses extension importing, start importing extensions.
  // and NotifyImportEnded() will be called from OnGetChromeExtensionsList().
  // Handling extensions importing after finishing all other properties makes
  // logic simpler.
  // Don't import if cancelled.
#if BUILDFLAG(ENABLE_EXTENSIONS)
  if (NeedToImportExtensions() && extensions_importer_) {
    NotifyImportItemStarted(user_data_importer::EXTENSIONS);
    if (extensions_importer_->Import(base::BindRepeating(
            &QoraiExternalProcessImporterHost::OnExtensionImported,
            weak_ptr_factory_.GetWeakPtr()))) {
      return;
    }
  }
#endif
  // Force tests to fail if |this| is deleted.
  DCHECK(weak_ptr_factory_.GetWeakPtr());

  // Otherwise, notifying here and importing is finished.
  ExternalProcessImporterHost::NotifyImportEnded();
}

void QoraiExternalProcessImporterHost::LaunchImportIfReady() {
#if BUILDFLAG(ENABLE_EXTENSIONS)
  if (NeedToImportExtensions()) {
    if (!extensions_importer_) {
      extensions_importer_ =
          std::make_unique<extensions_import::ExtensionsImporter>(
              source_profile_.source_path, profile_);
      extensions_importer_->Prepare(base::BindOnce(
          &QoraiExternalProcessImporterHost::OnExtensionsImportReady,
          weak_ptr_factory_.GetWeakPtr()));
      return;
    }
    if (!extensions_import_ready_) {
      return;
    }
  }
#endif

  if (!do_not_launch_import_for_testing_) {
    CHECK(!client_);
    ExternalProcessImporterHost::LaunchImportIfReady();
  } else {
    NotifyImportEnded();
  }
}

void QoraiExternalProcessImporterHost::DoNotLaunchImportForTesting() {
  do_not_launch_import_for_testing_ = true;
}

void QoraiExternalProcessImporterHost::NotifyImportEndedForTesting() {
  ExternalProcessImporterHost::NotifyImportEnded();
}

importer::ImporterProgressObserver*
QoraiExternalProcessImporterHost::GetObserverForTesting() {
  return observer_;
}

#if BUILDFLAG(ENABLE_EXTENSIONS)

bool QoraiExternalProcessImporterHost::NeedToImportExtensions() const {
  return !cancelled_ && (items_ & user_data_importer::EXTENSIONS) ==
                            user_data_importer::EXTENSIONS;
}

void QoraiExternalProcessImporterHost::OnExtensionsImportReady(bool ready) {
  if (cancelled_) {
    return;
  }
  if (!ready) {
    extensions_importer_.reset();
    importer::ShowImportLockDialog(
        parent_view_, parent_window_,
        base::BindOnce(
            &QoraiExternalProcessImporterHost::OnExtensionsImportLockDialogEnd,
            weak_ptr_factory_.GetWeakPtr()),
        IDS_EXTENSIONS_IMPORTER_LOCK_TITLE, IDS_EXTENSIONS_IMPORTER_LOCK_TEXT);
  } else {
    extensions_import_ready_ = true;
    LaunchImportIfReady();
  }
}

void QoraiExternalProcessImporterHost::OnExtensionsImportLockDialogEnd(
    bool is_continue) {
  DCHECK(!extensions_importer_);
  if (is_continue) {
    LaunchImportIfReady();
  } else {
    NotifyImportEnded();
  }
}

void QoraiExternalProcessImporterHost::OnExtensionImported(
    const std::string& extension_id,
    extensions_import::ExtensionImportStatus status) {
  if (!extensions_importer_ || !extensions_importer_->IsImportInProgress()) {
    extensions_importer_.reset();
    if (observer_) {
      NotifyImportItemEnded(user_data_importer::EXTENSIONS);
    }
    ExternalProcessImporterHost::NotifyImportEnded();
  }
}

#endif
