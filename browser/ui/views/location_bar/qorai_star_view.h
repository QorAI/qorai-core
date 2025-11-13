/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_LOCATION_BAR_QORAI_STAR_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_LOCATION_BAR_QORAI_STAR_VIEW_H_

#include "chrome/browser/ui/views/location_bar/star_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiStarView : public StarView {
  METADATA_HEADER(QoraiStarView, StarView)
 public:
  using StarView::StarView;

  QoraiStarView(const QoraiStarView&) = delete;
  QoraiStarView& operator=(const QoraiStarView&) = delete;

  void OnBubbleWidgetChanged(views::Widget* widget);

 protected:
  // views::View:
  void UpdateImpl() override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_LOCATION_BAR_QORAI_STAR_VIEW_H_
