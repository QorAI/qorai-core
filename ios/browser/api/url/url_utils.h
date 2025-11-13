/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_URL_URL_UTILS_H_
#define QORAI_IOS_BROWSER_API_URL_URL_UTILS_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
@interface NSURL (Utilities)

+ (nullable NSURL*)URLFromIDNString:(NSString*)idnString
    NS_SWIFT_NAME(init(idnString:));

/// Returns the domain registry
///  google.co.uk -> co.uk
///  google.com -> com
@property(readonly) NSString* qorai_registry NS_SWIFT_NAME(registry);

/// Returns the eTLD+1 including private registries.
@property(readonly)
    NSString* qorai_domainAndRegistry NS_SWIFT_NAME(domainAndRegistry);

/// Returns the eTLD+1 not including private registries.
@property(readonly)
    NSString* qorai_domainAndRegistryExcludingPrivateRegistries NS_SWIFT_NAME(
        domainAndRegistryExcludingPrivateRegistries);

/// Returns `true` when the `host` is an IP address.
@property(readonly) bool qorai_isHostIPAddress NS_SWIFT_NAME(isHostIPAddress);

/// The string representation of a URL is called the spec.
/// Returns the canonicalized URL's spec.
@property(readonly) NSString* qorai_spec NS_SWIFT_NAME(spec);

/// Appends the key=value query parameter, escaping if needed.
- (NSURL*)qorai_addingQueryParameter:(NSString*)key
                               value:(NSString*)value
    NS_SWIFT_NAME(addingQueryParameter(key:value:));

/// Appends OR Replaces the key=value query parameter, escaping if needed.
- (NSURL*)qorai_replacingQueryParameter:(NSString*)key
                                  value:(NSString*)value
    NS_SWIFT_NAME(replacingQueryParameter(key:value:));

/// Returns the value for the query parameter. NULL if no parameter exists.
- (nullable NSString*)qorai_valueForQueryParameter:(NSString*)key
    NS_SWIFT_NAME(valueForQueryParameter(key:));

/// Returns true if the URL has a scheme.
- (bool)qorai_hasScheme:(NSString*)scheme NS_SWIFT_NAME(hasScheme(scheme:));
@end

OBJC_EXPORT
@interface NSURL (StaticUtilities)

/// Returns the domain registry
///  google.co.uk -> co.uk
///  google.com -> com
+ (NSString*)qorai_registryFromHost:(NSString*)host
    NS_SWIFT_NAME(registry(host:));

/// Returns the eTLD+1 including private registries.
+ (NSString*)qorai_domainAndRegistryFromHost:(NSString*)host
    NS_SWIFT_NAME(domainAndRegistry(host:));

/// Returns the eTLD+1 not including private registries.
+ (NSString*)qorai_domainAndRegistryExcludingPrivateRegistriesFromHost:
    (NSString*)host
    NS_SWIFT_NAME(domainAndRegistryExcludingPrivateRegistries(host:));

/// Returns `true` when the `host` is an IP address.
+ (bool)qorai_isHostIPAddressFromHost:(NSString*)host
    NS_SWIFT_NAME(isHostIPAddress(host:));
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_URL_URL_UTILS_H_
