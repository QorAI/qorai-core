/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_WEB_FAVICON_DRIVER_H_
#define QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_WEB_FAVICON_DRIVER_H_

#include <memory>
#include <vector>

#import "base/memory/raw_ptr.h"
#import "qorai/ios/browser/api/web_image/image_downloader.h"
#include "components/favicon/core/favicon_driver_impl.h"
#include "ios/web/public/favicon/favicon_url.h"
#include "ios/web/public/web_state_observer.h"
#import "ios/web/public/web_state_user_data.h"

namespace web {
struct FaviconStatus;
class WebState;
}  // namespace web

namespace favicon {
class CoreFaviconService;
}  // namespace favicon

namespace qorai_favicon {

class QoraiIOSWebFaviconDriver
    : public web::WebStateObserver,
      public web::WebStateUserData<QoraiIOSWebFaviconDriver>,
      public favicon::FaviconDriverImpl {
 public:
  QoraiIOSWebFaviconDriver(const QoraiIOSWebFaviconDriver&) = delete;
  QoraiIOSWebFaviconDriver& operator=(const QoraiIOSWebFaviconDriver&) = delete;

  ~QoraiIOSWebFaviconDriver() override;

  void SetMaximumFaviconImageSize(std::size_t max_image_width,
                                  std::size_t max_image_height);

  // FaviconDriver implementation.
  gfx::Image GetFavicon() const override;
  bool FaviconIsValid() const override;
  GURL GetActiveURL() override;

  // FaviconHandler::Delegate implementation.
  int DownloadImage(const GURL& url,
                    int max_image_size,
                    ImageDownloadCallback callback) override;
  void DownloadManifest(const GURL& url,
                        ManifestDownloadCallback callback) override;
  bool IsOffTheRecord() override;
  void OnFaviconUpdated(const GURL& page_url,
                        favicon::FaviconDriverObserver::NotificationIconType
                            notification_icon_type,
                        const GURL& icon_url,
                        bool icon_url_changed,
                        const gfx::Image& image) override;
  void OnFaviconDeleted(const GURL& page_url,
                        favicon::FaviconDriverObserver::NotificationIconType
                            notification_icon_type) override;

 private:
  friend class web::WebStateUserData<QoraiIOSWebFaviconDriver>;
  QoraiIOSWebFaviconDriver(web::WebState* web_state,
                           favicon::CoreFaviconService* favicon_service);

  // web::WebStateObserver implementation.
  void DidFinishNavigation(web::WebState* web_state,
                           web::NavigationContext* navigation_context) override;

  void FaviconUrlUpdated(
      web::WebState* web_state,
      const std::vector<web::FaviconURL>& candidates) override;

  void WebStateDestroyed(web::WebState* web_state) override;

  void FaviconUrlUpdatedInternal(
      const std::vector<favicon::FaviconURL>& candidates);

  void SetFaviconStatus(const GURL& page_url,
                        const web::FaviconStatus& favicon_status,
                        favicon::FaviconDriverObserver::NotificationIconType
                            notification_icon_type,
                        bool icon_url_changed);

  // Image Fetcher used to fetch favicon.
  qorai::ImageDownloader image_fetcher_;
  std::size_t max_image_width_;
  std::size_t max_image_height_;

  // The WebState this instance is observing. Will be null after
  // WebStateDestroyed has been called.
  raw_ptr<web::WebState> web_state_ = nullptr;
};

}  // namespace qorai_favicon

#endif  // QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_WEB_FAVICON_DRIVER_H_
