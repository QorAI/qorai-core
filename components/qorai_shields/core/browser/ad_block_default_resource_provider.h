// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_DEFAULT_RESOURCE_PROVIDER_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_DEFAULT_RESOURCE_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_resource_provider.h"

namespace component_updater {
class ComponentUpdateService;
}  // namespace component_updater

namespace base {
class FilePath;
}

class AdBlockServiceTest;

namespace qorai_shields {

class AdBlockDefaultResourceProvider : public AdBlockResourceProvider {
 public:
  explicit AdBlockDefaultResourceProvider(
      component_updater::ComponentUpdateService* cus);
  ~AdBlockDefaultResourceProvider() override;
  AdBlockDefaultResourceProvider(const AdBlockDefaultResourceProvider&) =
      delete;
  AdBlockDefaultResourceProvider& operator=(
      const AdBlockDefaultResourceProvider&) = delete;

  /// Returns the path to the resources file.
  base::FilePath GetResourcesPath();

  void LoadResources(
      base::OnceCallback<void(const std::string& resources_json)>) override;

 private:
  friend class ::AdBlockServiceTest;

  void OnComponentReady(const base::FilePath&);

  base::FilePath component_path_;

  base::WeakPtrFactory<AdBlockDefaultResourceProvider> weak_factory_{this};
};

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_AD_BLOCK_DEFAULT_RESOURCE_PROVIDER_H_
