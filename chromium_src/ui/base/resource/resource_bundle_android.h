// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_
#define QORAI_CHROMIUM_SRC_UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_

#include <ui/base/resource/resource_bundle_android.h>  // IWYU pragma: export

namespace ui {

COMPONENT_EXPORT(UI_BASE)
void QoraiLoadMainAndroidPackFile(const char* path_within_apk,
                                  const base::FilePath& disk_file_path);
}

#endif  // QORAI_CHROMIUM_SRC_UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_
