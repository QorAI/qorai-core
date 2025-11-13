/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_GROUP_HIGHLIGHT_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_GROUP_HIGHLIGHT_H_

#include "chrome/browser/ui/views/tabs/tab_group_highlight.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiTabGroupHighlight : public TabGroupHighlight {
  METADATA_HEADER(QoraiTabGroupHighlight, TabGroupHighlight)
 public:
  using TabGroupHighlight::TabGroupHighlight;
  ~QoraiTabGroupHighlight() override;

 private:
  // TabGroupHighlight:
  SkPath GetPath() const override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_GROUP_HIGHLIGHT_H_
