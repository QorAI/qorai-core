/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_SYNC_DRIVER_QORAI_SYNC_PROFILE_SERVICE_H_
#define QORAI_IOS_BROWSER_API_SYNC_DRIVER_QORAI_SYNC_PROFILE_SERVICE_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, QoraiSyncUserSelectableTypes) {
  QoraiSyncUserSelectableTypes_NONE = 1ULL << 0,
  QoraiSyncUserSelectableTypes_BOOKMARKS = 1ULL << 1,
  QoraiSyncUserSelectableTypes_PREFERENCES = 1ULL << 2,
  QoraiSyncUserSelectableTypes_PASSWORDS = 1ULL << 3,
  QoraiSyncUserSelectableTypes_AUTOFILL = 1ULL << 4,
  QoraiSyncUserSelectableTypes_THEMES = 1ULL << 5,
  QoraiSyncUserSelectableTypes_HISTORY = 1ULL << 6,
  QoraiSyncUserSelectableTypes_EXTENSIONS = 1ULL << 7,
  QoraiSyncUserSelectableTypes_APPS = 1ULL << 8,
  QoraiSyncUserSelectableTypes_READING_LIST = 1ULL << 9,
  QoraiSyncUserSelectableTypes_TABS = 1ULL << 10,
  QoraiSyncUserSelectableTypes_SAVED_TAB_GROUPS = 1ULL << 11,
  QoraiSyncUserSelectableTypes_PAYMENTS = 1ULL << 12,
  QoraiSyncUserSelectableTypes_PRODUCT_COMPARISON = 1ULL << 14,
  QoraiSyncUserSelectableTypes_COOKIES = 1ULL << 15
};

OBJC_EXPORT
@interface QoraiSyncProfileServiceIOS : NSObject

- (instancetype)init NS_UNAVAILABLE;

// Whether all conditions are satisfied for Sync to start
// Does not imply that Sync is actually running
@property(nonatomic, readonly) bool isSyncFeatureActive;

/// Selectable Types for the Sync User
/// Used for opting in/out on iOS side
@property(nonatomic, assign) QoraiSyncUserSelectableTypes userSelectedTypes;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_SYNC_DRIVER_QORAI_SYNC_PROFILE_SERVICE_H_
