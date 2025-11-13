// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_NEWS_QORAI_NEWS_TAB_HELPER_H_
#define QORAI_BROWSER_QORAI_NEWS_QORAI_NEWS_TAB_HELPER_H_

#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "base/scoped_observation.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "qorai/components/qorai_news/browser/qorai_news_pref_manager.h"
#include "qorai/components/qorai_news/browser/publishers_controller.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom-forward.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class RenderFrameHost;
}

class QorAINewsTabHelper
    : public content::WebContentsUserData<QorAINewsTabHelper>,
      public content::WebContentsObserver,
      public qorai_news::QorAINewsPrefManager::PrefObserver {
 public:
  struct FeedDetails {
    GURL feed_url;
    std::string title = "";
    bool subscribed = false;

    // The combined publisher id, if any. Empty string if not a combined
    // publisher.
    std::string combined_publisher_id = "";

    // Indicates whether we've requested this feed, so we don't request it
    // multiple times.
    bool requested_feed = false;

    FeedDetails();
    FeedDetails(const FeedDetails&) = delete;
    FeedDetails& operator=(const FeedDetails&) = delete;
    FeedDetails(FeedDetails&&);
    FeedDetails& operator=(FeedDetails&&);
    ~FeedDetails();
  };

  class PageFeedsObserver : public base::CheckedObserver {
   public:
    virtual void OnAvailableFeedsChanged(
        const std::vector<GURL>& feed_urls) = 0;
  };

  static void MaybeCreateForWebContents(content::WebContents* contents);

  QorAINewsTabHelper(const QorAINewsTabHelper&) = delete;
  QorAINewsTabHelper& operator=(const QorAINewsTabHelper&) = delete;

  ~QorAINewsTabHelper() override;

  const std::vector<GURL> GetAvailableFeedUrls();
  bool IsSubscribed(const GURL& feed_url);
  bool IsSubscribed();

  void ToggleSubscription(const GURL& feed_details);
  std::string GetTitleForFeedUrl(const GURL& url);

  void OnReceivedRssUrls(const GURL& site_url, std::vector<GURL> feed_urls);
  void OnFoundFeedData(const GURL& feed_url,
                       const GURL& site_url,
                       std::vector<qorai_news::mojom::FeedSearchResultItemPtr>);

  void AddObserver(PageFeedsObserver* observer);
  void RemoveObserver(PageFeedsObserver* observer);

  // content::WebContentsObserver:
  void PrimaryPageChanged(content::Page& page) override;
  void DOMContentLoaded(content::RenderFrameHost* rfh) override;

  // qorai_news::QorAINewsPrefManager::PrefObserver:
  void OnPublishersChanged() override;

 private:
  explicit QorAINewsTabHelper(content::WebContents* contents);

  bool ShouldFindFeeds();
  void OnReceivedNewPublishers(qorai_news::Publishers publishers);
  void AvailableFeedsChanged();
  void UpdatePageFeed();

  raw_ptr<qorai_news::QorAINewsController> controller_;

  std::vector<FeedDetails> rss_page_feeds_;

  // The (optional) publisher associated with this page from our
  // PublishersController. This may be duplicated by one of the
  // |rss_page_feeds_| so we should ensure we deduplicate based on |feed_url|.
  qorai_news::mojom::PublisherPtr default_feed_ = nullptr;

  base::ObserverList<PageFeedsObserver> observers_;

  base::ScopedObservation<qorai_news::QorAINewsPrefManager,
                          qorai_news::QorAINewsPrefManager::PrefObserver>
      pref_observation_{this};

  base::WeakPtrFactory<QorAINewsTabHelper> weak_ptr_factory_{this};

  friend WebContentsUserData;
  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

#endif  // QORAI_BROWSER_QORAI_NEWS_QORAI_NEWS_TAB_HELPER_H_
