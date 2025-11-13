/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_BUBBLE_CONTROLLER_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_BUBBLE_CONTROLLER_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
}

class QoraiNewsBubbleView;
class QoraiNewsActionIconView;

namespace qorai_news {

class QoraiNewsBubbleController
    : public content::WebContentsUserData<QoraiNewsBubbleController> {
 public:
  static QoraiNewsBubbleController* CreateOrGetFromWebContents(
      content::WebContents* web_contents);

  ~QoraiNewsBubbleController() override;

  void ShowBubble(base::WeakPtr<QoraiNewsActionIconView> anchor_view);
  QoraiNewsBubbleView* GetBubble();
  void OnBubbleClosed();
  base::WeakPtr<QoraiNewsBubbleController> AsWeakPtr();

 private:
  friend class content::WebContentsUserData<QoraiNewsBubbleController>;
  WEB_CONTENTS_USER_DATA_KEY_DECL();

  explicit QoraiNewsBubbleController(content::WebContents* web_contents);

  raw_ptr<QoraiNewsBubbleView> bubble_ = nullptr;
  raw_ptr<content::WebContents> web_contents_ = nullptr;

  base::WeakPtrFactory<QoraiNewsBubbleController> weak_ptr_factory_{this};
};

}  // namespace qorai_news

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_BUBBLE_CONTROLLER_H_
