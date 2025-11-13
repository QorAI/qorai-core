/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/gcm_driver/qorai_gcm_channel_status.h"

#include <memory>

#include "qorai/components/constants/pref_names.h"
#include "chrome/browser/gcm/gcm_profile_service_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/gcm_driver/gcm_driver_desktop.h"
#include "components/gcm_driver/gcm_profile_service.h"
#include "components/prefs/pref_service.h"

namespace gcm {

constexpr char kQoraiGCMStatusKey[] = "qorai_gcm_channel_status";

QoraiGCMChannelStatus::QoraiGCMChannelStatus(Profile* profile, bool enabled)
    : profile_(profile), gcm_enabled_(enabled) {}

// static
QoraiGCMChannelStatus* QoraiGCMChannelStatus::GetForProfile(
    Profile* profile) {
  QoraiGCMChannelStatus* status = static_cast<QoraiGCMChannelStatus*>(
      profile->GetUserData(kQoraiGCMStatusKey));

  if (!status) {
    bool enabled = profile->GetPrefs()->GetBoolean(kQoraiGCMChannelStatus);
    // Object cleanup is handled by SupportsUserData
    profile->SetUserData(
        kQoraiGCMStatusKey,
        std::make_unique<QoraiGCMChannelStatus>(profile, enabled));
    status = static_cast<QoraiGCMChannelStatus*>(
        profile->GetUserData(kQoraiGCMStatusKey));
  }
  return status;
}

bool QoraiGCMChannelStatus::IsGCMEnabled() const {
  return gcm_enabled_;
}

void QoraiGCMChannelStatus::UpdateGCMDriverStatus() {
  if (!profile_)
    return;
  gcm::GCMProfileService* gcm_profile_service =
      gcm::GCMProfileServiceFactory::GetForProfile(profile_);
  if (!gcm_profile_service)
    return;
  gcm::GCMDriver* gcm_driver = gcm_profile_service->driver();
  if (!gcm_driver)
    return;
  gcm_driver->SetEnabled(IsGCMEnabled());
}

}  // namespace gcm
