/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_QORAI_NETWORK_AUDIT_TEST_HELPER_H_
#define QORAI_BROWSER_NET_QORAI_NETWORK_AUDIT_TEST_HELPER_H_

#include <string>
#include <vector>

#include "base/files/file_util.h"

namespace qorai {
// Verify that the netlog file was written, appears to be well formed, and
// includes the requested level of data.
void VerifyNetworkAuditLog(
    const base::FilePath& net_log_path,
    const base::FilePath& audit_results_path,
    const std::vector<std::string>& extra_allowed_prefixes);
}  // namespace qorai

#endif  // QORAI_BROWSER_NET_QORAI_NETWORK_AUDIT_TEST_HELPER_H_
