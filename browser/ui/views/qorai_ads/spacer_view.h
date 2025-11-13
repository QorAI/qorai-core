/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_SPACER_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_SPACER_VIEW_H_

namespace views {
class View;
}  // namespace views

namespace qorai_ads {

views::View* CreateFlexibleSpacerView(int spacing);
views::View* CreateFixedSizeSpacerView(int spacing);

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_SPACER_VIEW_H_
