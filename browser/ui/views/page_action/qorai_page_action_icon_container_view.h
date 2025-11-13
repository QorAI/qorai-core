/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PAGE_ACTION_QORAI_PAGE_ACTION_ICON_CONTAINER_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_PAGE_ACTION_QORAI_PAGE_ACTION_ICON_CONTAINER_VIEW_H_

#include "chrome/browser/ui/views/page_action/page_action_icon_container.h"

class QoraiPageActionIconContainerView : public PageActionIconContainerView {
  METADATA_HEADER(QoraiPageActionIconContainerView, PageActionIconContainerView)
 public:

  // Unfortunately, |PageActionIconParams| can't not be copied or moved. So drop
  // const qualifier to modify |param| for Qorai.
  explicit QoraiPageActionIconContainerView(PageActionIconParams& param);
  ~QoraiPageActionIconContainerView() override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_PAGE_ACTION_QORAI_PAGE_ACTION_ICON_CONTAINER_VIEW_H_
