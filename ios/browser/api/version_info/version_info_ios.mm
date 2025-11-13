/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/api/version_info/version_info_ios.h"

#include "base/strings/sys_string_conversions.h"
#include "qorai/components/version_info/version_info.h"
#include "components/version_info/version_info.h"
#include "components/version_info/version_string.h"
#include "ios/chrome/common/channel_info.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelStable =
    static_cast<NSInteger>(version_info::Channel::STABLE);
QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelBeta =
    static_cast<NSInteger>(version_info::Channel::BETA);
QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelDevelopment =
    static_cast<NSInteger>(version_info::Channel::DEV);
QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelNightly =
    static_cast<NSInteger>(version_info::Channel::CANARY);
QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelUnknown =
    static_cast<NSInteger>(version_info::Channel::UNKNOWN);

@implementation QoraiCoreVersionInfo

+ (NSString*)qoraiCoreVersion {
  return base::SysUTF8ToNSString(
      version_info::GetQoraiVersionWithoutChromiumMajorVersion());
}

+ (NSString*)chromiumVersion {
  return base::SysUTF8ToNSString(version_info::GetQoraiChromiumVersionNumber());
}

+ (NSString*)channelString {
  return base::SysUTF8ToNSString(GetChannelString());
}

+ (QoraiCoreVersionInfoChannel)channel {
  switch (GetChannel()) {
    case version_info::Channel::STABLE:
      return QoraiCoreVersionInfoChannelStable;
    case version_info::Channel::BETA:
      return QoraiCoreVersionInfoChannelBeta;
    case version_info::Channel::DEV:
      return QoraiCoreVersionInfoChannelDevelopment;
    case version_info::Channel::CANARY:
      return QoraiCoreVersionInfoChannelNightly;
    case version_info::Channel::UNKNOWN:
      return QoraiCoreVersionInfoChannelUnknown;
  }
}
@end
