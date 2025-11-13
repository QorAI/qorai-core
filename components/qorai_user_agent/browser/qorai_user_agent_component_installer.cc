// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_component_installer.h"

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "base/functional/bind.h"
#include "base/functional/callback.h"
#include "qorai/components/qorai_component_updater/browser/qorai_on_demand_updater.h"
#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "components/component_updater/component_installer.h"
#include "components/component_updater/component_updater_service.h"
#include "crypto/sha2.h"

using qorai_component_updater::QoraiOnDemandUpdater;

namespace qorai_user_agent {

namespace {

class QoraiUserAgentComponentInstallerPolicy
    : public component_updater::ComponentInstallerPolicy {
 public:
  QoraiUserAgentComponentInstallerPolicy();
  ~QoraiUserAgentComponentInstallerPolicy() override;

  QoraiUserAgentComponentInstallerPolicy(
      const QoraiUserAgentComponentInstallerPolicy&) = delete;
  QoraiUserAgentComponentInstallerPolicy& operator=(
      const QoraiUserAgentComponentInstallerPolicy&) = delete;

  // component_updater::ComponentInstallerPolicy
  bool SupportsGroupPolicyEnabledComponentUpdates() const override;
  bool RequiresNetworkEncryption() const override;
  update_client::CrxInstaller::Result OnCustomInstall(
      const base::Value::Dict& manifest,
      const base::FilePath& install_dir) override;
  void OnCustomUninstall() override;
  bool VerifyInstallation(const base::Value::Dict& manifest,
                          const base::FilePath& install_dir) const override;
  void ComponentReady(const base::Version& version,
                      const base::FilePath& path,
                      base::Value::Dict manifest) override;
  base::FilePath GetRelativeInstallDir() const override;
  void GetHash(std::vector<uint8_t>* hash) const override;
  std::string GetName() const override;
  update_client::InstallerAttributes GetInstallerAttributes() const override;
  bool IsQoraiComponent() const override;

 private:
  const std::string component_id_;
  const std::string component_name_;
  std::array<uint8_t, crypto::kSHA256Length> component_hash_;
};

QoraiUserAgentComponentInstallerPolicy::QoraiUserAgentComponentInstallerPolicy()
    : component_id_(kQoraiUserAgentExceptionsComponentId),
      component_name_(kQoraiUserAgentExceptionsComponentName) {
  // Generate hash from public key.
  component_hash_ =
      crypto::SHA256Hash(kQoraiUserAgentExceptionsComponentPublicKey);
}

QoraiUserAgentComponentInstallerPolicy::
    ~QoraiUserAgentComponentInstallerPolicy() = default;

bool QoraiUserAgentComponentInstallerPolicy::
    SupportsGroupPolicyEnabledComponentUpdates() const {
  return true;
}

bool QoraiUserAgentComponentInstallerPolicy::RequiresNetworkEncryption() const {
  return false;
}

update_client::CrxInstaller::Result
QoraiUserAgentComponentInstallerPolicy::OnCustomInstall(
    const base::Value::Dict& manifest,
    const base::FilePath& install_dir) {
  return update_client::CrxInstaller::Result(0);
}

void QoraiUserAgentComponentInstallerPolicy::OnCustomUninstall() {}

void QoraiUserAgentComponentInstallerPolicy::ComponentReady(
    const base::Version& version,
    const base::FilePath& path,
    base::Value::Dict manifest) {
  QoraiUserAgentExceptions::GetInstance()->OnComponentReady(path);
}

bool QoraiUserAgentComponentInstallerPolicy::VerifyInstallation(
    const base::Value::Dict& manifest,
    const base::FilePath& install_dir) const {
  return true;
}

base::FilePath QoraiUserAgentComponentInstallerPolicy::GetRelativeInstallDir()
    const {
  return base::FilePath::FromUTF8Unsafe(component_id_);
}

void QoraiUserAgentComponentInstallerPolicy::GetHash(
    std::vector<uint8_t>* hash) const {
  hash->assign(component_hash_.begin(), component_hash_.end());
}

std::string QoraiUserAgentComponentInstallerPolicy::GetName() const {
  return component_name_;
}

update_client::InstallerAttributes
QoraiUserAgentComponentInstallerPolicy::GetInstallerAttributes() const {
  return update_client::InstallerAttributes();
}

bool QoraiUserAgentComponentInstallerPolicy::IsQoraiComponent() const {
  return true;
}

}  // namespace

void RegisterQoraiUserAgentComponent(
    component_updater::ComponentUpdateService* cus) {
  // In test, |cus| could be nullptr.
  if (!base::FeatureList::IsEnabled(
          qorai_user_agent::features::kUseQoraiUserAgent) ||
      !cus) {
    return;
  }

  auto installer = base::MakeRefCounted<component_updater::ComponentInstaller>(
      std::make_unique<QoraiUserAgentComponentInstallerPolicy>());
  installer->Register(
      // After Register, run the callback with component id.
      cus, base::BindOnce([]() {
        qorai_component_updater::QoraiOnDemandUpdater::GetInstance()
            ->EnsureInstalled(kQoraiUserAgentExceptionsComponentId);
      }));
}

}  // namespace qorai_user_agent
