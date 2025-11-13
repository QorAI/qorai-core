// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_CONTAINERS_CONTAINER_MODEL_H_
#define QORAI_BROWSER_UI_CONTAINERS_CONTAINER_MODEL_H_

#include <string>

#include "qorai/components/containers/core/mojom/containers.mojom.h"
#include "ui/base/models/image_model.h"

namespace containers {

// A model for view that represents a container in the UI.
class ContainerModel {
 public:
  ContainerModel(mojom::ContainerPtr container, float scale_factor);
  ContainerModel(const ContainerModel&) = delete;
  ContainerModel& operator=(const ContainerModel&) = delete;
  ContainerModel(ContainerModel&& other) noexcept;
  ContainerModel& operator=(ContainerModel&& other) noexcept;
  ~ContainerModel();

  const std::string& id() const { return container_->id; }
  const std::string& name() const { return container_->name; }
  const ui::ImageModel& icon() const { return icon_; }
  const mojom::ContainerPtr& container() const { return container_; }

 private:
  mojom::ContainerPtr container_;

  // An icon representing the `container_`. Each container can have its icon.
  // This icon can be used by UI, such as menus and tabs.
  ui::ImageModel icon_;
};

}  // namespace containers

#endif  // QORAI_BROWSER_UI_CONTAINERS_CONTAINER_MODEL_H_
