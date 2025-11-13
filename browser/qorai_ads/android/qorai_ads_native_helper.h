/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_ANDROID_QORAI_ADS_NATIVE_HELPER_H_
#define QORAI_BROWSER_QORAI_ADS_ANDROID_QORAI_ADS_NATIVE_HELPER_H_

#include "base/android/scoped_java_ref.h"

namespace qorai_ads {

static jboolean JNI_QoraiAdsNativeHelper_IsOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android);

static void JNI_QoraiAdsNativeHelper_SetOptedInToNotificationAds(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    jboolean opted_in);

static jboolean JNI_QoraiAdsNativeHelper_IsSupportedRegion(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android);

static void JNI_QoraiAdsNativeHelper_ClearData(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android);

static void JNI_QoraiAdsNativeHelper_OnNotificationAdShown(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    const base::android::JavaParamRef<jstring>& j_notification_id);

static void JNI_QoraiAdsNativeHelper_OnNotificationAdClosed(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    const base::android::JavaParamRef<jstring>& j_notification_id,
    jboolean j_by_user);

static void JNI_QoraiAdsNativeHelper_OnNotificationAdClicked(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& j_profile_android,
    const base::android::JavaParamRef<jstring>& j_notification_id);

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_ANDROID_QORAI_ADS_NATIVE_HELPER_H_
