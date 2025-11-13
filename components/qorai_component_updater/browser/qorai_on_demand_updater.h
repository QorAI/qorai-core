/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_ON_DEMAND_UPDATER_H_
#define QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_ON_DEMAND_UPDATER_H_

#include <string>
#include <vector>

#include "base/component_export.h"
#include "base/functional/callback_helpers.h"
#include "components/component_updater/component_updater_service.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_component_updater {

class COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER) QoraiOnDemandUpdater {
 public:
  static QoraiOnDemandUpdater* GetInstance();

  QoraiOnDemandUpdater(const QoraiOnDemandUpdater&) = delete;
  QoraiOnDemandUpdater& operator=(const QoraiOnDemandUpdater&) = delete;

  component_updater::OnDemandUpdater* RegisterOnDemandUpdater(
      bool is_component_update_disabled,
      component_updater::OnDemandUpdater* on_demand_updater);

  // Install the component with the given id. If the component is already
  // installed, do nothing.
  void EnsureInstalled(
      const std::string& id,
      component_updater::Callback callback = base::DoNothing());

  void OnDemandUpdate(const std::string& id,
                      component_updater::OnDemandUpdater::Priority priority,
                      component_updater::Callback callback = base::DoNothing());

  void OnDemandUpdate(const std::vector<std::string>& ids,
                      component_updater::OnDemandUpdater::Priority priority,
                      component_updater::Callback callback = base::DoNothing());

  bool is_component_update_disabled() { return is_component_update_disabled_; }

 private:
  friend base::NoDestructor<QoraiOnDemandUpdater>;
  QoraiOnDemandUpdater();
  ~QoraiOnDemandUpdater();

  raw_ptr<component_updater::OnDemandUpdater, DanglingUntriaged>
      on_demand_updater_ = nullptr;
  bool is_component_update_disabled_ = false;
};

}  // namespace qorai_component_updater

#endif  // QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_ON_DEMAND_UPDATER_H_
