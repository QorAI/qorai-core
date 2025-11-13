/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_PROFILE_ID_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_PROFILE_ID_H_

#include <string>

#include "base/files/file_path.h"

namespace qorai_origin {

// Creates a base64url encoded profile identifier for stable, safe identifier
std::string GetProfileId(const base::FilePath& profile_path);

}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_PROFILE_ID_H_
