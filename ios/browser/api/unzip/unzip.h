// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Foundation/Foundation.h>

#ifndef QORAI_IOS_BROWSER_API_UNZIP_UNZIP_H_
#define QORAI_IOS_BROWSER_API_UNZIP_UNZIP_H_

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
NS_SWIFT_NAME(Unzip)
@interface QoraiUnzip : NSObject

/// Unzips a zip file located on disc asynchronously to a given folder using
/// the standard in-process unzipper
+ (void)unzip:(NSString*)zipFile
    toDirectory:(NSString*)directory
     completion:(void (^)(bool))completion;

/// Unzips data asynchronously using Chromium's rust unzipper returning an array
/// containing the data for each unzipped file in the archive or an error if
/// the zip couldn't be expanded
+ (void)unzipData:(NSData*)data
       completion:(void (^)(NSArray<NSData*>* _Nullable unzippedFiles,
                            NSError* _Nullable error))completion
    NS_SWIFT_NAME(unzip(data:completion:));
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_UNZIP_UNZIP_H_
