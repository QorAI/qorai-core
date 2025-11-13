/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_SERVICE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_SERVICE_H_

namespace chrome {
namespace android {
class QoraiComponentUpdaterAndroid;
}
}  // namespace chrome

namespace qorai_component_updater {
class QoraiOnDemandUpdater;
}

#define QORAI_COMPONENT_UPDATER_SERVICE_H_ \
  friend class ::chrome::android::QoraiComponentUpdaterAndroid;

#define QORAI_COMPONENT_UPDATER_SERVICE_H_ON_DEMAND_UPDATER               \
 private:                                                                 \
  friend class qorai_component_updater::QoraiOnDemandUpdater;             \
                                                                          \
  virtual void EnsureInstalled(const std::string& id, Callback callback); \
  virtual void OnDemandUpdate(const std::vector<std::string>& ids,        \
                              Priority priority, Callback callback);      \
                                                                          \
 public:

#include <components/component_updater/component_updater_service.h>  // IWYU pragma: export

#undef QORAI_COMPONENT_UPDATER_SERVICE_H_ON_DEMAND_UPDATER
#undef QORAI_COMPONENT_UPDATER_SERVICE_H_

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_SERVICE_H_
