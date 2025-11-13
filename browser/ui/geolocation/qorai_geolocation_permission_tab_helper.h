/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_GEOLOCATION_QORAI_GEOLOCATION_PERMISSION_TAB_HELPER_H_
#define QORAI_BROWSER_UI_GEOLOCATION_QORAI_GEOLOCATION_PERMISSION_TAB_HELPER_H_

#include "qorai/components/qorai_geolocation_permission/common/qorai_geolocation_permission.mojom.h"
#include "content/public/browser/render_frame_host_receiver_set.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class QoraiGeolocationPermissionTabHelper final
    : public content::WebContentsObserver,
      public geolocation::mojom::QoraiGeolocationPermission,
      public content::WebContentsUserData<QoraiGeolocationPermissionTabHelper> {
 public:
  explicit QoraiGeolocationPermissionTabHelper(content::WebContents* contents);
  ~QoraiGeolocationPermissionTabHelper() override;

  static void BindQoraiGeolocationPermission(
      mojo::PendingAssociatedReceiver<
          geolocation::mojom::QoraiGeolocationPermission> receiver,
      content::RenderFrameHost* rfh);

  // content::WebContentsObserver
  void PrimaryPageChanged(content::Page& page) override;

  // geolocation::mojom::QoraiGeolocationPermission overrides:
  void SetEnableHighAccuracy(bool high_accuracy) override;

  bool enable_high_accuracy() const { return enable_high_accuracy_; }

  WEB_CONTENTS_USER_DATA_KEY_DECL();

 private:
  content::RenderFrameHostReceiverSet<
      geolocation::mojom::QoraiGeolocationPermission>
      qorai_geolocation_permission_receivers_;

  bool enable_high_accuracy_ = false;
};

#endif  // QORAI_BROWSER_UI_GEOLOCATION_QORAI_GEOLOCATION_PERMISSION_TAB_HELPER_H_
