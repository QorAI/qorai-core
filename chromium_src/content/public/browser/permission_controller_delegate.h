/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_PERMISSION_CONTROLLER_DELEGATE_H_
#define QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_PERMISSION_CONTROLLER_DELEGATE_H_

#include "content/public/browser/permission_controller.h"

#define UnsubscribeFromPermissionResultChange                                 \
  PermissionControllerDelegateNotUsed() {}                                    \
  virtual void RequestPermissionsForOrigin(                                   \
      const std::vector<blink::PermissionType>& permissions,                  \
      content::RenderFrameHost* render_frame_host,                            \
      const GURL& requesting_origin, bool user_gesture,                       \
      base::OnceCallback<void(const std::vector<content::PermissionResult>&)> \
          callback) {}                                                        \
                                                                              \
  virtual blink::mojom::PermissionStatus GetPermissionStatusForOrigin(        \
      blink::PermissionType permission,                                       \
      content::RenderFrameHost* render_frame_host,                            \
      const GURL& requesting_origin);                                         \
                                                                              \
  virtual void UnsubscribeFromPermissionResultChange

#include <content/public/browser/permission_controller_delegate.h>  // IWYU pragma: export

#undef UnsubscribeFromPermissionResultChange

#endif  // QORAI_CHROMIUM_SRC_CONTENT_PUBLIC_BROWSER_PERMISSION_CONTROLLER_DELEGATE_H_
