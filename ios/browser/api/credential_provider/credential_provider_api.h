/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_CREDENTIAL_PROVIDER_CREDENTIAL_PROVIDER_API_H_
#define QORAI_IOS_BROWSER_API_CREDENTIAL_PROVIDER_CREDENTIAL_PROVIDER_API_H_

#import <Foundation/Foundation.h>

@protocol CredentialStore
, Credential;
@class FaviconAttributes;

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
@interface CredentialProviderAPI : NSObject

+ (id<CredentialStore>)credentialStore;

+ (void)loadAttributesForCredential:(id<Credential>)credential
                         completion:(void (^)(FaviconAttributes*))completion;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_CREDENTIAL_PROVIDER_CREDENTIAL_PROVIDER_API_H_
