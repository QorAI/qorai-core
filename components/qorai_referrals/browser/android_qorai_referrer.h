/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REFERRALS_BROWSER_ANDROID_QORAI_REFERRER_H_
#define QORAI_COMPONENTS_QORAI_REFERRALS_BROWSER_ANDROID_QORAI_REFERRER_H_

#include <jni.h>
#include <memory>
#include <string>
#include <vector>

#include "base/android/scoped_java_ref.h"
#include "net/base/completion_once_callback.h"

namespace android_qorai_referrer {

using InitReferrerCallback = base::OnceCallback<void()>;

class QoraiReferrer {
 public:
  explicit QoraiReferrer();
  ~QoraiReferrer();

  QoraiReferrer(const QoraiReferrer&) = delete;
  QoraiReferrer& operator=(const QoraiReferrer&) = delete;

  void InitReferrer(InitReferrerCallback init_referrer_callback);
  void OnReferrerReady(JNIEnv* env);

 private:
  base::android::ScopedJavaGlobalRef<jobject> java_obj_;
  InitReferrerCallback init_referrer_callback_;
};

}  // namespace android_qorai_referrer

#endif  // QORAI_COMPONENTS_QORAI_REFERRALS_BROWSER_ANDROID_QORAI_REFERRER_H_
