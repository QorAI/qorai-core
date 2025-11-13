/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_BOOKMARKS_EXPORTER_QORAI_BOOKMARKS_EXPORTER_H_
#define QORAI_IOS_BROWSER_API_BOOKMARKS_EXPORTER_QORAI_BOOKMARKS_EXPORTER_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, QoraiBookmarksExporterState) {
  QoraiBookmarksExporterStateCompleted,
  QoraiBookmarksExporterStateStarted,
  QoraiBookmarksExporterStateCancelled,
  QoraiBookmarksExporterStateErrorCreatingFile,
  QoraiBookmarksExporterStateErrorWritingHeader,
  QoraiBookmarksExporterStateErrorWritingNodes
};

@class IOSBookmarkNode;

OBJC_EXPORT
@interface QoraiBookmarksExporter : NSObject
- (instancetype)init;

- (void)exportToFile:(NSString*)filePath
        withListener:(void (^)(QoraiBookmarksExporterState))listener;

- (void)exportToFile:(NSString*)filePath
           bookmarks:(NSArray<IOSBookmarkNode*>*)bookmarks
        withListener:(void (^)(QoraiBookmarksExporterState))listener;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_BOOKMARKS_EXPORTER_QORAI_BOOKMARKS_EXPORTER_H_
