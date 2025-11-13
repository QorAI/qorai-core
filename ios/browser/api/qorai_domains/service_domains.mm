// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/qorai_domains/service_domains.h"

#include "base/check.h"
#include "base/command_line.h"
#include "base/strings/strcat.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/ios/browser/api/qorai_domains/service_domains.h"

namespace {
constexpr char kQoraiServicesSwitchValueDev[] = "dev";
constexpr char kQoraiServicesSwitchValueStaging[] = "staging";
constexpr char kQoraiServicesEnvironmentSwitch[] = "qorai-services-env";
}  // namespace

QoraiServicesEnvironmentIOS const QoraiServicesEnvironmentIOSDevelopment =
    static_cast<NSInteger>(qorai_domains::ServicesEnvironment::DEV);
QoraiServicesEnvironmentIOS const QoraiServicesEnvironmentIOSStaging =
    static_cast<NSInteger>(qorai_domains::ServicesEnvironment::STAGING);
QoraiServicesEnvironmentIOS const QoraiServicesEnvironmentIOSProduction =
    static_cast<NSInteger>(qorai_domains::ServicesEnvironment::PROD);

@implementation QoraiDomains
+ (QoraiServicesEnvironmentIOS)environment {
  return [QoraiDomains environmentWithPrefix:@""];
}

+ (QoraiServicesEnvironmentIOS)environmentWithPrefix:(NSString*)prefix {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  DCHECK(command_line);

  if (command_line) {
    std::string env_from_switch =
        command_line->GetSwitchValueASCII(kQoraiServicesEnvironmentSwitch);

    if ([prefix length] > 0) {
      env_from_switch = command_line->GetSwitchValueASCII(
          base::StrCat({"env-", base::SysNSStringToUTF8(prefix)}));
    }

    if (env_from_switch == kQoraiServicesSwitchValueDev) {
      return QoraiServicesEnvironmentIOSDevelopment;
    }

    if (env_from_switch == kQoraiServicesSwitchValueStaging) {
      return QoraiServicesEnvironmentIOSStaging;
    }
  }
  return QoraiServicesEnvironmentIOSProduction;
}

+ (NSString*)serviceDomainWithPrefix:(NSString*)prefix {
  return base::SysUTF8ToNSString(
      qorai_domains::GetServicesDomain(base::SysNSStringToUTF8(prefix)));
}

+ (NSString*)serviceDomainWithPrefix:(NSString*)prefix
                         environment:(QoraiServicesEnvironmentIOS)environment {
  return base::SysUTF8ToNSString(qorai_domains::GetServicesDomain(
      base::SysNSStringToUTF8(prefix),
      static_cast<qorai_domains::ServicesEnvironment>(environment)));
}
@end
