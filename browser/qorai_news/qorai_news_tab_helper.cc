// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_news/qorai_news_tab_helper.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "base/check_is_test.h"
#include "base/check_op.h"
#include "base/containers/contains.h"
#include "base/containers/flat_set.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/memory/weak_ptr.h"
#include "qorai/browser/qorai_news/qorai_news_controller_factory.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "chrome/browser/feed/rss_links_fetcher.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/page.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "url/gurl.h"

QorAINewsTabHelper::FeedDetails::FeedDetails() = default;
QorAINewsTabHelper::FeedDetails::~FeedDetails() = default;
QorAINewsTabHelper::FeedDetails::FeedDetails(FeedDetails&&) = default;
QorAINewsTabHelper::FeedDetails& QorAINewsTabHelper::FeedDetails::operator=(
    QorAINewsTabHelper::FeedDetails&&) = default;

// static
void QorAINewsTabHelper::MaybeCreateForWebContents(
    content::WebContents* contents) {
  if (contents->GetBrowserContext()->IsOffTheRecord()) {
    return;
  }

  CreateForWebContents(contents);
}

QorAINewsTabHelper::QorAINewsTabHelper(content::WebContents* contents)
    : content::WebContentsUserData<QorAINewsTabHelper>(*contents),
      content::WebContentsObserver(contents),
      controller_(qorai_news::QorAINewsControllerFactory::GetForBrowserContext(
          contents->GetBrowserContext())) {
  CHECK(!contents->GetBrowserContext()->IsOffTheRecord());

  if (controller_) {
    pref_observation_.Observe(&controller_->prefs());
    UpdatePageFeed();
  } else {
    CHECK_IS_TEST();
  }
}

QorAINewsTabHelper::~QorAINewsTabHelper() = default;

const std::vector<GURL> QorAINewsTabHelper::GetAvailableFeedUrls() {
  std::vector<GURL> feeds;
  base::flat_set<GURL> seen_feeds;

  if (default_feed_) {
    seen_feeds.insert(default_feed_->feed_source);
    feeds.push_back(default_feed_->feed_source);
  }

  for (const auto& rss_feed : rss_page_feeds_) {
    if (seen_feeds.contains(rss_feed.feed_url)) {
      continue;
    }

    seen_feeds.insert(rss_feed.feed_url);
    feeds.push_back(rss_feed.feed_url);
  }

  return feeds;
}

bool QorAINewsTabHelper::IsSubscribed(const GURL& feed_url) {
  if (default_feed_ && default_feed_->feed_source == feed_url) {
    return qorai_news::IsSubscribed(default_feed_);
  }

  auto it = std::ranges::find(rss_page_feeds_, feed_url,
                              [](const auto& feed) { return feed.feed_url; });
  if (it == rss_page_feeds_.end()) {
    return false;
  }

  return it->subscribed;
}

bool QorAINewsTabHelper::IsSubscribed() {
  return (default_feed_ && qorai_news::IsSubscribed(default_feed_)) ||
         std::ranges::any_of(rss_page_feeds_,
                             [](const auto& feed) { return feed.subscribed; });
}

std::string QorAINewsTabHelper::GetTitleForFeedUrl(const GURL& feed_url) {
  // If there's a default publisher for this |feed_url| we should use it's
  // title.
  if (default_feed_ && default_feed_->feed_source == feed_url) {
    return default_feed_->publisher_name;
  }

  // Otherwise, find the |FeedDetails| for this |feed_url|.
  auto it =
      std::ranges::find(rss_page_feeds_, feed_url, &FeedDetails::feed_url);
  // If we don't have any details, return the empty string as we don't know what
  // the title should be.
  if (it == rss_page_feeds_.end()) {
    return "";
  }

  // Return our cached title, if we have one.
  if (!it->title.empty()) {
    return it->title;
  }

  // If we have an entry, but don't have a title for it, we should request the
  // feed (if we haven't already). Observers will be notified once the feed
  // resolves and we extract a title.
  if (!it->requested_feed) {
    const auto url = web_contents()->GetLastCommittedURL();
    controller_->FindFeeds(
        feed_url,
        base::BindOnce(&QorAINewsTabHelper::OnFoundFeedData,
                       weak_ptr_factory_.GetWeakPtr(), feed_url, url));
    it->requested_feed = true;
  }

  // In the meantime, use the feed_url as the title. Observers will be
  // notified when we receive a title.
  return feed_url.spec();
}

void QorAINewsTabHelper::ToggleSubscription(const GURL& feed_url) {
  bool subscribed = IsSubscribed(feed_url);
  controller_->GetPublisherForFeed(
      feed_url,
      base::BindOnce(
          [](base::WeakPtr<QorAINewsTabHelper> tab_helper, bool subscribed,
             GURL feed_url, qorai_news::mojom::PublisherPtr publisher) {
            if (!tab_helper) {
              return;
            }

            if (publisher) {
              tab_helper->controller_->SetPublisherPref(
                  publisher->publisher_id,
                  subscribed ? qorai_news::mojom::UserEnabled::DISABLED
                             : qorai_news::mojom::UserEnabled::ENABLED);
            } else {
              tab_helper->controller_->SubscribeToNewDirectFeed(
                  feed_url, base::DoNothing());
            }

            tab_helper->OnPublishersChanged();
          },
          weak_ptr_factory_.GetWeakPtr(), subscribed, feed_url));
}

