/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "qorai/qorai_domains/android/jni_headers/QorAIDomainsUtils_jni.h"
#include "qorai/qorai_domains/service_domains.h"

namespace qorai_domains {
namespace android {

// Validate that a runtime integer value corresponds to a valid enum value.
// This function performs runtime validation of values passed from JNI.
constexpr bool IsValidServicesEnvironment(jint environment) {
  switch (environment) {
    case qorai_domains::DEV:
    case qorai_domains::STAGING:
    case qorai_domains::PROD:
      return true;
      // No default case - compiler will warn if new enum values are added
  }
  return false;
}

static std::string JNI_QorAIDomainsUtils_GetServicesDomain(JNIEnv* env,
                                                           std::string& prefix,
                                                           jint environment) {
  // Validate that environment is a valid enum value, if not, default to DEV.
  if (!IsValidServicesEnvironment(environment)) {
    environment = static_cast<jint>(qorai_domains::DEV);
  }

  auto env_value = static_cast<qorai_domains::ServicesEnvironment>(environment);
  return qorai_domains::GetServicesDomain(std::move(prefix), env_value);
}

}  // namespace android
}  // namespace qorai_domains
