/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_component_updater/browser/qorai_on_demand_updater.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "base/check_is_test.h"
#include "base/command_line.h"
#include "base/functional/callback.h"  // IWYU pragma: keep
#include "base/no_destructor.h"

namespace qorai_component_updater {

namespace {
// This is a temporary workaround to preserve existing behavior for perf tests
constexpr char kAllowQoraiComponentUpdate[] = "allow-qorai-component-update";
}  // namespace

QoraiOnDemandUpdater* QoraiOnDemandUpdater::GetInstance() {
  static base::NoDestructor<QoraiOnDemandUpdater> instance;
  return instance.get();
}

QoraiOnDemandUpdater::QoraiOnDemandUpdater() = default;

QoraiOnDemandUpdater::~QoraiOnDemandUpdater() = default;

component_updater::OnDemandUpdater*
QoraiOnDemandUpdater::RegisterOnDemandUpdater(
    bool is_component_update_disabled,
    component_updater::OnDemandUpdater* on_demand_updater) {
  if (!on_demand_updater) {
    CHECK_IS_TEST();
  }
  bool allow_qorai_component_update =
      base::CommandLine::ForCurrentProcess()->HasSwitch(
          kAllowQoraiComponentUpdate);
  is_component_update_disabled_ =
      is_component_update_disabled && !allow_qorai_component_update;
  return std::exchange(on_demand_updater_, on_demand_updater);
}

void QoraiOnDemandUpdater::EnsureInstalled(
    const std::string& id,
    component_updater::Callback callback) {
  CHECK(on_demand_updater_);
  DCHECK(!is_component_update_disabled());
  on_demand_updater_->EnsureInstalled(id, std::move(callback));
}

void QoraiOnDemandUpdater::OnDemandUpdate(
    const std::string& id,
    component_updater::OnDemandUpdater::Priority priority,
    component_updater::Callback callback) {
  CHECK(on_demand_updater_);
  DCHECK(!is_component_update_disabled());
  on_demand_updater_->OnDemandUpdate(id, priority, std::move(callback));
}

void QoraiOnDemandUpdater::OnDemandUpdate(
    const std::vector<std::string>& ids,
    component_updater::OnDemandUpdater::Priority priority,
    component_updater::Callback callback) {
  CHECK(on_demand_updater_);
  DCHECK(!is_component_update_disabled());
  on_demand_updater_->OnDemandUpdate(ids, priority, std::move(callback));
}

}  // namespace qorai_component_updater
