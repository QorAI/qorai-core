/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_COLOR_QORAI_COLOR_MIXER_H_
#define QORAI_BROWSER_UI_COLOR_QORAI_COLOR_MIXER_H_

#include "third_party/skia/include/core/SkColor.h"
#include "ui/color/color_provider_key.h"

namespace ui {
class ColorProvider;
}  // namespace ui

// Handling normal profile's dark or light theme.
void AddQoraiThemeColorMixer(ui::ColorProvider* provider,
                             const ui::ColorProviderKey& key);
void AddBravifiedChromeThemeColorMixer(ui::ColorProvider* provider,
                                       const ui::ColorProviderKey& key);
void AddPrivateThemeColorMixer(ui::ColorProvider* provider,
                               const ui::ColorProviderKey& key);
void AddTorThemeColorMixer(ui::ColorProvider* provider,
                           const ui::ColorProviderKey& key);
void AddQoraiOmniboxColorMixer(ui::ColorProvider* provider,
                               const ui::ColorProviderKey& key);
void AddQoraiOmniboxPrivateThemeColorMixer(ui::ColorProvider* provider,
                                           const ui::ColorProviderKey& key);
void AddBravifiedTabStripColorMixer(ui::ColorProvider* provider,
                                    const ui::ColorProviderKey& key);
#endif  // QORAI_BROWSER_UI_COLOR_QORAI_COLOR_MIXER_H_
