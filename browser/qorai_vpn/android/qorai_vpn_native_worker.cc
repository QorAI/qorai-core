/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/android/qorai_vpn_native_worker.h"

#include "base/android/jni_android.h"
#include "base/android/jni_array.h"
#include "base/android/jni_string.h"
#include "base/functional/bind.h"
#include "base/json/json_writer.h"
#include "base/values.h"
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "chrome/android/chrome_jni_headers/QoraiVpnNativeWorker_jni.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"

using qorai_vpn::QoraiVpnService;

namespace {

QoraiVpnService* GetQoraiVpnService() {
  return qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
}

}  // namespace

namespace chrome {
namespace android {

QoraiVpnNativeWorker::QoraiVpnNativeWorker(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& obj)
    : weak_java_qorai_vpn_native_worker_(env, obj), weak_factory_(this) {
  Java_QoraiVpnNativeWorker_setNativePtr(env, obj,
                                         reinterpret_cast<intptr_t>(this));
}

QoraiVpnNativeWorker::~QoraiVpnNativeWorker() {}

void QoraiVpnNativeWorker::Destroy(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  delete this;
}

void QoraiVpnNativeWorker::GetTimezonesForRegions(JNIEnv* env) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->GetTimezonesForRegions(
        base::BindOnce(&QoraiVpnNativeWorker::OnGetTimezonesForRegions,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiVpnNativeWorker::OnGetTimezonesForRegions(
    const std::string& timezones_json,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onGetTimezonesForRegions(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, timezones_json), success);
}

void QoraiVpnNativeWorker::GetHostnamesForRegion(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& region,
    const base::android::JavaParamRef<jstring>& region_precision) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->GetHostnamesForRegion(
        base::BindOnce(&QoraiVpnNativeWorker::OnGetHostnamesForRegion,
                       weak_factory_.GetWeakPtr()),
        base::android::ConvertJavaStringToUTF8(env, region),
        base::android::ConvertJavaStringToUTF8(env, region_precision));
  }
}

void QoraiVpnNativeWorker::OnGetHostnamesForRegion(
    const std::string& hostnames_json,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onGetHostnamesForRegion(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, hostnames_json), success);
}

void QoraiVpnNativeWorker::GetWireguardProfileCredentials(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& subscriber_credential,
    const base::android::JavaParamRef<jstring>& public_key,
    const base::android::JavaParamRef<jstring>& hostname) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->GetWireguardProfileCredentials(
        base::BindOnce(&QoraiVpnNativeWorker::OnGetWireguardProfileCredentials,
                       weak_factory_.GetWeakPtr()),
        base::android::ConvertJavaStringToUTF8(env, subscriber_credential),
        base::android::ConvertJavaStringToUTF8(env, public_key),
        base::android::ConvertJavaStringToUTF8(env, hostname));
  }
}

void QoraiVpnNativeWorker::OnGetWireguardProfileCredentials(
    const std::string& wireguard_profile_credentials_json,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onGetWireguardProfileCredentials(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(
          env, wireguard_profile_credentials_json),
      success);
}

void QoraiVpnNativeWorker::VerifyCredentials(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& hostname,
    const base::android::JavaParamRef<jstring>& client_id,
    const base::android::JavaParamRef<jstring>& subscriber_credential,
    const base::android::JavaParamRef<jstring>& api_auth_token) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->VerifyCredentials(
        base::BindOnce(&QoraiVpnNativeWorker::OnVerifyCredentials,
                       weak_factory_.GetWeakPtr()),
        base::android::ConvertJavaStringToUTF8(env, hostname),
        base::android::ConvertJavaStringToUTF8(env, client_id),
        base::android::ConvertJavaStringToUTF8(env, subscriber_credential),
        base::android::ConvertJavaStringToUTF8(env, api_auth_token));
  }
}

void QoraiVpnNativeWorker::OnVerifyCredentials(
    const std::string& verify_credentials_json,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onVerifyCredentials(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, verify_credentials_json),
      success);
}

void QoraiVpnNativeWorker::InvalidateCredentials(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& hostname,
    const base::android::JavaParamRef<jstring>& client_id,
    const base::android::JavaParamRef<jstring>& subscriber_credential,
    const base::android::JavaParamRef<jstring>& api_auth_token) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->InvalidateCredentials(
        base::BindOnce(&QoraiVpnNativeWorker::OnInvalidateCredentials,
                       weak_factory_.GetWeakPtr()),
        base::android::ConvertJavaStringToUTF8(env, hostname),
        base::android::ConvertJavaStringToUTF8(env, client_id),
        base::android::ConvertJavaStringToUTF8(env, subscriber_credential),
        base::android::ConvertJavaStringToUTF8(env, api_auth_token));
  }
}

