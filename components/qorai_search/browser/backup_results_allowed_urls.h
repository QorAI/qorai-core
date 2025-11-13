/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_BACKUP_RESULTS_ALLOWED_URLS_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_BACKUP_RESULTS_ALLOWED_URLS_H_

#include "url/gurl.h"

namespace qorai_search {

bool IsBackupResultURLAllowed(const GURL& url);

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_BACKUP_RESULTS_ALLOWED_URLS_H_
