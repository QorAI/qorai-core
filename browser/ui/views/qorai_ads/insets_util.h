/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_INSETS_UTIL_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_INSETS_UTIL_H_

namespace gfx {
class FontList;
class Insets;
}  // namespace gfx

namespace qorai_ads {

void AdjustInsetsForFontList(gfx::Insets* insets,
                             const gfx::FontList& font_list);

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_INSETS_UTIL_H_
