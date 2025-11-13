/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUPPORTED_SUBDIVISIONS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUPPORTED_SUBDIVISIONS_H_

#include <string>
#include <string_view>

#include "base/containers/flat_map.h"
#include "base/values.h"

namespace qorai_ads {

using SubdivisionMap = base::flat_map</*subdivision*/ std::string_view,
                                      /*name*/ std::string_view>;

using SupportedSubdivisionMap =
    base::flat_map</*country_code*/ std::string_view, SubdivisionMap>;

const SupportedSubdivisionMap& GetSupportedSubdivisions();

base::Value::List GetSupportedSubdivisionsAsValueList(
    const std::string& country_code);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUPPORTED_SUBDIVISIONS_H_
