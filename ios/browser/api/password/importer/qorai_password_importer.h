// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_PASSWORD_IMPORTER_QORAI_PASSWORD_IMPORTER_H_
#define QORAI_IOS_BROWSER_API_PASSWORD_IMPORTER_QORAI_PASSWORD_IMPORTER_H_

#include <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSInteger QoraiPasswordImportEntryStatus
    NS_TYPED_ENUM NS_SWIFT_NAME(QoraiPasswordImportEntry.Status);

OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusNone;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusUnknownError;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusMissingPassword;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusMissingURL;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusInvalidURL;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongURL;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongPassword;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongUsername;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusConflictProfile;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusConflictAccount;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongNote;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusLongConcatenatedNote;
OBJC_EXPORT QoraiPasswordImportEntryStatus const
    QoraiPasswordImportEntryStatusValid;

OBJC_EXPORT
@interface QoraiPasswordImportEntry : NSObject
@property(nonatomic, readonly) QoraiPasswordImportEntryStatus status;
@property(nonatomic, readonly) NSInteger id;
@property(nonatomic, readonly) NSString* username;
@property(nonatomic, readonly) NSString* password;
@end

typedef NSInteger QoraiPasswordImporterResultsStatus
    NS_TYPED_ENUM NS_SWIFT_NAME(QoraiPasswordImporterResults.Status);

OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusNone;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusUnknownError;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusSuccess;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusIOError;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusBadFormat;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusDismissed;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusMaxFileSize;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusImportAlreadyActive;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusNumPasswordsExceeded;
OBJC_EXPORT QoraiPasswordImporterResultsStatus const
    QoraiPasswordImporterResultsStatusConflicts;

OBJC_EXPORT
NS_SWIFT_NAME(QoraiPasswordImporter.Results)
@interface QoraiPasswordImporterResults : NSObject
@property(nonatomic, readonly) QoraiPasswordImporterResultsStatus status;
@property(nonatomic, readonly) NSString* fileName;
@property(nonatomic, readonly) NSUInteger numberImported;
@property(nonatomic, readonly)
    NSArray<QoraiPasswordImportEntry*>* displayedEntries;
@end

OBJC_EXPORT
@interface QoraiPasswordImporter : NSObject
- (void)importPasswords:(NSString*)fileName
             completion:(void (^)(QoraiPasswordImporterResults*))completion;

- (void)continueImport:(NSArray<QoraiPasswordImportEntry*>*)entriesToReplace
            completion:(void (^)(QoraiPasswordImporterResults*))completion;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_PASSWORD_IMPORTER_QORAI_PASSWORD_IMPORTER_H_
