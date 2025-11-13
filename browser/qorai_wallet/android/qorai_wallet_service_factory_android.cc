/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"

#include "base/android/jni_android.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "chrome/android/chrome_jni_headers/QoraiWalletServiceFactory_jni.h"
#include "chrome/browser/profiles/profile.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace chrome {
namespace android {

namespace {
template <class T>
jlong BindWalletService(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  auto* profile = Profile::FromJavaObject(profile_android);
  if (auto* qorai_wallet_service =
          qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(
              profile)) {
    mojo::PendingRemote<T> pending;
    qorai_wallet_service->Bind(pending.InitWithNewPipeAndPassReceiver());
    return static_cast<jlong>(pending.PassPipe().release().value());
  }
  return static_cast<jlong>(mojo::kInvalidHandleValue);
}
}  // namespace

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToQoraiWalletService(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::QoraiWalletService>(
      env, profile_android);
}

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToQoraiWalletP3A(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::QoraiWalletP3A>(
      env, profile_android);
}

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToJsonRpcService(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::JsonRpcService>(
      env, profile_android);
}

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToKeyringService(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::KeyringService>(
      env, profile_android);
}

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToTxService(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::TxService>(env,
                                                           profile_android);
}

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToEthTxManagerProxy(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::EthTxManagerProxy>(
      env, profile_android);
}

static jlong JNI_QoraiWalletServiceFactory_GetInterfaceToSolanaTxManagerProxy(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& profile_android) {
  return BindWalletService<qorai_wallet::mojom::SolanaTxManagerProxy>(
      env, profile_android);
}

}  // namespace android
}  // namespace chrome
