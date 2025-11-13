/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_SERVICE_SANDBOX_TYPE_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_SERVICE_SANDBOX_TYPE_H_

#include "build/build_config.h"
#include "content/public/browser/service_process_host.h"

namespace qorai_rewards::mojom {
class RewardsEngineFactory;
}  // namespace qorai_rewards::mojom

template <>
inline sandbox::mojom::Sandbox
content::GetServiceSandboxType<qorai_rewards::mojom::RewardsEngineFactory>() {
#if !BUILDFLAG(IS_ANDROID)
  return sandbox::mojom::Sandbox::kNoSandbox;
#else
  return sandbox::mojom::Sandbox::kUtility;
#endif  // !BUILDFLAG(IS_ANDROID)
}

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_SERVICE_SANDBOX_TYPE_H_
