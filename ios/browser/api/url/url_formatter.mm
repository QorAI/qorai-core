/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/api/url/url_formatter.h"

#include "base/functional/bind.h"
#include "base/functional/callback.h"
#include "base/strings/string_util.h"
#include "base/strings/sys_string_conversions.h"
#include "build/build_config.h"
#include "components/url_formatter/elide_url.h"
#include "components/url_formatter/url_formatter.h"
#include "net/base/apple/url_conversions.h"
#include "url/gurl.h"
#include "url/origin.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

// MARK: - SchemeDisplay
QoraiURLSchemeDisplay const QoraiURLSchemeDisplayShow =
    static_cast<NSInteger>(url_formatter::SchemeDisplay::SHOW);
QoraiURLSchemeDisplay const QoraiURLSchemeDisplayOmitHttpAndHttps =
    static_cast<NSInteger>(url_formatter::SchemeDisplay::OMIT_HTTP_AND_HTTPS);
/// Omit cryptographic (i.e. https and wss).
QoraiURLSchemeDisplay const QoraiURLSchemeDisplayOmitCryptographic =
    static_cast<NSInteger>(url_formatter::SchemeDisplay::OMIT_CRYPTOGRAPHIC);

// MARK: - Implementation

namespace {
constexpr char16_t kChromeSchema16[] = u"chrome://";
constexpr char16_t kQoraiSchema16[] = u"qorai://";
}  // namespace

namespace qorai_utils {

bool ReplaceChromeToQoraiScheme(std::u16string& url_string) {
  if (base::StartsWith(url_string, kChromeSchema16,
                       base::CompareCase::INSENSITIVE_ASCII)) {
    base::ReplaceFirstSubstringAfterOffset(&url_string, 0, kChromeSchema16,
                                           kQoraiSchema16);
    return true;
  }

  return false;
}

}  // namespace qorai_utils

@implementation QoraiURLFormatter
+ (NSString*)formatURLOriginForSecurityDisplay:(NSString*)origin
                                 schemeDisplay:
                                     (QoraiURLSchemeDisplay)schemeDisplay {
  std::u16string result = url_formatter::FormatUrlForSecurityDisplay(
      GURL(base::SysNSStringToUTF8(origin)),
      static_cast<url_formatter::SchemeDisplay>(schemeDisplay));
  qorai_utils::ReplaceChromeToQoraiScheme(result);
  return base::SysUTF16ToNSString(result) ?: @"";
}

+ (NSString*)formatURLOriginForDisplayOmitSchemePathAndTrivialSubdomains:
    (NSString*)origin {
  std::u16string result =
      url_formatter::FormatUrlForDisplayOmitSchemePathAndTrivialSubdomains(
          GURL(base::SysNSStringToUTF8(origin)));
  qorai_utils::ReplaceChromeToQoraiScheme(result);
  return base::SysUTF16ToNSString(result) ?: @"";
}

+ (NSString*)formatURL:(NSString*)url
           formatTypes:(QoraiURLFormatterFormatType)formatTypes
       unescapeOptions:(QoraiURLFormatterUnescapeRule)unescapeOptions {
  std::u16string result = url_formatter::FormatUrl(
      GURL(base::SysNSStringToUTF8(url)),
      static_cast<url_formatter::FormatUrlType>(formatTypes),
      static_cast<base::UnescapeRule::Type>(unescapeOptions), nullptr, nullptr,
      nullptr);
  qorai_utils::ReplaceChromeToQoraiScheme(result);
  return base::SysUTF16ToNSString(result) ?: @"";
}
@end
