/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_BROWSER_DIALOGS_H_
#define QORAI_BROWSER_UI_BROWSER_DIALOGS_H_

#include "base/functional/callback_forward.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/text_recognition/common/buildflags/buildflags.h"

class Browser;
class SkBitmap;

namespace content {
class WebContents;
}  // namespace content

namespace qorai {

// Tab restore dialog will be launched after ask dialog is closed.
void ShowCrashReportPermissionAskDialog(Browser* browser);

// Run |callback| when dialog closed.
void ShowObsoleteSystemConfirmDialog(base::OnceCallback<void(bool)> callback);

#if BUILDFLAG(ENABLE_TEXT_RECOGNITION)
// Show web modal dialog for showing text that recognized from |image|.
void ShowTextRecognitionDialog(content::WebContents* web_contents,
                               const SkBitmap& image);
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
void ShowQoraiVpnIKEv2FallbackDialog();
#endif
}  // namespace qorai

#endif  // QORAI_BROWSER_UI_BROWSER_DIALOGS_H_