void QorAINewsTabHelper::OnReceivedRssUrls(const GURL& site_url,
                                           std::vector<GURL> feed_urls) {
  if (site_url != GetWebContents().GetLastCommittedURL()) {
    return;
  }

  // For each feed, we need to check if its a combined feed.
  for (const auto& feed_url : feed_urls) {
    controller_->GetPublisherForFeed(
        feed_url,
        base::BindOnce(
            [](base::WeakPtr<QorAINewsTabHelper> tab_helper, GURL feed_url,
               qorai_news::mojom::PublisherPtr publisher) {
              if (!tab_helper) {
                return;
              }

              FeedDetails feed;
              feed.feed_url = feed_url;
              if (publisher) {
                if (publisher->type !=
                    qorai_news::mojom::PublisherType::DIRECT_SOURCE) {
                  feed.combined_publisher_id = publisher->publisher_id;
                }
                feed.title = publisher->publisher_name;
                feed.requested_feed = true;
              }
              tab_helper->rss_page_feeds_.push_back(std::move(feed));
              tab_helper->OnPublishersChanged();
            },
            weak_ptr_factory_.GetWeakPtr(), feed_url));
  }
}

void QorAINewsTabHelper::OnFoundFeedData(
    const GURL& feed_url,
    const GURL& site_url,
    std::vector<qorai_news::mojom::FeedSearchResultItemPtr> feeds) {
  if (site_url != GetWebContents().GetLastCommittedURL()) {
    return;
  }

  if (feeds.empty()) {
    auto to_remove =
        std::ranges::remove(rss_page_feeds_, feed_url, &FeedDetails::feed_url);
    rss_page_feeds_.erase(to_remove.begin(), to_remove.end());
  } else {
    DCHECK_EQ(1u, feeds.size())
        << "As we were passed a FeedURL, this should only find one feed.";

    // Find the FeedDetails this title is for.
    auto result = std::ranges::find_if(
        rss_page_feeds_,
        [feed_url](const auto& detail) { return detail.feed_url == feed_url; });

    // If there was a match, set the title.
    if (result != rss_page_feeds_.end()) {
      result->title = feeds.at(0)->feed_title;
    }
  }

  AvailableFeedsChanged();
}

void QorAINewsTabHelper::AddObserver(PageFeedsObserver* observer) {
  observers_.AddObserver(observer);
}

void QorAINewsTabHelper::RemoveObserver(PageFeedsObserver* observer) {
  observers_.RemoveObserver(observer);
}

bool QorAINewsTabHelper::ShouldFindFeeds() {
  auto* prefs = Profile::FromBrowserContext(web_contents()->GetBrowserContext())
                    ->GetPrefs();
  return qorai_news::IsEnabled(prefs) &&
         prefs->GetBoolean(qorai_news::prefs::kShouldShowToolbarButton);
}

void QorAINewsTabHelper::OnReceivedNewPublishers(
    qorai_news::Publishers publishers) {
  UpdatePageFeed();
  AvailableFeedsChanged();
}

void QorAINewsTabHelper::AvailableFeedsChanged() {
  const auto& feed_urls = GetAvailableFeedUrls();
  for (auto& observer : observers_) {
    observer.OnAvailableFeedsChanged(feed_urls);
  }
}

void QorAINewsTabHelper::PrimaryPageChanged(content::Page& page) {
  // Invalidate all weak pointers - we're on a new page now.
  weak_ptr_factory_.InvalidateWeakPtrs();
  rss_page_feeds_.clear();
  default_feed_ = nullptr;

  UpdatePageFeed();
  AvailableFeedsChanged();
}

void QorAINewsTabHelper::UpdatePageFeed() {
  if (!controller_) {
    CHECK_IS_TEST();
    return;
  }
  controller_->GetPublisherForSite(
      GetWebContents().GetLastCommittedURL(),
      base::BindOnce(
          [](base::WeakPtr<QorAINewsTabHelper> tab_helper,
             qorai_news::mojom::PublisherPtr publisher) {
            if (!tab_helper) {
              return;
            }

            if (!publisher) {
              tab_helper->default_feed_ = nullptr;
              tab_helper->AvailableFeedsChanged();
              return;
            }

            tab_helper->default_feed_ = std::move(publisher);
            tab_helper->AvailableFeedsChanged();
          },
          weak_ptr_factory_.GetWeakPtr()));
}

void QorAINewsTabHelper::DOMContentLoaded(content::RenderFrameHost* rfh) {
  if (GetWebContents().GetPrimaryMainFrame() != rfh) {
    return;
  }

  if (!ShouldFindFeeds()) {
    return;
  }

  feed::FetchRssLinks(GetWebContents().GetLastCommittedURL(), &GetWebContents(),
                      base::BindOnce(&QorAINewsTabHelper::OnReceivedRssUrls,
                                     weak_ptr_factory_.GetWeakPtr(),
                                     GetWebContents().GetLastCommittedURL()));
}

void QorAINewsTabHelper::OnPublishersChanged() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  auto subscriptions = controller_->prefs().GetSubscriptions();
  for (auto& feed : rss_page_feeds_) {
    feed.subscribed =
        subscriptions.enabled_publishers().contains(
            feed.combined_publisher_id) ||
        base::Contains(subscriptions.direct_feeds(), feed.feed_url,
                       [](const auto& direct_feed) { return direct_feed.url; });
  }
  controller_->GetPublishers(
      base::BindOnce(&QorAINewsTabHelper::OnReceivedNewPublishers,
                     weak_ptr_factory_.GetWeakPtr()));
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(QorAINewsTabHelper);
