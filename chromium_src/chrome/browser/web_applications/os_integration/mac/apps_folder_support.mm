 /* Copyright (c) 2019 The Qorai Authors. All rights reserved.
  * This Source Code Form is subject to the terms of the Mozilla Public
  * License, v. 2.0. If a copy of the MPL was not distributed with this file,
  * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/notreached.h"

 namespace base {
 class FilePath;
 }  // namespace base

namespace {
base::FilePath GetLocalizableQoraiAppShortcutsSubdirName();
}

#define QORAI_GET_CHROME_APPS_FOLDER_IMPL \
  return path.Append(GetLocalizableQoraiAppShortcutsSubdirName());

#include <chrome/browser/web_applications/os_integration/mac/apps_folder_support.mm>
#undef QORAI_GET_CHROME_APPS_FOLDER_IMPL

namespace {
constexpr char kQoraiBrowserDevelopmentAppDirName[] =
    "Qorai Browser Development Apps.localized";
constexpr char kQoraiBrowserAppDirName[] = "Qorai Browser Apps.localized";
constexpr char kQoraiBrowserBetaAppDirName[] =
    "Qorai Browser Beta Apps.localized";
constexpr char kQoraiBrowserDevAppDirName[] =
    "Qorai Browser Dev Apps.localized";
constexpr char kQoraiBrowserNightlyAppDirName[] =
    "Qorai Browser Nightly Apps.localized";

base::FilePath GetLocalizableQoraiAppShortcutsSubdirName() {
  switch (chrome::GetChannel()) {
    case version_info::Channel::STABLE:
      return base::FilePath(kQoraiBrowserAppDirName);
    case version_info::Channel::BETA:
      return base::FilePath(kQoraiBrowserBetaAppDirName);
    case version_info::Channel::DEV:
      return base::FilePath(kQoraiBrowserDevAppDirName);
    case version_info::Channel::CANARY:
      return base::FilePath(kQoraiBrowserNightlyAppDirName);
    case version_info::Channel::UNKNOWN:
      return base::FilePath(kQoraiBrowserDevelopmentAppDirName);
  }

  NOTREACHED() << "All possible channels are handled above.";
}
}  // namespace
