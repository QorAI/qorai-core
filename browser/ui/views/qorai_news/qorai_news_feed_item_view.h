// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_FEED_ITEM_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_FEED_ITEM_VIEW_H_

#include <vector>

#include "qorai/browser/qorai_news/qorai_news_tab_helper.h"
#include "ui/views/controls/label.h"
#include "ui/views/view.h"

namespace content {
class WebContents;
}

namespace views {
class MdTextButton;
}

class QoraiNewsFeedItemView : public views::View,
                              public QoraiNewsTabHelper::PageFeedsObserver {
  METADATA_HEADER(QoraiNewsFeedItemView, views::View)
 public:

  QoraiNewsFeedItemView(const GURL& feed_url, content::WebContents* contents);
  QoraiNewsFeedItemView(const QoraiNewsFeedItemView&) = delete;
  QoraiNewsFeedItemView& operator=(const QoraiNewsFeedItemView&) = delete;
  ~QoraiNewsFeedItemView() override;

  void Update();
  void OnPressed();

  // QoraiNewsTabHelper::PageFeedsObserver:
  void OnAvailableFeedsChanged(const std::vector<GURL>& feed_urls) override;

 private:
  bool loading_ = false;
  raw_ptr<views::Label> title_ = nullptr;
  raw_ptr<views::MdTextButton> subscribe_button_ = nullptr;

  GURL feed_url_;
  raw_ptr<content::WebContents> contents_;
  raw_ptr<QoraiNewsTabHelper> tab_helper_;

  base::ScopedObservation<QoraiNewsTabHelper,
                          QoraiNewsTabHelper::PageFeedsObserver>
      tab_helper_observation_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_FEED_ITEM_VIEW_H_
