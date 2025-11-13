// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include <string>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "qorai/browser/android/safe_browsing/buildflags.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_stats/qorai_stats_updater.h"
#include "chrome/android/chrome_jni_headers/QoraiActivity_jni.h"

namespace chrome {
namespace android {

static void JNI_QoraiActivity_RestartStatsUpdater(JNIEnv* env) {
  g_qorai_browser_process->qorai_stats_updater()->Stop();
  g_qorai_browser_process->qorai_stats_updater()->Start();
}

static base::android::ScopedJavaLocalRef<jstring>
JNI_QoraiActivity_GetSafeBrowsingApiKey(JNIEnv* env) {
  return base::android::ConvertUTF8ToJavaString(
      env, BUILDFLAG(SAFEBROWSING_API_KEY));
}

}  // namespace android
}  // namespace chrome
