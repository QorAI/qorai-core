/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace qorai_ads {

class ResourceComponentObserver : public base::CheckedObserver {
 public:
  // Invoked when the resource for the given `id` has updated to
  // `manifest_version`.
  virtual void OnResourceComponentDidChange(const std::string& manifest_version,
                                            const std::string& id) = 0;

  // Invoked when the resource for the given `id` has been unregistered.
  virtual void OnDidUnregisterResourceComponent(const std::string& id) = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_OBSERVER_H_
