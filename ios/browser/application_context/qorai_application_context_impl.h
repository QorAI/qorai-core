// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_APPLICATION_CONTEXT_QORAI_APPLICATION_CONTEXT_IMPL_H_
#define QORAI_IOS_BROWSER_APPLICATION_CONTEXT_QORAI_APPLICATION_CONTEXT_IMPL_H_

#include <memory>
#include <string>

#include "qorai/components/qorai_component_updater/browser/qorai_component.h"
#include "qorai/components/debounce/core/browser/debounce_component_installer.h"
#include "qorai/components/https_upgrade_exceptions/browser/https_upgrade_exceptions_service.h"
#include "qorai/components/url_sanitizer/core/browser/url_sanitizer_component_installer.h"
#include "ios/chrome/browser/application_context/model/application_context_impl.h"

namespace base {
class CommandLine;
class SequencedTaskRunner;
}  // namespace base

/// This extends the behaviors of the ApplicationContext
class QoraiApplicationContextImpl : public ApplicationContextImpl {
 public:
  // Out-of-line constructor declaration
  QoraiApplicationContextImpl(
      base::SequencedTaskRunner* local_state_task_runner,
      const base::CommandLine& command_line,
      const std::string& locale,
      const std::string& country);

  QoraiApplicationContextImpl(const QoraiApplicationContextImpl&) = delete;
  QoraiApplicationContextImpl& operator=(const QoraiApplicationContextImpl&) =
      delete;

  ~QoraiApplicationContextImpl() override;

  // ApplicationContextImpl
  ukm::UkmRecorder* GetUkmRecorder() override;
  gcm::GCMDriver* GetGCMDriver() override;

  // QoraiApplicationContextImpl
  qorai::URLSanitizerComponentInstaller* url_sanitizer_component_installer();
  debounce::DebounceComponentInstaller* debounce_component_installer();
  https_upgrade_exceptions::HttpsUpgradeExceptionsService*
  https_upgrade_exceptions_service();

  // Start any services that we may need later
  void StartQoraiServices();

 private:
  qorai_component_updater::QoraiComponent::Delegate*
  qorai_component_updater_delegate();
  qorai_component_updater::LocalDataFilesService* local_data_files_service();

  std::unique_ptr<qorai_component_updater::QoraiComponent::Delegate>
      qorai_component_updater_delegate_;
  std::unique_ptr<qorai_component_updater::LocalDataFilesService>
      local_data_files_service_;
  std::unique_ptr<qorai::URLSanitizerComponentInstaller>
      url_sanitizer_component_installer_;
  std::unique_ptr<debounce::DebounceComponentInstaller>
      debounce_component_installer_;
  std::unique_ptr<https_upgrade_exceptions::HttpsUpgradeExceptionsService>
      https_upgrade_exceptions_service_;
};

#endif  // QORAI_IOS_BROWSER_APPLICATION_CONTEXT_QORAI_APPLICATION_CONTEXT_IMPL_H_
