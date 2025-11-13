/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "qorai/components/constants/pref_names.h"

#define QORAI_MANAGED_CONTENT_SETTINGS                                         \
  {kManagedQoraiShieldsDisabledForUrls, ContentSettingsType::QORAI_SHIELDS,    \
   CONTENT_SETTING_BLOCK},                                                     \
      {kManagedQoraiShieldsEnabledForUrls, ContentSettingsType::QORAI_SHIELDS, \
       CONTENT_SETTING_ALLOW},

#define QORAI_MANAGED_PREFS \
  kManagedQoraiShieldsDisabledForUrls, kManagedQoraiShieldsEnabledForUrls,

#define QORAI_MANAGED_DEFAULT                    \
  {ContentSettingsType::QORAI_FINGERPRINTING_V2, \
   kManagedDefaultQoraiFingerprintingV2},

#define QORAI_MANAGED_DEFAULT_PREFS kManagedDefaultQoraiFingerprintingV2,

#include <components/content_settings/core/browser/content_settings_policy_provider.cc>
#undef QORAI_MANAGED_DEFAULT_PREFS
#undef QORAI_MANAGED_DEFAULT
#undef QORAI_MANAGED_PREFS
#undef QORAI_MANAGED_CONTENT_SETTINGS
