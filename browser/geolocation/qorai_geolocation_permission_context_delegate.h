/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_GEOLOCATION_QORAI_GEOLOCATION_PERMISSION_CONTEXT_DELEGATE_H_
#define QORAI_BROWSER_GEOLOCATION_QORAI_GEOLOCATION_PERMISSION_CONTEXT_DELEGATE_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/geolocation/geolocation_permission_context_delegate.h"

class Profile;

class QoraiGeolocationPermissionContextDelegate
    : public GeolocationPermissionContextDelegate {
 public:
  explicit QoraiGeolocationPermissionContextDelegate(
      content::BrowserContext* browser_context);
  QoraiGeolocationPermissionContextDelegate(
      const QoraiGeolocationPermissionContextDelegate&) = delete;
  QoraiGeolocationPermissionContextDelegate& operator=(
      const QoraiGeolocationPermissionContextDelegate&) = delete;
  ~QoraiGeolocationPermissionContextDelegate() override;

  bool DecidePermission(
      const permissions::PermissionRequestData& request_data,
      permissions::BrowserPermissionCallback* callback,
      permissions::GeolocationPermissionContext* context) override;

 private:
  raw_ptr<Profile> profile_ = nullptr;
};

#endif  // QORAI_BROWSER_GEOLOCATION_QORAI_GEOLOCATION_PERMISSION_CONTEXT_DELEGATE_H_
