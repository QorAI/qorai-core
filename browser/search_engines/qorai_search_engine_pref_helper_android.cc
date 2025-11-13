/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/android/java/org/chromium/chrome/browser/search_engines/jni_headers/QoraiSearchEnginePrefHelper_jni.h"

#include "qorai/components/qorai_search/browser/prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_service.h"

namespace {
Profile* GetOriginalProfile() {
  return ProfileManager::GetActiveUserProfile()->GetOriginalProfile();
}
}  // namespace

void JNI_QoraiSearchEnginePrefHelper_SetFetchSEFromNative(JNIEnv* env,
                                                          jboolean value) {
  GetOriginalProfile()->GetPrefs()->SetBoolean(
      qorai_search::prefs::kFetchFromNative, value);
}

jboolean JNI_QoraiSearchEnginePrefHelper_GetFetchSEFromNative(JNIEnv* env) {
  return GetOriginalProfile()->GetPrefs()->GetBoolean(
      qorai_search::prefs::kFetchFromNative);
}
