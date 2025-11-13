/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_BROWSING_DATA_CHROME_BROWSING_DATA_REMOVER_DELEGATE_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_BROWSING_DATA_CHROME_BROWSING_DATA_REMOVER_DELEGATE_H_

#include "build/build_config.h"

class QoraiBrowsingDataRemoverDelegate;

#define QORAI_CHROME_BROWSING_DATA_REMOVER_DELEGATE_H \
  friend class QoraiBrowsingDataRemoverDelegate;

#include <chrome/browser/browsing_data/chrome_browsing_data_remover_delegate.h>  // IWYU pragma: export
#undef QORAI_CHROME_BROWSING_DATA_REMOVER_DELEGATE_H

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_BROWSING_DATA_CHROME_BROWSING_DATA_REMOVER_DELEGATE_H_
