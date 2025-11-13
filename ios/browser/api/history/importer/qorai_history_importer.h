/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_HISTORY_IMPORTER_QORAI_HISTORY_IMPORTER_H_
#define QORAI_IOS_BROWSER_API_HISTORY_IMPORTER_QORAI_HISTORY_IMPORTER_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, QoraiHistoryImporterState) {
  QoraiHistoryImporterStateCompleted,
  QoraiHistoryImporterStateAutoCompleted,
  QoraiHistoryImporterStateStarted,
  QoraiHistoryImporterStateCancelled
};

OBJC_EXPORT
@interface QoraiImportedHistory : NSObject
@property(nonatomic, readonly) NSURL* url;
@property(nonatomic, readonly) NSString* title;
@property(nonatomic, readonly) NSInteger visitCount;
@property(nonatomic, readonly) NSDate* lastVisitDate;
@end

OBJC_EXPORT
@interface QoraiHistoryImporter : NSObject
- (instancetype)init;

- (void)cancel;

- (void)importFromFile:(NSString*)filePath
       automaticImport:(bool)automaticImport
          withListener:
              (void (^)(QoraiHistoryImporterState,
                        NSArray<QoraiImportedHistory*>* _Nullable))listener;

- (void)importFromArray:(NSArray<QoraiImportedHistory*>*)historyItems
           withListener:(void (^)(QoraiHistoryImporterState))listener;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_HISTORY_IMPORTER_QORAI_HISTORY_IMPORTER_H_
