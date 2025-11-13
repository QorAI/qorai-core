/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/check.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/decentralized_dns/core/utils.h"
#include "chrome/android/chrome_jni_headers/WalletNativeUtils_jni.h"
#include "chrome/browser/profiles/profile.h"

namespace chrome {
namespace android {

static void JNI_WalletNativeUtils_ResetWallet(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  auto* profile = Profile::FromJavaObject(profile_android);
  DCHECK(profile);

  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(profile);
  if (qorai_wallet_service) {
    qorai_wallet_service->Reset();
  }
}

static jboolean JNI_WalletNativeUtils_IsUnstoppableDomainsTld(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& domain) {
  auto domain_string = base::android::ConvertJavaStringToUTF8(env, domain);

  return decentralized_dns::IsUnstoppableDomainsTLD(domain_string);
}

static jboolean JNI_WalletNativeUtils_IsEnsTld(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& domain) {
  auto domain_string = base::android::ConvertJavaStringToUTF8(env, domain);

  return decentralized_dns::IsENSTLD(domain_string);
}

static jboolean JNI_WalletNativeUtils_IsSnsTld(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& domain) {
  auto domain_string = base::android::ConvertJavaStringToUTF8(env, domain);

  return decentralized_dns::IsSnsTLD(domain_string);
}

}  // namespace android
}  // namespace chrome
