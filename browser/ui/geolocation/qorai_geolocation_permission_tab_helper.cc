/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/geolocation/qorai_geolocation_permission_tab_helper.h"

#include <utility>

#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/web_contents.h"

QoraiGeolocationPermissionTabHelper::QoraiGeolocationPermissionTabHelper(
    content::WebContents* contents)
    : WebContentsObserver(contents),
      content::WebContentsUserData<QoraiGeolocationPermissionTabHelper>(
          *contents),
      qorai_geolocation_permission_receivers_(contents, this) {}

QoraiGeolocationPermissionTabHelper::~QoraiGeolocationPermissionTabHelper() =
    default;

// static
void QoraiGeolocationPermissionTabHelper::BindQoraiGeolocationPermission(
    mojo::PendingAssociatedReceiver<
        geolocation::mojom::QoraiGeolocationPermission> receiver,
    content::RenderFrameHost* rfh) {
  auto* web_contents = content::WebContents::FromRenderFrameHost(rfh);
  if (!web_contents) {
    return;
  }

  auto* tab_helper =
      QoraiGeolocationPermissionTabHelper::FromWebContents(web_contents);
  if (!tab_helper) {
    return;
  }
  tab_helper->qorai_geolocation_permission_receivers_.Bind(rfh,
                                                           std::move(receiver));
}

void QoraiGeolocationPermissionTabHelper::PrimaryPageChanged(
    content::Page& page) {
  enable_high_accuracy_ = false;
}

void QoraiGeolocationPermissionTabHelper::SetEnableHighAccuracy(
    bool enable_high_accuracy) {
  enable_high_accuracy_ = enable_high_accuracy;
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(QoraiGeolocationPermissionTabHelper);
