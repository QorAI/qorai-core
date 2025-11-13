// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/qorai_domains/service_domains.h"

#include <string>

#include "base/command_line.h"
#include "base/containers/contains.h"
#include "base/containers/fixed_flat_map.h"
#include "base/containers/fixed_flat_set.h"
#include "base/containers/map_util.h"
#include "base/logging.h"
#include "base/notreached.h"
#include "base/strings/strcat.h"
#include "qorai/qorai_domains/buildflags.h"

namespace qorai_domains {

namespace {

constexpr char kQorAIServicesSwitchValueDev[] = "dev";
constexpr char kQorAIServicesSwitchValueStaging[] = "staging";
constexpr char kQorAIServicesSwitchValueProduction[] = "prod";
constexpr char kQorAIServicesEnvironmentSwitch[] = "qorai-services-env";

std::string GetServicesDomainForSwitchValue(std::string env_from_switch) {
  if (env_from_switch == kQorAIServicesSwitchValueStaging) {
    return BUILDFLAG(QORAI_SERVICES_STAGING_DOMAIN);
  }
  if (env_from_switch == kQorAIServicesSwitchValueDev) {
    return BUILDFLAG(QORAI_SERVICES_DEV_DOMAIN);
  }
  // Default to production
  return BUILDFLAG(QORAI_SERVICES_PRODUCTION_DOMAIN);
}

bool IsValidSwitchValue(std::string value) {
  static constexpr auto kAllowedSwitchValues =
      base::MakeFixedFlatSet<std::string_view>(
          {kQorAIServicesSwitchValueDev, kQorAIServicesSwitchValueStaging,
           kQorAIServicesSwitchValueProduction});
  return kAllowedSwitchValues.contains(value);
}

void MaybeWarnSwitchValue(std::string key, std::string value) {
  if (!value.empty()) {
    if (!IsValidSwitchValue(value)) {
      LOG(ERROR) << "The switch value for --" << key << " is \"" << value
                 << "\" which is not a valid value, please provide"
                 << " either \"" << kQorAIServicesSwitchValueDev << "\", \""
                 << kQorAIServicesSwitchValueStaging << "\", or \""
                 << kQorAIServicesSwitchValueProduction << "\" (default).";
    } else {
      // It's useful to have this in the logs. This should be a temporary
      // dev or debug tool and not a permanent situation for a user.
      LOG(WARNING) << "Services domain(s) was overriden with the parameter: --"
                   << key << " and value \"" << value << "\"";
    }
  }
}

#if !defined(OFFICIAL_BUILD)
std::string_view ConvertEnvironmentToString(
    qorai_domains::ServicesEnvironment env) {
  static constexpr auto kEnvs = base::MakeFixedFlatMap<
      qorai_domains::ServicesEnvironment, std::string_view>(
      {{qorai_domains::ServicesEnvironment::DEV, kQorAIServicesSwitchValueDev},
       {qorai_domains::ServicesEnvironment::STAGING,
        kQorAIServicesSwitchValueStaging},
       {qorai_domains::ServicesEnvironment::PROD,
        kQorAIServicesSwitchValueProduction}});

  auto* value = base::FindOrNull(kEnvs, env);
  CHECK(value);
  return *value;
}
#endif

}  // namespace

std::string GetServicesDomain(
    std::string prefix,
    ServicesEnvironment env_value_default_override,
    base::CommandLine*
        command_line /* = base::CommandLine::ForCurrentProcess() */) {
  // Default to production
  std::string env_value = kQorAIServicesSwitchValueProduction;

  // If a default parameter was supplied, use that instead, but only
  // for unofficial builds.
#if !defined(OFFICIAL_BUILD)
  env_value = ConvertEnvironmentToString(env_value_default_override);
#endif

  // If a global value was supplied via CLI, use that instead.
  std::string env_from_switch =
      command_line->GetSwitchValueASCII(kQorAIServicesEnvironmentSwitch);
  MaybeWarnSwitchValue(kQorAIServicesEnvironmentSwitch, env_from_switch);
  if (IsValidSwitchValue(env_from_switch)) {
    env_value = env_from_switch;
  }

  // If a value was supplied for this specific prefix via CLI, use that instead.
  if (!prefix.empty()) {
    std::string env_key = base::StrCat({"env-", prefix});
    env_from_switch = command_line->GetSwitchValueASCII(env_key);
    MaybeWarnSwitchValue(env_key, env_from_switch);
    if (IsValidSwitchValue(env_from_switch)) {
      env_value = env_from_switch;
    }
  }

  // Build hostname
  if (prefix.empty()) {
    return GetServicesDomainForSwitchValue(env_value);
  }

  return base::StrCat(
      {prefix, ".", GetServicesDomainForSwitchValue(env_value)});
}

}  // namespace qorai_domains
