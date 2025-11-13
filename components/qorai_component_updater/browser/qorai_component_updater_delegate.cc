/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_component_updater/browser/qorai_component_updater_delegate.h"

#include "base/task/sequenced_task_runner.h"
#include "base/task/thread_pool.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component_installer.h"
#include "qorai/components/qorai_component_updater/browser/qorai_on_demand_updater.h"
#include "components/component_updater/component_updater_service.h"
#include "components/prefs/pref_service.h"

using qorai_component_updater::QoraiComponent;
using qorai_component_updater::QoraiOnDemandUpdater;
using component_updater::ComponentUpdateService;

namespace qorai_component_updater {

namespace {

void RegisterComponent(component_updater::ComponentUpdateService* cus,
                       const std::string& name,
                       const std::string& base64_public_key,
                       base::OnceClosure registered_callback,
                       QoraiComponent::ReadyCallback ready_callback) {
  auto installer = base::MakeRefCounted<component_updater::ComponentInstaller>(
      std::make_unique<QoraiComponentInstallerPolicy>(
          name, base64_public_key, std::move(ready_callback)));
  installer->Register(cus, std::move(registered_callback));
}

}  // namespace

QoraiComponentUpdaterDelegate::QoraiComponentUpdaterDelegate(
    ComponentUpdateService* component_updater,
    PrefService* local_state,
    const std::string& locale)
    : component_updater_(
          raw_ref<ComponentUpdateService>::from_ptr(component_updater)),
      local_state_(raw_ref<PrefService>::from_ptr(local_state)),
      locale_(locale),
      task_runner_(base::ThreadPool::CreateSequencedTaskRunner(
          {base::MayBlock(), base::TaskPriority::USER_BLOCKING,
           base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN})) {}

QoraiComponentUpdaterDelegate::~QoraiComponentUpdaterDelegate() = default;

void QoraiComponentUpdaterDelegate::Register(
    const std::string& component_name,
    const std::string& component_base64_public_key,
    base::OnceClosure registered_callback,
    QoraiComponent::ReadyCallback ready_callback) {
  if (!QoraiOnDemandUpdater::GetInstance()->is_component_update_disabled()) {
    RegisterComponent(base::to_address(component_updater_), component_name,
                      component_base64_public_key,
                      std::move(registered_callback),
                      std::move(ready_callback));
  }
}

bool QoraiComponentUpdaterDelegate::Unregister(
    const std::string& component_id) {
  return component_updater_->UnregisterComponent(component_id);
}

void QoraiComponentUpdaterDelegate::EnsureInstalled(
    const std::string& component_id) {
  QoraiOnDemandUpdater::GetInstance()->EnsureInstalled(component_id);
}

void QoraiComponentUpdaterDelegate::AddObserver(ComponentObserver* observer) {
  component_updater_->AddObserver(observer);
}

void QoraiComponentUpdaterDelegate::RemoveObserver(
    ComponentObserver* observer) {
  component_updater_->RemoveObserver(observer);
}

scoped_refptr<base::SequencedTaskRunner>
QoraiComponentUpdaterDelegate::GetTaskRunner() {
  return task_runner_;
}

const std::string& QoraiComponentUpdaterDelegate::locale() const {
  return locale_;
}

PrefService* QoraiComponentUpdaterDelegate::local_state() {
  return base::to_address(local_state_);
}

}  // namespace qorai_component_updater
