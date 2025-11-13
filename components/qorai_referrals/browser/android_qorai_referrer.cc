/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_referrals/browser/android_qorai_referrer.h"

#include <utility>

#include "base/android/jni_android.h"
#include "qorai/components/qorai_referrals/browser/jni_headers/QoraiReferrer_jni.h"

namespace android_qorai_referrer {

QoraiReferrer::QoraiReferrer() {
  JNIEnv* env = base::android::AttachCurrentThread();
  java_obj_ = Java_QoraiReferrer_create(env, reinterpret_cast<intptr_t>(this));
}

QoraiReferrer::~QoraiReferrer() {
  Java_QoraiReferrer_destroy(base::android::AttachCurrentThread(), java_obj_);
}

void QoraiReferrer::InitReferrer(InitReferrerCallback init_referrer_callback) {
  init_referrer_callback_ = std::move(init_referrer_callback);
  JNIEnv* env = base::android::AttachCurrentThread();
  return Java_QoraiReferrer_initReferrer(env, java_obj_);
}

void QoraiReferrer::OnReferrerReady(JNIEnv* env) {
  std::move(init_referrer_callback_).Run();
}

}  // namespace android_qorai_referrer
