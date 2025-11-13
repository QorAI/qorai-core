/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_CONSTANTS_QORAI_SERVICES_KEY_HELPER_H_
#define QORAI_COMPONENTS_CONSTANTS_QORAI_SERVICES_KEY_HELPER_H_

class GURL;

namespace qorai {

bool ShouldAddQoraiServicesKeyHeader(const GURL& url);

}  // namespace qorai

#endif  // QORAI_COMPONENTS_CONSTANTS_QORAI_SERVICES_KEY_HELPER_H_
