/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_PUBLIC_KEY_INFO_H_
#define QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_PUBLIC_KEY_INFO_H_

#import <Foundation/Foundation.h>
#include "qorai_certificate_enums.h"  // NOLINT

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
@interface QoraiCertificatePublicKeyInfo : NSObject
@property(nonatomic, readonly) QoraiPublicKeyType type;
@property(nonatomic, readonly) NSString* algorithm;
@property(nonatomic, readonly) NSData* objectIdentifier;
@property(nonatomic, readonly) NSString* absoluteObjectIdentifier;
@property(nonatomic, readonly) NSString* curveName;
@property(nonatomic, readonly) NSString* nistCurveName;
@property(nonatomic, readonly) NSString* parameters;
@property(nonatomic, readonly) NSString* keyHexEncoded;
@property(nonatomic, readonly) NSUInteger keyBytesSize;
@property(nonatomic, readonly) NSUInteger effectiveSize;
@property(nonatomic, readonly) NSUInteger exponent;
@property(nonatomic, readonly) NSUInteger keySizeInBits;
@property(nonatomic, readonly) QoraiPublicKeyUsage keyUsage;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_PUBLIC_KEY_INFO_H_
