// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_WEB_VIEW_PUBLIC_CWV_DOWNLOAD_TASK_EXTRAS_H_
#define QORAI_IOS_WEB_VIEW_PUBLIC_CWV_DOWNLOAD_TASK_EXTRAS_H_

#import <Foundation/Foundation.h>

#import "cwv_download_task.h"

NS_ASSUME_NONNULL_BEGIN

@interface CWVDownloadTask (Extras)
@property(readonly) NSString* originatingHost;
@property(readonly, nullable) NSURL* redirectedURL;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_WEB_VIEW_PUBLIC_CWV_DOWNLOAD_TASK_EXTRAS_H_
