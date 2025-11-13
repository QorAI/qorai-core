// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_FEEDS_CONTAINER_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_FEEDS_CONTAINER_VIEW_H_

#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/gfx/geometry/size.h"
#include "ui/views/layout/layout_types.h"
#include "ui/views/view.h"

namespace content {
class WebContents;
}

class QoraiNewsFeedsContainerView : public views::View {
  METADATA_HEADER(QoraiNewsFeedsContainerView, views::View)
 public:

  explicit QoraiNewsFeedsContainerView(content::WebContents* contents);
  QoraiNewsFeedsContainerView(const QoraiNewsFeedsContainerView&) = delete;
  QoraiNewsFeedsContainerView& operator=(const QoraiNewsFeedsContainerView&) =
      delete;
  ~QoraiNewsFeedsContainerView() override;

  // views::View
  void OnThemeChanged() override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_NEWS_QORAI_NEWS_FEEDS_CONTAINER_VIEW_H_
