// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/web/qorai_web_main_parts.h"

#include "base/check.h"
#include "base/command_line.h"
#include "base/path_service.h"
#include "base/strings/sys_string_conversions.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/thread_pool.h"
#include "qorai/components/ai_chat/core/browser/local_models_updater.h"
#include "qorai/components/qorai_component_updater/browser/qorai_on_demand_updater.h"
#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_component_installer.h"
#include "qorai/components/qorai_wallet/browser/wallet_data_files_installer.h"
#include "qorai/ios/browser/application_context/qorai_application_context_impl.h"
#include "chrome/browser/component_updater/zxcvbn_data_component_installer.h"
#include "components/component_updater/installer_policies/safety_tips_component_installer.h"
#include "ios/chrome/browser/application_context/model/application_context_impl.h"
#include "ios/chrome/browser/shared/model/paths/paths.h"
#include "ui/base/l10n/l10n_util_mac.h"
#include "ui/base/resource/resource_bundle.h"

namespace {
void RegisterComponentsForUpdate(
    component_updater::ComponentUpdateService* cus) {
  RegisterSafetyTipsComponent(cus);
  qorai_wallet::WalletDataFilesInstaller::GetInstance()
      .MaybeRegisterWalletDataFilesComponent(
          cus, GetApplicationContext()->GetLocalState());
  ai_chat::MigrateDeprecatedLocalModelsComponent(cus);
  qorai_user_agent::RegisterQoraiUserAgentComponent(cus);
  RegisterZxcvbnDataComponent(cus);
}
}  // namespace

QoraiWebMainParts::QoraiWebMainParts(
    const base::CommandLine& parsed_command_line)
    : IOSChromeMainParts(parsed_command_line) {}

QoraiWebMainParts::~QoraiWebMainParts() {}

void QoraiWebMainParts::PreCreateMainMessageLoop() {
  IOSChromeMainParts::PreCreateMainMessageLoop();

  // Add Qorai Resource Pack
  auto qorai_pack_path = base::PathService::CheckedGet(base::DIR_ASSETS);
  qorai_pack_path = qorai_pack_path.AppendASCII("qorai_resources.pak");
  ui::ResourceBundle::GetSharedInstance().AddDataPackFromPath(
      qorai_pack_path, ui::kScaleFactorNone);
}

void QoraiWebMainParts::PreMainMessageLoopRun() {
  IOSChromeMainParts::PreMainMessageLoopRun();

  // Setup Component Updater
  component_updater::ComponentUpdateService* cus =
      application_context_->GetComponentUpdateService();
  DCHECK(cus);
  qorai_component_updater::QoraiOnDemandUpdater::GetInstance()
      ->RegisterOnDemandUpdater(
          base::CommandLine::ForCurrentProcess()->HasSwitch(
              "disable-component-update"),
          &cus->GetOnDemandUpdater());
  RegisterComponentsForUpdate(cus);
}
