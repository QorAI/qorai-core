/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/component_updater/registration.h"
#include "base/functional/bind.h"

#define RegisterComponentsForUpdate RegisterComponentsForUpdate_ChromiumImpl

#include <chrome/browser/component_updater/registration.cc>

#undef RegisterComponentsForUpdate

#include "qorai/browser/qorai_browser_process.h"
#include "qorai/components/ai_chat/core/browser/local_models_updater.h"
#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_component_installer.h"
#include "qorai/components/qorai_wallet/browser/wallet_data_files_installer.h"
#include "qorai/components/p3a/component_installer.h"
#include "qorai/components/p3a/p3a_service.h"
#include "qorai/components/psst/buildflags/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/component_updater/component_updater_utils.h"

#if BUILDFLAG(ENABLE_PSST)
#include "qorai/components/psst/browser/core/psst_component_installer.h"
#endif

#if BUILDFLAG(IS_ANDROID)
#include "chrome/browser/component_updater/zxcvbn_data_component_installer.h"
#endif  // BUILDFLAG(IS_ANDROID)

namespace component_updater {

void RegisterComponentsForUpdate() {
  RegisterComponentsForUpdate_ChromiumImpl();
  ComponentUpdateService* cus = g_browser_process->component_updater();
  qorai_wallet::WalletDataFilesInstaller::GetInstance()
      .MaybeRegisterWalletDataFilesComponent(cus,
                                             g_browser_process->local_state());
#if BUILDFLAG(ENABLE_PSST)
  psst::RegisterPsstComponent(cus);
#endif
  p3a::MaybeToggleP3AComponent(cus, g_qorai_browser_process->p3a_service());
#if BUILDFLAG(IS_ANDROID)
  // Currently behind !BUILDFLAG(IS_ANDROID) in upstream.
  RegisterZxcvbnDataComponent(cus);
#endif  // BUILDFLAG(IS_ANDROID)
  qorai_user_agent::RegisterQoraiUserAgentComponent(cus);
}

}  // namespace component_updater
