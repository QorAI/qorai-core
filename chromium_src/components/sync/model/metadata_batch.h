/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_MODEL_METADATA_BATCH_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_MODEL_METADATA_BATCH_H_

#define SetDataTypeState \
  ClearProgressToken();  \
  void SetDataTypeState

#include <components/sync/model/metadata_batch.h>  // IWYU pragma: export

#undef SetDataTypeState

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SYNC_MODEL_METADATA_BATCH_H_
