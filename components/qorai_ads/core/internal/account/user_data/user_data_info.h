/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_USER_DATA_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_USER_DATA_INFO_H_

#include "base/values.h"

namespace qorai_ads {

struct UserDataInfo final {
  UserDataInfo();

  UserDataInfo(const UserDataInfo&);
  UserDataInfo& operator=(const UserDataInfo&);

  UserDataInfo(UserDataInfo&&) noexcept;
  UserDataInfo& operator=(UserDataInfo&&) noexcept;

  ~UserDataInfo();

  bool operator==(const UserDataInfo&) const = default;

  // User data that may change.
  base::Value::Dict dynamic;

  // User data that remains constant.
  base::Value::Dict fixed;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_USER_DATA_INFO_H_
