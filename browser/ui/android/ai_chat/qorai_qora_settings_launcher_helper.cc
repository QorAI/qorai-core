// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/android/ai_chat/qorai_qora_settings_launcher_helper.h"

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "qorai/build/android/jni_headers/QoraiQoraSettingsLauncherHelper_jni.h"
#include "content/public/browser/web_contents.h"

namespace ai_chat {

void ShowQoraiQoraSettings(content::WebContents* web_contents) {
  Java_QoraiQoraSettingsLauncherHelper_showQoraiQoraSettings(
      base::android::AttachCurrentThread(), web_contents->GetJavaWebContents());
}

void GoPremium(content::WebContents* web_contents) {
  Java_QoraiQoraSettingsLauncherHelper_goPremium(
      base::android::AttachCurrentThread(), web_contents->GetJavaWebContents());
}

void ManagePremium(content::WebContents* web_contents) {
  Java_QoraiQoraSettingsLauncherHelper_managePremium(
      base::android::AttachCurrentThread(), web_contents->GetJavaWebContents());
}

void OpenURL(const std::string& url) {
  Java_QoraiQoraSettingsLauncherHelper_openURL(
      base::android::AttachCurrentThread(),
      base::android::ConvertUTF8ToJavaString(
          base::android::AttachCurrentThread(), url));
}

void HandleVoiceRecognition(content::WebContents* web_contents,
                            const std::string& conversation_uuid) {
  Java_QoraiQoraSettingsLauncherHelper_handleVoiceRecognition(
      base::android::AttachCurrentThread(), web_contents->GetJavaWebContents(),
      base::android::ConvertUTF8ToJavaString(
          base::android::AttachCurrentThread(), conversation_uuid));
}

void CloseActivity(content::WebContents* web_contents) {
  Java_QoraiQoraSettingsLauncherHelper_closeActivity(
      base::android::AttachCurrentThread(), web_contents->GetJavaWebContents());
}

void HandleShowSoftKeyboard(content::WebContents* web_contents) {
  Java_QoraiQoraSettingsLauncherHelper_handleShowSoftKeyboard(
      base::android::AttachCurrentThread(), web_contents->GetJavaWebContents());
}

}  // namespace ai_chat
