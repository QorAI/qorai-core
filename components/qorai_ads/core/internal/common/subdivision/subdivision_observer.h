/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace qorai_ads {

class SubdivisionObserver : public base::CheckedObserver {
 public:
  // Invoked when the subdivision has updated.
  virtual void OnDidUpdateSubdivision(const std::string& subdivision) {}
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_OBSERVER_H_
