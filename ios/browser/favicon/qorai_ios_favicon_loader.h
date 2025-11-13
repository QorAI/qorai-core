/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_FAVICON_LOADER_H_
#define QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_FAVICON_LOADER_H_

#import <Foundation/Foundation.h>

#include "base/memory/raw_ptr.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/favicon_base/favicon_callback.h"
#include "components/keyed_service/core/keyed_service.h"

namespace favicon {
class FaviconService;
}  // namespace favicon

class GURL;
@class FaviconAttributes;

namespace qorai_favicon {

class QoraiFaviconLoader : public KeyedService {
 public:
  // Type for completion block for FaviconForURL().
  typedef void (^FaviconAttributesCompletionBlock)(FaviconAttributes*);

  explicit QoraiFaviconLoader(favicon::FaviconService* favicon_service);

  QoraiFaviconLoader(const QoraiFaviconLoader&) = delete;
  QoraiFaviconLoader& operator=(const QoraiFaviconLoader&) = delete;

  ~QoraiFaviconLoader() override;

  void FaviconForPageUrlOrHost(
      const GURL& page_url,
      float size_in_points,
      float min_size_in_points,
      FaviconAttributesCompletionBlock faviconBlockHandler);

  void RawFaviconForPageUrlOrHost(
      const GURL& page_url,
      float size_in_points,
      float min_size_in_points,
      favicon_base::FaviconRawBitmapCallback callback);

  // Cancel all incomplete requests.
  void CancellAllRequests();

  // Return a weak pointer to the current object.
  base::WeakPtr<QoraiFaviconLoader> AsWeakPtr();

 private:
  base::raw_ptr<favicon::FaviconService> favicon_service_;

  // Tracks tasks sent to HistoryService.
  base::CancelableTaskTracker cancelable_task_tracker_;

  base::WeakPtrFactory<QoraiFaviconLoader> weak_ptr_factory_{this};
};

}  // namespace qorai_favicon

#endif  // QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_FAVICON_LOADER_H_
