/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_FEATURES_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_FEATURES_H_

#include <components/permissions/features.h>  // IWYU pragma: export

namespace permissions {
namespace features {

COMPONENT_EXPORT(PERMISSIONS_COMMON)
BASE_DECLARE_FEATURE(kPermissionLifetime);

}  // namespace features
}  // namespace permissions

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_PERMISSIONS_FEATURES_H_
