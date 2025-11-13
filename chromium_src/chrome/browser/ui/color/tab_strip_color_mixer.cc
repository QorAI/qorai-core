/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/color/tab_strip_color_mixer.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/color/qorai_color_mixer.h"
#include "qorai/browser/ui/tabs/qorai_tab_color_mixer.h"
#endif

#define AddTabStripColorMixer AddTabStripColorMixer_ChromiumImpl
#include <chrome/browser/ui/color/tab_strip_color_mixer.cc>
#undef AddTabStripColorMixer

namespace {

void AddQoraiTabStripColorMixer(ui::ColorProvider* provider,
                                const ui::ColorProviderKey& key) {
#if !BUILDFLAG(IS_ANDROID)
  AddBravifiedTabStripColorMixer(provider, key);
#endif  // #if !BUILDFLAG(IS_ANDROID)
}

}  // namespace

void AddTabStripColorMixer(ui::ColorProvider* provider,
                           const ui::ColorProviderKey& key) {
  AddTabStripColorMixer_ChromiumImpl(provider, key);
  AddQoraiTabStripColorMixer(provider, key);

#if !BUILDFLAG(IS_ANDROID)
  // Set vertical tab mixer after adding tab strip mixer because
  // vertical tab mixer uses tab strip mixer's color.
  tabs::AddQoraiTabThemeColorMixer(provider, key);
#endif
}
