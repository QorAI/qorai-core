// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_ANDROID_TAB_FEATURES_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_ANDROID_TAB_FEATURES_H_

#define TabFeatures TabFeatures_Chromium

#include <chrome/browser/android/tab_features.h>  // IWYU pragma: export

#undef TabFeatures

namespace tabs {
class QoraiTabFeatures;
class TabFeatures {
 public:
  TabFeatures(content::WebContents* web_contents, Profile* profile);
  ~TabFeatures();

 private:
  friend QoraiTabFeatures;
  std::unique_ptr<QoraiTabFeatures> qorai_tab_features_;
};
}  // namespace tabs

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_ANDROID_TAB_FEATURES_H_
