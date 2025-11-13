/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_URL_URL_FORMATTER_H_
#define QORAI_IOS_BROWSER_API_URL_URL_FORMATTER_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSInteger QoraiURLSchemeDisplay NS_TYPED_ENUM
    NS_SWIFT_NAME(URLFormatter.SchemeDisplay);

OBJC_EXPORT QoraiURLSchemeDisplay const QoraiURLSchemeDisplayShow;
OBJC_EXPORT QoraiURLSchemeDisplay const QoraiURLSchemeDisplayOmitHttpAndHttps;
/// Omit cryptographic (i.e. https and wss).
OBJC_EXPORT QoraiURLSchemeDisplay const QoraiURLSchemeDisplayOmitCryptographic;

NS_SWIFT_NAME(URLFormatter.FormatType)
typedef NS_OPTIONS(NSUInteger, QoraiURLFormatterFormatType) {
  QoraiURLFormatterFormatTypeOmitNothing = 0,
  QoraiURLFormatterFormatTypeOmitUsernamePassword = 1 << 0,
  QoraiURLFormatterFormatTypeOmitHTTP = 1 << 1,
  QoraiURLFormatterFormatTypeOmitTrailingSlashOnBareHostname = 1 << 2,
  QoraiURLFormatterFormatTypeOmitHTTPS = 1 << 3,
  QoraiURLFormatterFormatTypeOmitTrivialSubdomains = 1 << 5,
  QoraiURLFormatterFormatTypeTrimAfterHost = 1 << 6,
  QoraiURLFormatterFormatTypeOmitFileScheme = 1 << 7,
  QoraiURLFormatterFormatTypeOmitMailToScheme = 1 << 8,
  QoraiURLFormatterFormatTypeOmitMobilePrefix = 1 << 9,

  /// Omits Username & Password, HTTP (not HTTPS), and Trailing Slash
  QoraiURLFormatterFormatTypeOmitDefaults =
      QoraiURLFormatterFormatTypeOmitUsernamePassword |
      QoraiURLFormatterFormatTypeOmitHTTP |
      QoraiURLFormatterFormatTypeOmitTrailingSlashOnBareHostname
};

NS_SWIFT_NAME(URLFormatter.UnescapeRule)
typedef NS_OPTIONS(NSUInteger, QoraiURLFormatterUnescapeRule) {
  QoraiURLFormatterUnescapeRuleNone = 0,
  QoraiURLFormatterUnescapeRuleNormal = 1 << 0,
  QoraiURLFormatterUnescapeRuleSpaces = 1 << 1,
  QoraiURLFormatterUnescapeRulePathSeparators = 1 << 2,
  QoraiURLFormatterUnescapeRuleSpecialCharsExceptPathSeparators = 1 << 3,
  QoraiURLFormatterUnescapeRuleReplacePlusWithSpace = 1 << 4
};

OBJC_EXPORT
NS_SWIFT_NAME(URLFormatter)
@interface QoraiURLFormatter : NSObject
- (instancetype)init NS_UNAVAILABLE;

/// Format a URL "origin/host" for Security Display
/// origin - The origin of the URL to format
/// schemeDisplay - Determines whether or not to omit the scheme
+ (NSString*)formatURLOriginForSecurityDisplay:(NSString*)origin
                                 schemeDisplay:
                                     (QoraiURLSchemeDisplay)schemeDisplay;

/// Format a URL "origin/host" omitting the scheme, path, and trivial
/// sub-domains. origin - The origin to be formatted
+ (NSString*)formatURLOriginForDisplayOmitSchemePathAndTrivialSubdomains:
    (NSString*)origin;

/// Format a URL
/// url - The URL string to be formatted
/// formatTypes - Formatter options when formatting the URL. Typically used to
/// omit certain parts of a URL unescapeOptions - Options passed to the
/// formatter for UN-Escaping parts of a URL
+ (NSString*)formatURL:(NSString*)url
           formatTypes:(QoraiURLFormatterFormatType)formatTypes
       unescapeOptions:(QoraiURLFormatterUnescapeRule)unescapeOptions;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_URL_URL_FORMATTER_H_
