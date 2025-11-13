/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_component_updater/browser/mock_on_demand_updater.h"

#include "qorai/components/qorai_component_updater/browser/qorai_on_demand_updater.h"

namespace qorai_component_updater {

MockOnDemandUpdater::MockOnDemandUpdater() {
  prev_on_demand_updater_ =
      QoraiOnDemandUpdater::GetInstance()->RegisterOnDemandUpdater(false, this);
}

MockOnDemandUpdater::~MockOnDemandUpdater() {
  QoraiOnDemandUpdater::GetInstance()->RegisterOnDemandUpdater(
      false, prev_on_demand_updater_);
}

}  // namespace qorai_component_updater
