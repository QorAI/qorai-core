/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_FINGERPRINT_H_
#define QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_FINGERPRINT_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, QoraiFingerprintType);

OBJC_EXPORT
@interface QoraiCertificateFingerprint : NSObject
@property(nonatomic, readonly) QoraiFingerprintType type;
@property(nonatomic, readonly) NSString* fingerprintHexEncoded;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_FINGERPRINT_H_
