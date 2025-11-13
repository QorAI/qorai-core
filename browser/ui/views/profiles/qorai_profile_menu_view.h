/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PROFILES_QORAI_PROFILE_MENU_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_PROFILES_QORAI_PROFILE_MENU_VIEW_H_

#include "chrome/browser/ui/views/profiles/profile_menu_view.h"

class QoraiProfileMenuView : public ProfileMenuView {
 public:
  QoraiProfileMenuView(const QoraiProfileMenuView&) = delete;
  QoraiProfileMenuView& operator=(const QoraiProfileMenuView&) = delete;
  ~QoraiProfileMenuView() override = default;

 private:
  friend class ProfileMenuView;
  using ProfileMenuView::ProfileMenuView;

  void BuildFeatureButtons() override;
  void MaybeBuildCloseBrowsersButton() override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_PROFILES_QORAI_PROFILE_MENU_VIEW_H_
