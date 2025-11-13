/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_
#define QORAI_CHROMIUM_SRC_CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_

namespace icon_resources {

// This file contains the indices of icon resources in qorai_exe.rc.

enum {
  // The main application icon is always index 0.
  kApplicationIndex = 0,

#if defined(OFFICIAL_BUILD)
  // Legacy indices that are no longer used.
  kApplication2Index = 1,
  kApplication3Index = 2,
  kApplication4Index = 3,

  // The Qorai Canary application icon.
  kSxSApplicationIndex = 4,

  // The Qorai App Launcher icon.
  kAppLauncherIndex = 5,

  // The Qorai App Launcher Canary icon.
  kSxSAppLauncherIndex = 6,

  // The Qorai incognito icon.
  kIncognitoIndex = 7,

  // The Qorai Dev application icon.
  kDevApplicationIndex = 8,

  // The Qorai Beta application icon.
  kBetaApplicationIndex = 9,

  // The various file type icon(ex, pdf).
  kFileTypeIndex = 10,
  kBetaFileTypeIndex = 11,
  kDevFileTypeIndex = 12,
  kSxSFileTypeIndex = 13,
#else
  // The Qorai Developer App Launcher icon.
  kAppLauncherIndex = 1,

  // The Qorai Developer incognito icon.
  kIncognitoIndex = 2,
#endif
};

}  // namespace icon_resources

#endif  // QORAI_CHROMIUM_SRC_CHROME_COMMON_CHROME_ICON_RESOURCES_WIN_H_
