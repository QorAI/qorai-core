/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/android/youtube_script_injector/qorai_youtube_script_injector_native_helper.h"

#include "base/android/jni_android.h"
#include "qorai/browser/android/youtube_script_injector/youtube_script_injector_tab_helper.h"
#include "chrome/android/chrome_jni_headers/QoraiYouTubeScriptInjectorNativeHelper_jni.h"
#include "content/public/browser/web_contents.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"

namespace youtube_script_injector {

// static
void JNI_QoraiYouTubeScriptInjectorNativeHelper_SetFullscreen(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jweb_contents) {
  content::WebContents* web_contents =
      content::WebContents::FromJavaWebContents(jweb_contents);
  YouTubeScriptInjectorTabHelper* helper =
      YouTubeScriptInjectorTabHelper::FromWebContents(web_contents);
  if (!helper) {
    return;
  }

  helper->MaybeSetFullscreen();
}

// static
jboolean JNI_QoraiYouTubeScriptInjectorNativeHelper_HasFullscreenBeenRequested(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jweb_contents) {
  content::WebContents* web_contents =
      content::WebContents::FromJavaWebContents(jweb_contents);

  YouTubeScriptInjectorTabHelper* helper =
      YouTubeScriptInjectorTabHelper::FromWebContents(web_contents);
  if (!helper) {
    return false;
  }

  return helper->HasFullscreenBeenRequested();
}

// static
jboolean JNI_QoraiYouTubeScriptInjectorNativeHelper_IsPictureInPictureAvailable(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jweb_contents) {
  content::WebContents* web_contents =
      content::WebContents::FromJavaWebContents(jweb_contents);

  YouTubeScriptInjectorTabHelper* helper =
      YouTubeScriptInjectorTabHelper::FromWebContents(web_contents);
  if (helper) {
    return helper->IsPictureInPictureAvailable();
  }

  return false;
}

// static
void EnterPictureInPicture(content::WebContents* web_contents) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiYouTubeScriptInjectorNativeHelper_enterPictureInPicture(
      env, web_contents->GetJavaWebContents());
}

}  // namespace youtube_script_injector
