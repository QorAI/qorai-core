// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_COMPONENTS_PREFS_PREF_SERVICE_BRIDGE_IMPL_H_
#define QORAI_IOS_COMPONENTS_PREFS_PREF_SERVICE_BRIDGE_IMPL_H_

#include "base/memory/raw_ptr.h"
#include "qorai/ios/components/prefs/pref_service_bridge.h"

class PrefService;

@interface PrefServiceBridgeImpl : NSObject <PrefServiceBridge>
@property(readonly) raw_ptr<PrefService> prefService;
- (instancetype)initWithPrefService:(raw_ptr<PrefService>)prefService;
@end

#endif  // QORAI_IOS_COMPONENTS_PREFS_PREF_SERVICE_BRIDGE_IMPL_H_
