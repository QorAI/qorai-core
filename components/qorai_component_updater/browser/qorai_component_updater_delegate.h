/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_COMPONENT_UPDATER_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_COMPONENT_UPDATER_DELEGATE_H_

#include <string>

#include "base/component_export.h"
#include "base/functional/callback.h"
#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component.h"

namespace base {
class SequencedTaskRunner;
}

namespace component_updater {
class ComponentUpdateService;
}

class PrefService;

namespace qorai_component_updater {

class COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER) QoraiComponentUpdaterDelegate
    : public QoraiComponent::Delegate {
 public:
  QoraiComponentUpdaterDelegate(
      component_updater::ComponentUpdateService* updater,
      PrefService* local_state,
      const std::string& locale);
  QoraiComponentUpdaterDelegate(const QoraiComponentUpdaterDelegate&) = delete;
  QoraiComponentUpdaterDelegate& operator=(
      const QoraiComponentUpdaterDelegate&) = delete;
  ~QoraiComponentUpdaterDelegate() override;

  using ComponentObserver = update_client::UpdateClient::Observer;
  // qorai_component_updater::QoraiComponent::Delegate implementation
  void Register(const std::string& component_name,
                const std::string& component_base64_public_key,
                base::OnceClosure registered_callback,
                qorai_component_updater::QoraiComponent::ReadyCallback
                    ready_callback) override;
  bool Unregister(const std::string& component_id) override;
  void EnsureInstalled(const std::string& component_id) override;

  void AddObserver(ComponentObserver* observer) override;
  void RemoveObserver(ComponentObserver* observer) override;

  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() override;

  const std::string& locale() const override;
  PrefService* local_state() override;

 private:
  const raw_ref<component_updater::ComponentUpdateService> component_updater_;
  const raw_ref<PrefService> local_state_;
  std::string locale_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
};

}  // namespace qorai_component_updater

#endif  // QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_COMPONENT_UPDATER_DELEGATE_H_
