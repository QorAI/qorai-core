/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_VALUE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_VALUE_UTIL_H_

#include "base/values.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_alias.h"

namespace qorai_ads {

base::Value::List DiagnosticsToValue(const DiagnosticMap& diagnostics);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_DIAGNOSTICS_DIAGNOSTIC_VALUE_UTIL_H_
