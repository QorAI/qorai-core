/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_SHELL_INTEGRATION_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_SHELL_INTEGRATION_H_

#define QORAI_DEFAULT_BROWSER_WORKER_H friend class QoraiDefaultBrowserWorker;

#include <chrome/browser/shell_integration.h>  // IWYU pragma: export

#undef QORAI_DEFAULT_BROWSER_WORKER_H

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_SHELL_INTEGRATION_H_
