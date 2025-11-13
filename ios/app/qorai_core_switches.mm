/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/app/qorai_core_switches.h"

#include "base/base_switches.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/components/qorai_component_updater/browser/switches.h"
#include "qorai/components/p3a/switches.h"
#include "qorai/components/variations/switches.h"
#include "components/component_updater/component_updater_switches.h"
#include "components/sync/base/command_line_switches.h"
#include "components/variations/variations_switches.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

const QoraiCoreSwitchKey QoraiCoreSwitchKeyComponentUpdater =
    base::SysUTF8ToNSString(switches::kComponentUpdater);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyVModule =
    base::SysUTF8ToNSString(switches::kVModule);
const QoraiCoreSwitchKey QoraiCoreSwitchKeySyncURL =
    base::SysUTF8ToNSString(syncer::kSyncServiceURL);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyVariationsPR =
    base::SysUTF8ToNSString(variations::switches::kVariationsPR);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyVariationsURL =
    base::SysUTF8ToNSString(variations::switches::kVariationsServerURL);
// There is no exposed switch for rewards
const QoraiCoreSwitchKey QoraiCoreSwitchKeyRewardsFlags = @"rewards";
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AUploadIntervalSeconds =
    base::SysUTF8ToNSString(p3a::switches::kP3AUploadIntervalSeconds);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3ADoNotRandomizeUploadInterval =
    base::SysUTF8ToNSString(p3a::switches::kP3ADoNotRandomizeUploadInterval);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3ATypicalRotationIntervalSeconds =
    base::SysUTF8ToNSString(p3a::switches::kP3ATypicalRotationIntervalSeconds);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AExpressRotationIntervalSeconds =
    base::SysUTF8ToNSString(p3a::switches::kP3AExpressRotationIntervalSeconds);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3ASlowRotationIntervalSeconds =
    base::SysUTF8ToNSString(p3a::switches::kP3ASlowRotationIntervalSeconds);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AFakeTypicalStarEpoch =
    base::SysUTF8ToNSString(p3a::switches::kP3AFakeTypicalStarEpoch);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AFakeSlowStarEpoch =
    base::SysUTF8ToNSString(p3a::switches::kP3AFakeSlowStarEpoch);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AFakeExpressStarEpoch =
    base::SysUTF8ToNSString(p3a::switches::kP3AFakeExpressStarEpoch);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AJsonUploadServerURL =
    base::SysUTF8ToNSString(p3a::switches::kP3AJsonUploadUrl);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3ACreativeUploadServerURL =
    base::SysUTF8ToNSString(p3a::switches::kP3ACreativeUploadUrl);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AConstellationUploadServerHost =
    base::SysUTF8ToNSString(p3a::switches::kP3AConstellationUploadHost);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3ADisableStarAttestation =
    base::SysUTF8ToNSString(p3a::switches::kP3ADisableStarAttestation);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AStarRandomnessHost =
    base::SysUTF8ToNSString(p3a::switches::kP3AStarRandomnessHost);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyP3AIgnoreServerErrors =
    base::SysUTF8ToNSString(p3a::switches::kP3AIgnoreServerErrors);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyUseDevGoUpdater =
    base::SysUTF8ToNSString(qorai_component_updater::kUseGoUpdateDev);
const QoraiCoreSwitchKey QoraiCoreSwitchKeyServicesEnvironment =
    @"qorai-services-env";

@implementation QoraiCoreSwitch
- (instancetype)initWithKey:(QoraiCoreSwitchKey)key {
  return [self initWithKey:key value:nil];
}
- (instancetype)initWithKey:(QoraiCoreSwitchKey)key
                      value:(nullable NSString*)value {
  if ((self = [super init])) {
    _key = [key copy];
    _value = [value copy];
  }
  return self;
}
@end
