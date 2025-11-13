/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/content/browser/screen_orientation/qorai_screen_orientation_delegate_android.h"

#include "qorai/content/public/browser/fullscreen_page_data.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_entry.h"

namespace content {

QoraiScreenOrientationDelegateAndroid::QoraiScreenOrientationDelegateAndroid() =
    default;
QoraiScreenOrientationDelegateAndroid::
    ~QoraiScreenOrientationDelegateAndroid() = default;

void QoraiScreenOrientationDelegateAndroid::Lock(
    WebContents* web_contents,
    device::mojom::ScreenOrientationLockType lock_orientation) {
  if (IsYouTubeFullscreenRequested(web_contents)) {
    return;
  }

  ScreenOrientationDelegateAndroid::Lock(web_contents, lock_orientation);
}

void QoraiScreenOrientationDelegateAndroid::Unlock(WebContents* web_contents) {
  if (IsYouTubeFullscreenRequested(web_contents)) {
    return;
  }

  ScreenOrientationDelegateAndroid::Unlock(web_contents);
}

// static
bool QoraiScreenOrientationDelegateAndroid::IsYouTubeFullscreenRequested(
    WebContents* web_contents) {
  // Check YouTube fullscreen state from NavigationEntry UserData
  if (!web_contents) {
    return false;
  }

  NavigationEntry* entry =
      web_contents->GetController().GetLastCommittedEntry();
  if (!entry) {
    return false;
  }

  auto* data = static_cast<FullscreenPageData*>(
      entry->GetUserData(kFullscreenPageDataKey));
  return data && data->fullscreen_requested();
}

}  // namespace content
