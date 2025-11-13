/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_IMPORTER_QORAI_IMPORTER_P3A_H_
#define QORAI_BROWSER_IMPORTER_QORAI_IMPORTER_P3A_H_

#include "components/user_data_importer/common/importer_type.h"

// This mostly duplicates code in |importer_uma.cc| but we want better
// naming, better buckets and slightly different logic.
void RecordImporterP3A(user_data_importer::ImporterType type);

#endif  // QORAI_BROWSER_IMPORTER_QORAI_IMPORTER_P3A_H_
