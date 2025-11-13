/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_ENUMS_H_
#define QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_ENUMS_H_

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, QoraiPublicKeyUsage) {
  QoraiPublicKeyUsage_INVALID = 1 << 0,
  QoraiPublicKeyUsage_ENCRYPT = 1 << 1,
  QoraiPublicKeyUsage_DECRYPT = 1 << 2,
  QoraiPublicKeyUsage_SIGN = 1 << 3,
  QoraiPublicKeyUsage_VERIFY = 1 << 4,
  QoraiPublicKeyUsage_WRAP = 1 << 5,
  QoraiPublicKeyUsage_DERIVE = 1 << 6,
  QoraiPublicKeyUsage_ANY = 1 << 7
};

typedef NS_ENUM(NSUInteger, QoraiPublicKeyType) {
  QoraiPublicKeyType_UNKNOWN,
  QoraiPublicKeyType_RSA,
  QoraiPublicKeyType_DSA,
  QoraiPublicKeyType_DH,
  QoraiPublicKeyType_EC
};

typedef NS_ENUM(NSUInteger, QoraiFingerprintType) {
  QoraiFingerprintType_SHA1,
  QoraiFingerprintType_SHA256
};

#endif  // QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_ENUMS_H_
