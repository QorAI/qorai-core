/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/android/qorai_shields_content_settings.h"

#include <string>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/check.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "chrome/android/chrome_jni_headers/QoraiShieldsContentSettings_jni.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/content_settings/core/browser/content_settings_utils.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "url/gurl.h"

namespace chrome {
namespace android {


// That class is linked to a global toolbar. It's a one instance on Android
QoraiShieldsContentSettings* g_qorai_shields_content_settings = nullptr;

static void JNI_QoraiShieldsContentSettings_Init(JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  g_qorai_shields_content_settings =
      new QoraiShieldsContentSettings(env, jcaller);
}

QoraiShieldsContentSettings::QoraiShieldsContentSettings(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& obj)
    : jobj_(base::android::ScopedJavaGlobalRef<jobject>(obj)) {
  Java_QoraiShieldsContentSettings_setNativePtr(env, obj,
      reinterpret_cast<intptr_t>(this));
}

QoraiShieldsContentSettings::~QoraiShieldsContentSettings() {
}

void QoraiShieldsContentSettings::Destroy(JNIEnv* env) {
  g_qorai_shields_content_settings = nullptr;
  delete this;
}

void QoraiShieldsContentSettings::DispatchBlockedEventToJava(int tab_id,
        const std::string& block_type, const std::string& subresource) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiShieldsContentSettings_blockedEvent(
      env, jobj_, tab_id,
      base::android::ConvertUTF8ToJavaString(env, block_type),
      base::android::ConvertUTF8ToJavaString(env, subresource));
}

void QoraiShieldsContentSettings::DispatchSavedBandwidthToJava(
  uint64_t savings) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiShieldsContentSettings_savedBandwidth(env, jobj_, savings);
}

void QoraiShieldsContentSettings::DispatchSavedBandwidth(uint64_t savings) {
  DCHECK(g_qorai_shields_content_settings);
  if (!g_qorai_shields_content_settings) {
    return;
  }
  g_qorai_shields_content_settings->DispatchSavedBandwidthToJava(savings);
}

// static
void QoraiShieldsContentSettings::DispatchBlockedEvent(int tab_id,
  const std::string& block_type, const std::string& subresource) {
  DCHECK(g_qorai_shields_content_settings);
  if (!g_qorai_shields_content_settings) {
    return;
  }
  g_qorai_shields_content_settings->DispatchBlockedEventToJava(tab_id,
      block_type, subresource);
}

void JNI_QoraiShieldsContentSettings_SetQoraiShieldsEnabled(JNIEnv* env,
    jboolean enabled,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetQoraiShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      enabled, GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

jboolean JNI_QoraiShieldsContentSettings_GetQoraiShieldsEnabled(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  return qorai_shields::GetQoraiShieldsEnabled(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)));
}

void JNI_QoraiShieldsContentSettings_SetAdControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_QoraiShieldsContentSettings_GetAdControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::ControlType control_type = qorai_shields::GetAdControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      qorai_shields::ControlTypeToString(control_type));
}

void JNI_QoraiShieldsContentSettings_SetCookieControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      Profile::FromJavaObject(j_profile)->GetPrefs(),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

void JNI_QoraiShieldsContentSettings_SetCosmeticFilteringControlType(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetCosmeticFilteringControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state(),
      Profile::FromJavaObject(j_profile)->GetPrefs());
}

void JNI_QoraiShieldsContentSettings_ResetCosmeticFilter(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url) {
  g_qorai_browser_process->ad_block_service()->ResetCosmeticFilter(
      GURL(base::android::ConvertJavaStringToUTF8(env, url)).host());
}

jboolean JNI_QoraiShieldsContentSettings_AreAnyBlockedElementsPresent(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url) {
  return g_qorai_browser_process->ad_block_service()
      ->AreAnyBlockedElementsPresent(
          GURL(base::android::ConvertJavaStringToUTF8(env, url)).host());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_QoraiShieldsContentSettings_GetCookieControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::ControlType control_type = qorai_shields::GetCookieControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      CookieSettingsFactory::GetForProfile(Profile::FromJavaObject(j_profile))
          .get(),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      qorai_shields::ControlTypeToString(control_type));
}

void JNI_QoraiShieldsContentSettings_SetFingerprintingControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetFingerprintingControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state(),
      Profile::FromJavaObject(j_profile)->GetPrefs());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_QoraiShieldsContentSettings_GetFingerprintingControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::ControlType control_type =
      qorai_shields::GetFingerprintingControlType(
          HostContentSettingsMapFactory::GetForProfile(
              Profile::FromJavaObject(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(
      env, qorai_shields::ControlTypeToString(control_type));
}

void JNI_QoraiShieldsContentSettings_SetHttpsUpgradeControlType(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetHttpsUpgradeControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
JNI_QoraiShieldsContentSettings_GetHttpsUpgradeControlType(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::ControlType control_type =
      qorai_shields::GetHttpsUpgradeControlType(
          HostContentSettingsMapFactory::GetForProfile(
              Profile::FromJavaObject(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      qorai_shields::ControlTypeToString(control_type));
}

base::android::ScopedJavaLocalRef<jstring>
JNI_QoraiShieldsContentSettings_GetCosmeticFilteringControlType(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::ControlType cosmetic_type =
      qorai_shields::GetCosmeticFilteringControlType(
          HostContentSettingsMapFactory::GetForProfile(
              Profile::FromJavaObject(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(
      env, qorai_shields::ControlTypeToString(cosmetic_type));
}

void JNI_QoraiShieldsContentSettings_SetNoScriptControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& type,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::SetNoScriptControlType(
      HostContentSettingsMapFactory::GetForProfile(
          Profile::FromJavaObject(j_profile)),
      qorai_shields::ControlTypeFromString(
          base::android::ConvertJavaStringToUTF8(env, type)),
      GURL(base::android::ConvertJavaStringToUTF8(env, url)),
      g_browser_process->local_state());
}

base::android::ScopedJavaLocalRef<jstring>
    JNI_QoraiShieldsContentSettings_GetNoScriptControlType(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  qorai_shields::ControlType control_type =
      qorai_shields::GetNoScriptControlType(
          HostContentSettingsMapFactory::GetForProfile(
              Profile::FromJavaObject(j_profile)),
          GURL(base::android::ConvertJavaStringToUTF8(env, url)));

  return base::android::ConvertUTF8ToJavaString(env,
      qorai_shields::ControlTypeToString(control_type));
}

void JNI_QoraiShieldsContentSettings_SetForgetFirstPartyStorageEnabled(
    JNIEnv* env,
    jboolean enabled,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  auto* qorai_shields_settings =
      QoraiShieldsSettingsServiceFactory::GetForProfile(
          Profile::FromJavaObject(j_profile));
  qorai_shields_settings->SetForgetFirstPartyStorageEnabled(
      enabled, GURL(base::android::ConvertJavaStringToUTF8(env, url)));
}

jboolean JNI_QoraiShieldsContentSettings_GetForgetFirstPartyStorageEnabled(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& url,
    const base::android::JavaParamRef<jobject>& j_profile) {
  auto* qorai_shields_settings =
      QoraiShieldsSettingsServiceFactory::GetForProfile(
          Profile::FromJavaObject(j_profile));
  return qorai_shields_settings->GetForgetFirstPartyStorageEnabled(
      GURL(base::android::ConvertJavaStringToUTF8(env, url)));
}

}  // namespace android
}  // namespace chrome
