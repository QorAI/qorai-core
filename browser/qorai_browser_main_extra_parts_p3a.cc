/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_browser_main_extra_parts_p3a.h"

#include "qorai/browser/updater/features.h"
#include "qorai/browser/updater/updater_p3a.h"
#include "chrome/browser/browser_process.h"
#include "chrome/common/chrome_constants.h"

QorAIBrowserMainExtraPartsP3A::QorAIBrowserMainExtraPartsP3A() = default;

QorAIBrowserMainExtraPartsP3A::~QorAIBrowserMainExtraPartsP3A() = default;

void QorAIBrowserMainExtraPartsP3A::PostBrowserStart() {
  qorai_updater::ReportLaunch(chrome::kChromeVersion,
                              qorai_updater::ShouldUseOmaha4(),
                              g_browser_process->local_state());
}
