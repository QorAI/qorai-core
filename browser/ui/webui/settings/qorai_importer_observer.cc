/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_importer_observer.h"

#include <utility>

#include "base/check.h"
#include "chrome/browser/importer/external_process_importer_host.h"

QoraiImporterObserver::QoraiImporterObserver(
    ExternalProcessImporterHost* importer_host,
    const user_data_importer::SourceProfile& source_profile,
    uint16_t imported_items,
    ReportProgressCallback callback)
    : source_profile_(source_profile),
      imported_items_(imported_items),
      callback_(std::move(callback)),
      importer_host_(importer_host) {
  DCHECK(importer_host);
  importer_host->set_observer(this);
}

QoraiImporterObserver::~QoraiImporterObserver() {
  if (importer_host_)
    importer_host_->set_observer(nullptr);
}

// importer::ImporterProgressObserver:
void QoraiImporterObserver::ImportStarted() {
  if (import_started_called_)
    return;
  import_started_called_ = true;
  base::Value::Dict data;
  data.Set("importer_name", source_profile_.importer_name);
  data.Set("importer_type", source_profile_.importer_type);
  data.Set("items_to_import", imported_items_);
  data.Set("event", "ImportStarted");
  callback_.Run(source_profile_, data);
}

void QoraiImporterObserver::ImportItemStarted(
    user_data_importer::ImportItem item) {
  base::Value::Dict data;
  data.Set("importer_name", source_profile_.importer_name);
  data.Set("importer_type", source_profile_.importer_type);
  data.Set("items_to_import", imported_items_);
  data.Set("event", "ImportItemStarted");
  data.Set("item", item);
  callback_.Run(source_profile_, data);
}

void QoraiImporterObserver::ImportItemEnded(
    user_data_importer::ImportItem item) {
  base::Value::Dict data;
  data.Set("importer_name", source_profile_.importer_name);
  data.Set("importer_type", source_profile_.importer_type);
  data.Set("items_to_import", imported_items_);
  data.Set("event", "ImportItemEnded");
  data.Set("item", item);
  callback_.Run(source_profile_, data);
}

void QoraiImporterObserver::ImportEnded() {
  base::Value::Dict data;
  data.Set("importer_name", source_profile_.importer_name);
  data.Set("importer_type", source_profile_.importer_type);
  data.Set("items_to_import", imported_items_);
  data.Set("event", "ImportEnded");

  DCHECK(importer_host_);
  if (importer_host_)
    importer_host_->set_observer(nullptr);

  importer_host_ = nullptr;

  callback_.Run(source_profile_, data);
}

ExternalProcessImporterHost*
QoraiImporterObserver::GetImporterHostForTesting() {
  return importer_host_.get();
}
