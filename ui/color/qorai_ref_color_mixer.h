// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_UI_COLOR_QORAI_REF_COLOR_MIXER_H_
#define QORAI_UI_COLOR_QORAI_REF_COLOR_MIXER_H_

#include "ui/color/color_provider.h"
#include "ui/color/color_provider_key.h"

namespace ui {

// This adds colors which are part of the Material Design Palette that Chromium
// doesn't define (as it doesn't need them) and redefines the baseline color
// palette to be slightly cooler.
void AddQoraiRefColorMixer(ColorProvider* provider,
                           const ColorProviderKey& key);

}  // namespace ui

#endif  // QORAI_UI_COLOR_QORAI_REF_COLOR_MIXER_H_
