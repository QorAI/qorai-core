/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_COMPONENT_INSTALLER_H_
#define QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_COMPONENT_INSTALLER_H_

#include <string>
#include <vector>

#include "base/component_export.h"
#include "base/files/file_path.h"
#include "base/functional/callback.h"
#include "base/values.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component.h"
#include "components/component_updater/component_installer.h"
#include "components/update_client/update_client.h"

namespace qorai_component_updater {

class COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER) QoraiComponentInstallerPolicy
    : public component_updater::ComponentInstallerPolicy {
 public:
  explicit QoraiComponentInstallerPolicy(
      const std::string& name,
      const std::string& base64_public_key,
      QoraiComponent::ReadyCallback ready_callback);

  QoraiComponentInstallerPolicy(const QoraiComponentInstallerPolicy&) = delete;
  QoraiComponentInstallerPolicy& operator=(
      const QoraiComponentInstallerPolicy&) = delete;

  ~QoraiComponentInstallerPolicy() override;

 private:
  // The following methods override ComponentInstallerPolicy
  bool VerifyInstallation(const base::Value::Dict& manifest,
                          const base::FilePath& install_dir) const override;
  bool SupportsGroupPolicyEnabledComponentUpdates() const override;
  bool RequiresNetworkEncryption() const override;
  update_client::CrxInstaller::Result OnCustomInstall(
      const base::Value::Dict& manifest,
      const base::FilePath& install_dir) override;
  void OnCustomUninstall() override;
  void ComponentReady(const base::Version& version,
                      const base::FilePath& install_dir,
                      base::Value::Dict manifest) override;
  base::FilePath GetRelativeInstallDir() const override;
  void GetHash(std::vector<uint8_t>* hash) const override;
  std::string GetName() const override;
  update_client::InstallerAttributes GetInstallerAttributes() const override;
  bool IsQoraiComponent() const override;

  std::string name_;
  std::string base64_public_key_;
  std::string public_key_;
  QoraiComponent::ReadyCallback ready_callback_;
};

}  // namespace qorai_component_updater

#endif  // QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_QORAI_COMPONENT_INSTALLER_H_
