// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/qorai_news/qorai_news_pref_names_bridge.h"

#include "base/strings/sys_string_conversions.h"
#include "qorai/components/qorai_news/common/pref_names.h"

NSString* const kQoraiNewsDisabledByPolicyPrefName =
    base::SysUTF8ToNSString(qorai_news::prefs::kQoraiNewsDisabledByPolicy);
