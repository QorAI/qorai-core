/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_INFOBARS_QORAI_INFOBAR_CONTAINER_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_INFOBARS_QORAI_INFOBAR_CONTAINER_VIEW_H_

#include "chrome/browser/ui/views/infobars/infobar_container_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiInfoBarContainerView : public InfoBarContainerView {
  METADATA_HEADER(QoraiInfoBarContainerView, InfoBarContainerView)
 public:
  explicit QoraiInfoBarContainerView(
      infobars::InfoBarContainer::Delegate* delegate);
  QoraiInfoBarContainerView(const QoraiInfoBarContainerView&) = delete;
  QoraiInfoBarContainerView& operator=(const QoraiInfoBarContainerView&) =
      delete;
  ~QoraiInfoBarContainerView() override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_INFOBARS_QORAI_INFOBAR_CONTAINER_VIEW_H_
