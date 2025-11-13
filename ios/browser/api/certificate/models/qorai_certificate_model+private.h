/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_MODEL_PRIVATE_H_
#define QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_MODEL_PRIVATE_H_

#import <Foundation/Foundation.h>
#import <Security/Security.h>

#include "qorai/ios/browser/api/certificate/models/qorai_certificate_enums.h"
#include "qorai/ios/browser/api/certificate/models/qorai_certificate_fingerprint.h"
#include "qorai/ios/browser/api/certificate/models/qorai_certificate_public_key_info.h"
#include "qorai/ios/browser/api/certificate/models/qorai_certificate_rdns_sequence.h"
#include "qorai/ios/browser/api/certificate/models/qorai_certificate_signature.h"

namespace bssl {
class ParsedCertificate;

namespace der {
class BitString;
class Input;
}  // namespace der
}  // namespace bssl

typedef NS_ENUM(NSUInteger, QoraiFingerprintType);

NS_ASSUME_NONNULL_BEGIN

@interface QoraiCertificateSignature ()
- (instancetype)initWithCertificate:(const bssl::ParsedCertificate*)certificate;
@end

@interface QoraiCertificatePublicKeyInfo ()
- (instancetype)initWithCertificate:(const bssl::ParsedCertificate*)certificate
                            withKey:(SecKeyRef)key;
@end

@interface QoraiCertificateFingerprint ()
- (instancetype)initWithCertificate:(CFDataRef)cert_data
                           withType:(QoraiFingerprintType)type;
@end

@interface QoraiCertificateRDNSequence ()
- (instancetype)initWithBERName:(const bssl::der::Input&)berName
                       uniqueId:(const bssl::der::BitString&)uniqueId;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_CERTIFICATE_MODELS_QORAI_CERTIFICATE_MODEL_PRIVATE_H_
