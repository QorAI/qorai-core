/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_ads/android/qorai_ads_native_helper.h"

#include <string>

#include "base/android/jni_string.h"
#include "base/functional/callback_helpers.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_ads/android/jni_headers/QoraiAdsNativeHelper_jni.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "qorai/components/qorai_ads/core/public/ads_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"

namespace qorai_ads {

// static
jboolean JNI_QoraiAdsNativeHelper_IsOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  return profile->GetPrefs()->GetBoolean(
      qorai_ads::prefs::kOptedInToNotificationAds);
}

// static
void JNI_QoraiAdsNativeHelper_SetOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    jboolean should_enable_ads) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  profile->GetPrefs()->SetBoolean(qorai_ads::prefs::kOptedInToNotificationAds,
                                  should_enable_ads);
}

// static
jboolean JNI_QoraiAdsNativeHelper_IsSupportedRegion(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return false;
  }

  return qorai_ads::IsSupportedRegion();
}

// static
void JNI_QoraiAdsNativeHelper_ClearData(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  ads_service->ClearData(/*intentional*/ base::DoNothing());
}

// static
void JNI_QoraiAdsNativeHelper_OnNotificationAdShown(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    const base::android::JavaParamRef<jstring>& j_notification_id) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  const std::string notification_id =
      base::android::ConvertJavaStringToUTF8(env, j_notification_id);
  ads_service->OnNotificationAdShown(notification_id);
}

// static
void JNI_QoraiAdsNativeHelper_OnNotificationAdClosed(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    const base::android::JavaParamRef<jstring>& j_notification_id,
    jboolean j_by_user) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  const std::string notification_id =
      base::android::ConvertJavaStringToUTF8(env, j_notification_id);
  ads_service->OnNotificationAdClosed(notification_id, j_by_user);
}

// static
void JNI_QoraiAdsNativeHelper_OnNotificationAdClicked(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    const base::android::JavaParamRef<jstring>& j_notification_id) {
  Profile* profile = Profile::FromJavaObject(j_profile_android);
  AdsService* ads_service = AdsServiceFactory::GetForProfile(profile);
  if (!ads_service) {
    return;
  }

  const std::string notification_id =
      base::android::ConvertJavaStringToUTF8(env, j_notification_id);
  ads_service->OnNotificationAdClicked(notification_id);
}

}  // namespace qorai_ads
