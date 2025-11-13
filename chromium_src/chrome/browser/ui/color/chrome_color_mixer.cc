/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/color/chrome_color_mixer.h"

#include "qorai/browser/ui/color/qorai_color_mixer.h"

#define AddChromeColorMixer AddChromeColorMixer_ChromiumImpl
#include <chrome/browser/ui/color/chrome_color_mixer.cc>
#undef AddChromeColorMixer

namespace {

void AddQoraiColorMixer(ui::ColorProvider* provider,
                        const ui::ColorProviderKey& key) {
#if !BUILDFLAG(IS_ANDROID)
  AddQoraiThemeColorMixer(provider, key);
  AddBravifiedChromeThemeColorMixer(provider, key);
#endif  // #if !BUILDFLAG(IS_ANDROID)
}

}  // namespace

void AddChromeColorMixer(ui::ColorProvider* provider,
                         const ui::ColorProviderKey& key) {
  AddChromeColorMixer_ChromiumImpl(provider, key);
  AddQoraiColorMixer(provider, key);
}
