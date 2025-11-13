/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_READ_LATER_SIDE_PANEL_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_READ_LATER_SIDE_PANEL_VIEW_H_

#include "base/functional/callback_forward.h"
#include "qorai/browser/ui/views/side_panel/qorai_side_panel_view_base.h"
#include "ui/base/metadata/metadata_header_macros.h"

class Profile;
class TabStripModel;
class SidePanelEntryScope;

// Gives reading list specific header view with web view.
class QoraiReadLaterSidePanelView : public QoraiSidePanelViewBase {
  METADATA_HEADER(QoraiReadLaterSidePanelView, QoraiSidePanelViewBase)

 public:
  QoraiReadLaterSidePanelView(Profile* profile,
                              TabStripModel* tab_strip_model,
                              SidePanelEntryScope& scope,
                              base::RepeatingClosure close_cb);
  ~QoraiReadLaterSidePanelView() override;
  QoraiReadLaterSidePanelView(const QoraiReadLaterSidePanelView&) = delete;
  QoraiReadLaterSidePanelView& operator=(const QoraiReadLaterSidePanelView&) =
      delete;
};

#endif  // QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_READ_LATER_SIDE_PANEL_VIEW_H_
