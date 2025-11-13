/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_CERTIFICATE_QORAI_CERTIFICATE_H_
#define QORAI_IOS_BROWSER_API_CERTIFICATE_QORAI_CERTIFICATE_H_

#import <Foundation/Foundation.h>
#import <Security/Security.h>

NS_ASSUME_NONNULL_BEGIN

@class QoraiCertificateRDNSequence;
@class QoraiCertificateSignature;
@class QoraiCertificatePublicKeyInfo;
@class QoraiCertificateFingerprint;
// @class QoraiCertificateExtensionModel;

OBJC_EXPORT
@interface QoraiCertificateModel : NSObject
@property(nonatomic, readonly) bool isRootCertificate;
@property(nonatomic, readonly) bool isCertificateAuthority;
@property(nonatomic, readonly) bool isSelfSigned;
@property(nonatomic, readonly) bool isSelfIssued;
@property(nonatomic, readonly) QoraiCertificateRDNSequence* subjectName;
@property(nonatomic, readonly) QoraiCertificateRDNSequence* issuerName;
@property(nonatomic, readonly) NSString* serialNumber;
@property(nonatomic, readonly) NSUInteger version;
@property(nonatomic, readonly) QoraiCertificateSignature* signature;
@property(nonatomic, readonly) NSDate* notValidBefore;
@property(nonatomic, readonly) NSDate* notValidAfter;
@property(nonatomic, readonly) QoraiCertificatePublicKeyInfo* publicKeyInfo;
// @property(nonatomic, readonly)
// NSArray<QoraiCertificateExtensionModel*>* extensions;
@property(nonatomic, readonly) QoraiCertificateFingerprint* sha1Fingerprint;
@property(nonatomic, readonly) QoraiCertificateFingerprint* sha256Fingerprint;

- (nullable instancetype)initWithCertificate:(SecCertificateRef)certificate;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_CERTIFICATE_QORAI_CERTIFICATE_H_
