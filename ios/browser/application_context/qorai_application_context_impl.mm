// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/application_context/qorai_application_context_impl.h"

#include <string>

#import "base/command_line.h"
#import "base/task/sequenced_task_runner.h"
#include "base/task/single_thread_task_runner.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component_updater_delegate.h"
#include "qorai/components/qorai_component_updater/browser/local_data_files_service.h"
#include "qorai/components/qorai_sync/network_time_helper.h"
#include "qorai/components/qorai_wallet/browser/wallet_data_files_installer.h"
#include "qorai/components/debounce/core/browser/debounce_component_installer.h"
#include "qorai/components/https_upgrade_exceptions/browser/https_upgrade_exceptions_service.h"
#include "qorai/components/url_sanitizer/core/browser/url_sanitizer_component_installer.h"
#include "qorai/ios/browser/qorai_wallet/wallet_data_files_installer_delegate_impl.h"
#include "components/application_locale_storage/application_locale_storage.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "net/base/features.h"

QoraiApplicationContextImpl::QoraiApplicationContextImpl(
    base::SequencedTaskRunner* local_state_task_runner,
    const base::CommandLine& command_line,
    const std::string& locale,
    const std::string& country)
    : ApplicationContextImpl(local_state_task_runner,
                             command_line,
                             locale,
                             country) {}

inline QoraiApplicationContextImpl::~QoraiApplicationContextImpl() = default;

// MARK: - ApplicationContextImpl

ukm::UkmRecorder* QoraiApplicationContextImpl::GetUkmRecorder() {
  return nullptr;
}

gcm::GCMDriver* QoraiApplicationContextImpl::GetGCMDriver() {
  return nullptr;
}

// MARK: - QoraiApplicationContextImpl

qorai_component_updater::QoraiComponent::Delegate*
QoraiApplicationContextImpl::qorai_component_updater_delegate() {
  if (!qorai_component_updater_delegate_) {
    qorai_component_updater_delegate_ = std::make_unique<
        qorai_component_updater::QoraiComponentUpdaterDelegate>(
        GetComponentUpdateService(), GetLocalState(),
        GetApplicationLocaleStorage()->Get());
  }

  return qorai_component_updater_delegate_.get();
}

qorai_component_updater::LocalDataFilesService*
QoraiApplicationContextImpl::local_data_files_service() {
  if (!local_data_files_service_) {
    local_data_files_service_ =
        qorai_component_updater::LocalDataFilesServiceFactory(
            qorai_component_updater_delegate());
  }
  return local_data_files_service_.get();
}

qorai::URLSanitizerComponentInstaller*
QoraiApplicationContextImpl::url_sanitizer_component_installer() {
  if (!url_sanitizer_component_installer_) {
    url_sanitizer_component_installer_ =
        std::make_unique<qorai::URLSanitizerComponentInstaller>(
            local_data_files_service());
  }
  return url_sanitizer_component_installer_.get();
}

debounce::DebounceComponentInstaller*
QoraiApplicationContextImpl::debounce_component_installer() {
  if (!debounce_component_installer_) {
    debounce_component_installer_ =
        std::make_unique<debounce::DebounceComponentInstaller>(
            local_data_files_service());
  }
  return debounce_component_installer_.get();
}

https_upgrade_exceptions::HttpsUpgradeExceptionsService*
QoraiApplicationContextImpl::https_upgrade_exceptions_service() {
  if (!https_upgrade_exceptions_service_) {
    https_upgrade_exceptions_service_ =
        https_upgrade_exceptions::HttpsUpgradeExceptionsServiceFactory(
            local_data_files_service());
  }
  return https_upgrade_exceptions_service_.get();
}

void QoraiApplicationContextImpl::StartQoraiServices() {
  // We need to Initialize the component installers
  // before calling Start on the local_data_files_service
  url_sanitizer_component_installer();
  debounce_component_installer();

  if (base::FeatureList::IsEnabled(net::features::kQoraiHttpsByDefault)) {
    https_upgrade_exceptions_service();
  }

  // Start the local data file service
  local_data_files_service()->Start();

  qorai_sync::NetworkTimeHelper::GetInstance()->SetNetworkTimeTracker(
      GetNetworkTimeTracker(),
      base::SingleThreadTaskRunner::GetCurrentDefault());

  qorai_wallet::WalletDataFilesInstaller::GetInstance().SetDelegate(
      std::make_unique<qorai_wallet::WalletDataFilesInstallerDelegateImpl>());
}
