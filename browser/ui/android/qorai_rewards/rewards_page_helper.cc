// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/android/qorai_rewards/rewards_page_helper.h"

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "qorai/build/android/jni_headers/TabUtils_jni.h"

namespace qorai_rewards {

void OpenURLForRewardsPage(const std::string& url) {
  Java_TabUtils_openURLWithQoraiActivity(
      base::android::AttachCurrentThread(),
      base::android::ConvertUTF8ToJavaString(
          base::android::AttachCurrentThread(), url));
}

}  // namespace qorai_rewards
