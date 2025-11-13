// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_QORAI_DOMAINS_SERVICE_DOMAINS_H_
#define QORAI_IOS_BROWSER_API_QORAI_DOMAINS_SERVICE_DOMAINS_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSInteger QoraiServicesEnvironmentIOS
    NS_TYPED_ENUM NS_SWIFT_NAME(QoraiDomains.ServicesEnvironment);

OBJC_EXPORT QoraiServicesEnvironmentIOS const
    QoraiServicesEnvironmentIOSDevelopment;
OBJC_EXPORT QoraiServicesEnvironmentIOS const
    QoraiServicesEnvironmentIOSStaging;
OBJC_EXPORT QoraiServicesEnvironmentIOS const
    QoraiServicesEnvironmentIOSProduction;

OBJC_EXPORT
@interface QoraiDomains : NSObject
@property(class, nonatomic, readonly) QoraiServicesEnvironmentIOS environment;

+ (QoraiServicesEnvironmentIOS)environmentWithPrefix:(NSString* _Nonnull)prefix
    NS_SWIFT_NAME(enviroment(prefix:));
+ (NSString*)serviceDomainWithPrefix:(NSString*)prefix
    NS_SWIFT_NAME(serviceDomain(prefix:));
+ (NSString*)serviceDomainWithPrefix:(NSString*)prefix
                         environment:(QoraiServicesEnvironmentIOS)environment
    NS_SWIFT_NAME(serviceDomain(prefix:environment:));

- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_DOMAINS_SERVICE_DOMAINS_H_
