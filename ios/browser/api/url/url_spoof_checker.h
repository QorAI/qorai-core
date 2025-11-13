/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_URL_URL_SPOOF_CHECKER_H_
#define QORAI_IOS_BROWSER_API_URL_URL_SPOOF_CHECKER_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The |SkeletonType| and |TopDomainEntry| are mirrored in trie_entry.h. These
/// are used to insert and read nodes from the Trie.
/// The type of skeleton in the trie node.
typedef NSInteger QoraiSpoofCheckerSkeletonType NS_TYPED_ENUM
    NS_SWIFT_NAME(URLSpoofChecker.SkeletonType);
OBJC_EXPORT QoraiSpoofCheckerSkeletonType const
    QoraiSpoofCheckerSkeletonTypeFull;
OBJC_EXPORT QoraiSpoofCheckerSkeletonType const
    QoraiSpoofCheckerSkeletonTypeSeparatorsRemoved;

typedef NSInteger QoraiSpoofCheckerLookalikeURLMatchType NS_TYPED_ENUM
    NS_SWIFT_NAME(URLSpoofChecker.LookalikeURLMatchType);

OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeNone;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeSkeletonMatchSiteEngagement;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeEditDistance;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeEditDistanceSiteEngagement;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeTargetEmbedding;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeSkeletonMatchTop500;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeSkeletonMatchTop5k;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeTargetEmbeddingForSafetyTips;
/// The domain name failed IDN spoof checks but didn't match a safe hostname.
/// As a result, there is no URL to suggest to the user in the form of "Did
/// you mean <url>?".
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeFailedSpoofChecks;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeCharacterSwapSiteEngagement;
OBJC_EXPORT QoraiSpoofCheckerLookalikeURLMatchType const
    QoraiSpoofCheckerLookalikeURLMatchTypeCharacterSwapTop500;

OBJC_EXPORT
NS_SWIFT_NAME(URLSpoofChecker.TopDomainEntry)
@interface URLSpoofCheckerTopDomainEntry : NSObject
- (instancetype)init NS_UNAVAILABLE;
/// The domain name.
@property(nonatomic, readonly) NSString* domain;
/// True if the domain is in the top 1000 bucket.
@property(nonatomic, readonly) bool isTopBucket;
/// Type of the skeleton stored in the trie node.
@property(nonatomic, readonly) QoraiSpoofCheckerSkeletonType skeletonType;
@end

OBJC_EXPORT
NS_SWIFT_NAME(URLSpoofChecker.Result)
@interface QoraiURLSpoofCheckerResult : NSObject
- (instancetype)init NS_UNAVAILABLE;
@property(nonatomic, readonly)
    QoraiSpoofCheckerLookalikeURLMatchType urlMatchType;
@property(nonatomic, readonly, nullable) NSURL* suggestedURL;
@end

OBJC_EXPORT
NS_SWIFT_NAME(URLSpoofChecker)
@interface QoraiURLSpoofChecker : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (URLSpoofCheckerTopDomainEntry*)getSimilarTopDomain:(NSString*)hostname;
+ (URLSpoofCheckerTopDomainEntry*)lookupSkeletonInTopDomains:
    (NSString*)hostname;
+ (NSArray<NSString*>*)getSkeletons:(NSString*)url;
+ (QoraiURLSpoofCheckerResult*)isLookalikeURL:(NSString*)url;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_URL_URL_SPOOF_CHECKER_H_
