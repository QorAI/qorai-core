/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_GROUP_HEADER_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_GROUP_HEADER_H_

#include <optional>

#include "chrome/browser/ui/views/tabs/tab_group_header.h"

namespace tab_groups {
class TabGroupId;
}  // namespace tab_groups

class QoraiTabGroupHeader : public TabGroupHeader {
  METADATA_HEADER(QoraiTabGroupHeader, TabGroupHeader)
 public:

  constexpr static int kPaddingForGroup = 4;

  using TabGroupHeader::TabGroupHeader;
  ~QoraiTabGroupHeader() override;

  // TabGroupHeader:
  void AddedToWidget() override;
  void VisualsChanged() override;
  int GetDesiredWidth() const override;
  void Layout(PassKey) override;

 private:
  bool ShouldShowVerticalTabs() const;
  void LayoutTitleChipForVerticalTabs();
  SkColor GetGroupColor() const;
  std::optional<SkColor> GetChipBackgroundColor() const;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_GROUP_HEADER_H_
