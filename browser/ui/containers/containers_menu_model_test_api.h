// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_CONTAINERS_CONTAINERS_MENU_MODEL_TEST_API_H_
#define QORAI_BROWSER_UI_CONTAINERS_CONTAINERS_MENU_MODEL_TEST_API_H_

#include <vector>

#include "qorai/browser/ui/containers/container_model.h"
#include "qorai/browser/ui/containers/containers_menu_model.h"

namespace containers::test {

class ContainersMenuModelTestApi {
 public:
  static ContainersMenuModel CreateContainersMenuModel(
      ContainersMenuModel::Delegate& delegate,
      std::vector<ContainerModel> containers);

  // Returns the items in the menu model.
  static const std::vector<ContainerModel>& GetItems(
      const ContainersMenuModel& model);

  // Returns the command ID for the item at the given index.
  static int GetCommandIdFromItemIndex(const ContainersMenuModel& model,
                                       int index);

  // Returns item index from the command ID.
  static int GetItemIndexFromCommandId(const ContainersMenuModel& model,
                                       int command_id);
};

}  // namespace containers::test

#endif  // QORAI_BROWSER_UI_CONTAINERS_CONTAINERS_MENU_MODEL_TEST_API_H_
