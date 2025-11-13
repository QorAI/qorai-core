/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_DELEGATE_H_

#include <string>

namespace base {
class FilePath;
}  // namespace base

namespace qorai_ads {

class ResourceComponentRegistrarDelegate {
 public:
  // Invoked when a resource component is registered.
  virtual void OnResourceComponentRegistered(
      const std::string& component_id,
      const base::FilePath& install_dir) = 0;

  // Invoked when a resource component is unregistered.
  virtual void OnResourceComponentUnregistered(
      const std::string& component_id) = 0;

 protected:
  virtual ~ResourceComponentRegistrarDelegate() = default;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_COMPONENT_UPDATER_RESOURCE_COMPONENT_REGISTRAR_DELEGATE_H_
