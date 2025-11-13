// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_BUBBLE_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_BUBBLE_VIEW_H_

#include "base/memory/raw_ptr.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/gfx/geometry/size.h"
#include "ui/views/bubble/bubble_dialog_delegate_view.h"
#include "ui/views/controls/label.h"
#include "ui/views/view.h"
#include "ui/views/widget/widget.h"

class QoraiNewsFeedsContainerView;
namespace qorai_news {
class QoraiNewsBubbleController;
}

class QoraiNewsBubbleView : public views::BubbleDialogDelegateView {
  METADATA_HEADER(QoraiNewsBubbleView, views::BubbleDialogDelegateView)
 public:
  static base::WeakPtr<views::Widget> Show(views::View* anchor,
                                           content::WebContents* contents);

  explicit QoraiNewsBubbleView(views::View* action_view,
                               content::WebContents* contents);
  QoraiNewsBubbleView(const QoraiNewsBubbleView&) = delete;
  QoraiNewsBubbleView& operator=(const QoraiNewsBubbleView&) = delete;
  ~QoraiNewsBubbleView() override;

  void OpenManageFeeds();

  // views::BubbleDialogDelegateView:
  void OnWidgetDestroyed(views::Widget*) override;
  void OnThemeChanged() override;

 private:
  raw_ptr<content::WebContents> contents_ = nullptr;
  raw_ptr<views::Label> title_label_ = nullptr;
  raw_ptr<views::Label> subtitle_label_ = nullptr;
  raw_ptr<QoraiNewsFeedsContainerView> feeds_container_ = nullptr;

  base::WeakPtr<qorai_news::QoraiNewsBubbleController> controller_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_BUBBLE_VIEW_H_