void QoraiVpnNativeWorker::OnInvalidateCredentials(
    const std::string& invalidate_credentials_json,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onInvalidateCredentials(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, invalidate_credentials_json),
      success);
}

void QoraiVpnNativeWorker::GetSubscriberCredential(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& product_type,
    const base::android::JavaParamRef<jstring>& product_id,
    const base::android::JavaParamRef<jstring>& validation_method,
    const base::android::JavaParamRef<jstring>& purchase_token,
    const base::android::JavaParamRef<jstring>& bundle_id) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->GetSubscriberCredential(
        base::BindOnce(&QoraiVpnNativeWorker::OnGetSubscriberCredential,
                       weak_factory_.GetWeakPtr()),
        base::android::ConvertJavaStringToUTF8(env, product_type),
        base::android::ConvertJavaStringToUTF8(env, product_id),
        base::android::ConvertJavaStringToUTF8(env, validation_method),
        base::android::ConvertJavaStringToUTF8(env, purchase_token),
        base::android::ConvertJavaStringToUTF8(env, bundle_id));
  }
}

void QoraiVpnNativeWorker::GetSubscriberCredentialV12(JNIEnv* env) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->GetSubscriberCredentialV12(
        base::BindOnce(&QoraiVpnNativeWorker::OnGetSubscriberCredential,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiVpnNativeWorker::OnGetSubscriberCredential(
    const std::string& subscriber_credential,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onGetSubscriberCredential(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, subscriber_credential),
      success);
}

void QoraiVpnNativeWorker::VerifyPurchaseToken(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& purchase_token,
    const base::android::JavaParamRef<jstring>& product_id,
    const base::android::JavaParamRef<jstring>& product_type,
    const base::android::JavaParamRef<jstring>& bundle_id) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->VerifyPurchaseToken(
        base::BindOnce(
            &QoraiVpnNativeWorker::OnVerifyPurchaseToken,
            weak_factory_.GetWeakPtr(),
            base::android::ConvertJavaStringToUTF8(env, purchase_token),
            base::android::ConvertJavaStringToUTF8(env, product_id)),
        base::android::ConvertJavaStringToUTF8(env, purchase_token),
        base::android::ConvertJavaStringToUTF8(env, product_id),
        base::android::ConvertJavaStringToUTF8(env, product_type),
        base::android::ConvertJavaStringToUTF8(env, bundle_id));
  }
}

void QoraiVpnNativeWorker::OnVerifyPurchaseToken(
    const std::string& purchase_token,
    const std::string& product_id,
    const std::string& json_response,
    bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiVpnNativeWorker_onVerifyPurchaseToken(
      env, weak_java_qorai_vpn_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, json_response),
      base::android::ConvertUTF8ToJavaString(env, purchase_token),
      base::android::ConvertUTF8ToJavaString(env, product_id), success);
}

jboolean QoraiVpnNativeWorker::IsPurchasedUser(JNIEnv* env) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    return qorai_vpn_service->is_purchased_user();
  }

  return false;
}

void QoraiVpnNativeWorker::ReloadPurchasedState(JNIEnv* env) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->ReloadPurchasedState();
  }
}

void QoraiVpnNativeWorker::ReportForegroundP3A(JNIEnv* env) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    // Reporting a new session to P3A functions.
    qorai_vpn_service->qorai_vpn_metrics()->RecordAllMetrics(true);
  }
}

void QoraiVpnNativeWorker::ReportBackgroundP3A(JNIEnv* env,
                                               jlong session_start_time_ms,
                                               jlong session_end_time_ms) {
  QoraiVpnService* qorai_vpn_service = GetQoraiVpnService();
  if (qorai_vpn_service) {
    qorai_vpn_service->RecordAndroidBackgroundP3A(session_start_time_ms,
                                                  session_end_time_ms);
  }
}

static void JNI_QoraiVpnNativeWorker_Init(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  new QoraiVpnNativeWorker(env, jcaller);
}

}  // namespace android
}  // namespace chrome
