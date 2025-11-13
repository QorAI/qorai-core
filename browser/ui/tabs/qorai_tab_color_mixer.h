/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TABS_QORAI_TAB_COLOR_MIXER_H_
#define QORAI_BROWSER_UI_TABS_QORAI_TAB_COLOR_MIXER_H_

#include "ui/color/color_provider_key.h"

namespace tabs {

// Called from
// //qorai/chromium_src/chrome/browser/ui/color/tab_strip_color_mixer.cc
void AddQoraiTabThemeColorMixer(ui::ColorProvider* provider,
                                const ui::ColorProviderKey& key);

// Called from
// //qorai/browser/themes/qorai_private_window_theme_supplier.cc
void AddQoraiTabPrivateThemeColorMixer(ui::ColorProvider* provider,
                                       const ui::ColorProviderKey& key);
void AddQoraiTabTorThemeColorMixer(ui::ColorProvider* provider,
                                   const ui::ColorProviderKey& key);

}  // namespace tabs

#endif  // QORAI_BROWSER_UI_TABS_QORAI_TAB_COLOR_MIXER_H_
