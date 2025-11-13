/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_BASE_THREADING_THREAD_RESTRICTIONS_H_
#define QORAI_CHROMIUM_SRC_BASE_THREADING_THREAD_RESTRICTIONS_H_

class QoraiBrowsingDataRemoverDelegate;
namespace qorai {
class ProcessLauncher;
}

#define QORAI_SCOPED_ALLOW_BASE_SYNC_PRIMITIVES_H  \
  friend class ::QoraiBrowsingDataRemoverDelegate; \
  friend class qorai::ProcessLauncher;

#include <base/threading/thread_restrictions.h>  // IWYU pragma: export

#undef QORAI_SCOPED_ALLOW_BASE_SYNC_PRIMITIVES_H

#endif  // QORAI_CHROMIUM_SRC_BASE_THREADING_THREAD_RESTRICTIONS_H_
