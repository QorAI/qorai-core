/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/tabs/qorai_tab_color_mixer.h"

#include "base/containers/fixed_flat_map.h"
#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/functional/callback_forward.h"
#include "base/logging.h"
#include "base/types/cxx23_to_underlying.h"
#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/ui/color/nala/nala_color_id.h"
#include "chrome/browser/themes/theme_properties.h"
#include "chrome/browser/ui/color/chrome_color_id.h"
#include "ui/color/color_id.h"
#include "ui/color/color_mixer.h"
#include "ui/color/color_provider.h"
#include "ui/color/color_provider_key.h"
#include "ui/color/color_recipe.h"
#include "ui/color/color_transform.h"
#include "ui/gfx/color_utils.h"

#if defined(TOOLKIT_VIEWS)
#include "qorai/browser/ui/darker_theme/darker_theme_color_transform_factory.h"
#include "qorai/browser/ui/darker_theme/features.h"
#endif  // defined(TOOLKIT_VIEWS)

namespace tabs {

namespace {

bool HasNonGrayscaleUserColor(const ui::ColorProviderKey& key) {
  // Some platform can have user color with gray scale.
  // Ex, accent color is always set as user_color on Windows.
  return (key.user_color_source !=
          ui::ColorProviderKey::UserColorSource::kGrayscale) &&
         key.user_color.has_value();
}

SkColor GetActiveVerticalTabBackgroundColor(const ui::ColorProviderKey& key,
                                            SkColor input,
                                            const ui::ColorMixer& mixer) {
  const auto default_color =
      mixer.GetResultColor(nala::kColorDesktopbrowserTabbarActiveTabVertical);
  if (!HasNonGrayscaleUserColor(key)) {
    return default_color;
  }

  // Extract Hue of tab foreground color and apply Saturation and Lightness for
  // vertical tabs.
  color_utils::HSL hsl;
  color_utils::SkColorToHSL(*key.user_color, &hsl);

  hsl.s = 0.6;    // A little more saturation as default color is grayish.
  hsl.l = 0.485;  // A little bit darker

  return color_utils::HSLShift(default_color, hsl);
}

SkColor GetHoveredTabBackgroundColor(const ui::ColorProviderKey& key,
                                     nala::Color default_color_id,
                                     SkColor input,
                                     const ui::ColorMixer& mixer) {
  CHECK(default_color_id == nala::kColorDesktopbrowserTabbarHoverTabVertical ||
        default_color_id == nala::kColorDesktopbrowserTabbarHoverTabHorizontal);

  const auto default_color = mixer.GetResultColor(default_color_id);
  if (!HasNonGrayscaleUserColor(key)) {
    // Defaults to Nala if no user color.
    return default_color;
  }

  CHECK_EQ(base::to_underlying(ui::ColorProviderKey::ColorMode::kLight), 0);
  CHECK_EQ(base::to_underlying(ui::ColorProviderKey::ColorMode::kDark), 1);

  constexpr auto kHSLShiftMap =
      base::MakeFixedFlatMap<nala::Color, std::array<color_utils::HSL, 2>>({
          {nala::kColorDesktopbrowserTabbarHoverTabVertical,
           {color_utils::HSL{
                .h = -1, .s = 0.5, .l = 0.8},  // Light mode : lighter
            color_utils::HSL{
                .h = -1, .s = 0.6, .l = 0.5}}},  // Dark mode : More saturation
          {nala::kColorDesktopbrowserTabbarHoverTabHorizontal,
           {color_utils::HSL{
                .h = -1,
                .s = 0.9,
                .l = 0.8},  // Light-mode: More saturation and lighter
            color_utils::HSL{
                .h = -1,
                .s = 0.55,
                .l = 0.52}}},  // Dark-mode: A little more saturation
                               // and a little bit darker
      });

  const color_utils::HSL& shift =
      kHSLShiftMap.at(default_color_id).at(base::to_underlying(key.color_mode));
  return color_utils::HSLShift(default_color, shift);
}

SkColor GetSplitViewTileBackgroundColor(const ui::ColorProviderKey& key,
                                        nala::Color default_color_id,
                                        SkColor input,
                                        const ui::ColorMixer& mixer) {
  const auto default_color = mixer.GetResultColor(default_color_id);
  if (!HasNonGrayscaleUserColor(key)) {
    return default_color;
  }

  CHECK_EQ(base::to_underlying(ui::ColorProviderKey::ColorMode::kLight), 0);
  CHECK_EQ(base::to_underlying(ui::ColorProviderKey::ColorMode::kDark), 1);

  // Derive split view tile backgrounds similarly to hovered tab backgrounds,
  // keeping the original hue while adjusting saturation and lightness
  // depending on the color mode and orientation.
  constexpr auto kHSLShiftMap =
      base::MakeFixedFlatMap<nala::Color, std::array<color_utils::HSL, 2>>({
          {nala::kColorDesktopbrowserTabbarSplitViewBackgroundHorizontal,
           {color_utils::HSL{.h = -1, .s = 0.65, .l = 0.59},   // Light mode
            color_utils::HSL{.h = -1, .s = 0.55, .l = 0.4}}},  // Dark mode
          {nala::kColorDesktopbrowserTabbarSplitViewBackgroundVertical,
           {color_utils::HSL{.h = -1, .s = 0.5, .l = 0.52},    // Light mode
            color_utils::HSL{.h = -1, .s = 0.6, .l = 0.52}}},  // Dark mode
      });

  const color_utils::HSL& shift =
      kHSLShiftMap.at(default_color_id).at(base::to_underlying(key.color_mode));
  return color_utils::HSLShift(default_color, shift);
}

}  // namespace

void AddQoraiTabThemeColorMixer(ui::ColorProvider* provider,
                                const ui::ColorProviderKey& key) {
  auto& mixer = provider->AddMixer();

  if (key.custom_theme) {
    mixer[kColorQoraiSplitViewTileBackgroundHorizontal] = {
        SkColorSetARGB(0x1A, 0x00, 0x00, 0x00)};
    mixer[kColorQoraiSplitViewTileBackgroundVertical] = {
        kColorQoraiSplitViewTileBackgroundHorizontal};
    mixer[kColorQoraiSplitViewTileBackgroundBorder] = {
        SkColorSetARGB(0x34, 0xFF, 0xFF, 0xFF)};
    mixer[kColorQoraiSplitViewTileDivider] = {kColorTabDividerFrameActive};
    mixer[kColorQoraiVerticalTabActiveBackground] = {
        kColorTabBackgroundInactiveFrameActive};
    mixer[kColorQoraiVerticalTabHoveredBackground] = {
        ui::AlphaBlend(kColorQoraiVerticalTabActiveBackground,
                       kColorQoraiVerticalTabInactiveBackground,
                       /* 40% opacity */ 0.4 * SK_AlphaOPAQUE)};
  } else {
    mixer[kColorQoraiSplitViewTileBackgroundHorizontal] = {base::BindRepeating(
        &GetSplitViewTileBackgroundColor, key,
        nala::kColorDesktopbrowserTabbarSplitViewBackgroundHorizontal)};
    mixer[kColorQoraiSplitViewTileBackgroundVertical] = {base::BindRepeating(
        &GetSplitViewTileBackgroundColor, key,
        nala::kColorDesktopbrowserTabbarSplitViewBackgroundVertical)};
    mixer[kColorQoraiSplitViewTileBackgroundBorder] = {SK_ColorTRANSPARENT};
    mixer[kColorQoraiSplitViewTileDivider] = {
        nala::kColorDesktopbrowserTabbarSplitViewDivider};
    mixer[kColorQoraiVerticalTabActiveBackground] = {
        base::BindRepeating(&GetActiveVerticalTabBackgroundColor, key)};
    mixer[kColorTabBackgroundInactiveHoverFrameActive] = {base::BindRepeating(
        &GetHoveredTabBackgroundColor, key,
        nala::kColorDesktopbrowserTabbarHoverTabHorizontal)};
    mixer[kColorQoraiVerticalTabHoveredBackground] = {
        base::BindRepeating(&GetHoveredTabBackgroundColor, key,
                            nala::kColorDesktopbrowserTabbarHoverTabVertical)};
  }

  mixer[kColorQoraiVerticalTabInactiveBackground] = {kColorToolbar};
  mixer[kColorQoraiVerticalTabSeparator] = {
      nala::kColorDesktopbrowserToolbarButtonOutline};
  mixer[kColorQoraiVerticalTabNTBIconColor] = {
      kColorTabForegroundInactiveFrameActive};
  mixer[kColorQoraiVerticalTabNTBTextColor] = {
      kColorTabForegroundInactiveFrameActive};
  mixer[kColorQoraiVerticalTabNTBShortcutTextColor] = {
      kColorTabForegroundActiveFrameActive};
  mixer[kColorQoraiSplitViewMenuItemIcon] = {nala::kColorIconDefault};
  mixer[kColorQoraiSplitViewUrl] = {nala::kColorTextTertiary};
  mixer[kColorQoraiSplitViewMenuButtonBorder] = {nala::kColorDividerSubtle};
  mixer[kColorQoraiSplitViewActiveWebViewBorder] = {
      nala::kColorPrimitiveBrandsRorange1};
  mixer[kColorQoraiSplitViewMenuButtonBackground] = {
      nala::kColorContainerBackground};
  mixer[kColorQoraiSplitViewMenuButtonIcon] = {nala::kColorIconInteractive};

  mixer[kColorQoraiSharedPinnedTabDummyViewThumbnailBorder] = {
      nala::kColorDividerSubtle};
  mixer[kColorQoraiSharedPinnedTabDummyViewDescription] = {
      nala::kColorTextSecondary};
  mixer[kColorQoraiSharedPinnedTabDummyViewTitle] = {nala::kColorTextPrimary};
  mixer[kColorQoraiSharedPinnedTabDummyViewBackground] = {
      nala::kColorContainerBackground};
  mixer[kColorQoraiSplitViewInactiveWebViewBorder] = {
      nala::kColorDesktopbrowserToolbarButtonOutline};

  auto& postprocessing_mixer = provider->AddPostprocessingMixer();
  auto apply_opacity_for_inactive_tab_foreground =
      base::BindRepeating([](SkColor input, const ui::ColorMixer& mixer) {
        return SkColorSetA(input,
                           0xFF * 0.7);  // 70% opacity of the input
      });

  // Note that this opacity adjustment will be overriden when darker theme
  // is applied.
  postprocessing_mixer[kColorTabForegroundInactiveFrameActive] =
      ui::ColorTransform(apply_opacity_for_inactive_tab_foreground);
  postprocessing_mixer[kColorTabForegroundInactiveFrameInactive] =
      ui::ColorTransform(apply_opacity_for_inactive_tab_foreground);

#if defined(TOOLKIT_VIEWS)
  if (!base::FeatureList::IsEnabled(
          darker_theme::features::kQoraiDarkerTheme) ||
      key.custom_theme ||
      key.scheme_variant != ui::ColorProviderKey::SchemeVariant::kDarker) {
    return;
  }

  // Tab background
  // : active/inactive tab X active/inactive frame
  postprocessing_mixer[kColorTabBackgroundActiveFrameActive] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral20);
  postprocessing_mixer[kColorTabBackgroundActiveFrameInactive] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral20);
  postprocessing_mixer[kColorTabBackgroundInactiveFrameActive] = {
      ui::kColorFrameActive};
  postprocessing_mixer[kColorTabBackgroundInactiveFrameInactive] = {
      ui::kColorFrameInactive};

  // Tab foreground - such as title text
  // : active/inactive tab X active/inactive frame
  postprocessing_mixer[kColorTabForegroundActiveFrameActive] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral80);
  postprocessing_mixer[kColorTabForegroundActiveFrameInactive] = {
      kColorTabForegroundActiveFrameActive};
  postprocessing_mixer[kColorTabForegroundInactiveFrameActive] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral40);
  postprocessing_mixer[kColorTabForegroundInactiveFrameInactive] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral40);

  // Tab hovered background
  postprocessing_mixer[kColorTabBackgroundInactiveHoverFrameActive] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral10);

  // Split view tile background - horizontal/vertical
  postprocessing_mixer[kColorQoraiSplitViewTileBackgroundHorizontal] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral5);
  postprocessing_mixer[kColorQoraiSplitViewTileBackgroundVertical] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral0);

  // NewTabButton
  postprocessing_mixer[kColorNewTabButtonForegroundFrameActive] = {
      kColorTabForegroundActiveFrameActive};
  postprocessing_mixer[kColorNewTabButtonForegroundFrameInactive] = {
      kColorTabForegroundActiveFrameInactive};
  postprocessing_mixer[kColorNewTabButtonBackgroundFrameActive] = {
      ui::kColorFrameActive};
  postprocessing_mixer[kColorNewTabButtonBackgroundFrameInactive] = {
      ui::kColorFrameInactive};

  // Vertical tabs
  postprocessing_mixer[kColorQoraiVerticalTabActiveBackground] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral20);
  postprocessing_mixer[kColorQoraiVerticalTabHoveredBackground] =
      darker_theme::ApplyDarknessFromColor(nala::kColorPrimitiveNeutral10);
  postprocessing_mixer[kColorQoraiVerticalTabInactiveBackground] = {
      kColorToolbar};

  const SkColor ntb_forground = postprocessing_mixer.GetResultColor(
      kColorTabForegroundInactiveFrameActive);
  postprocessing_mixer[kColorQoraiVerticalTabNTBIconColor] = {ntb_forground};
  postprocessing_mixer[kColorQoraiVerticalTabNTBTextColor] = {ntb_forground};
  postprocessing_mixer[kColorQoraiVerticalTabNTBShortcutTextColor] = {
      ntb_forground};
#endif  // defined(TOOLKIT_VIEWS)
}

void AddQoraiTabPrivateThemeColorMixer(ui::ColorProvider* provider,
                                       const ui::ColorProviderKey& key) {
  auto& mixer = provider->AddMixer();
  mixer[kColorQoraiVerticalTabActiveBackground] = {
      nala::kColorPrimitivePrivateWindow30};
  mixer[kColorQoraiVerticalTabInactiveBackground] = {
      mixer.GetResultColor(kColorToolbar)};
  mixer[kColorQoraiVerticalTabHoveredBackground] = {
      nala::kColorPrimitivePrivateWindow15};
  mixer[kColorQoraiSplitViewTileBackgroundHorizontal] = {
      nala::kColorPrimitivePrivateWindow10};
  mixer[kColorQoraiSplitViewTileBackgroundVertical] = {
      nala::kColorPrimitivePrivateWindow5};
  mixer[kColorQoraiSplitViewTileDivider] = {
      nala::kColorPrimitivePrivateWindow20};
  mixer[kColorQoraiSplitViewTileBackgroundBorder] = {SK_ColorTRANSPARENT};
}

void AddQoraiTabTorThemeColorMixer(ui::ColorProvider* provider,
                                   const ui::ColorProviderKey& key) {
  auto& mixer = provider->AddMixer();
  mixer[kColorQoraiVerticalTabActiveBackground] = {
      nala::kColorPrimitiveTorWindow30};
  mixer[kColorQoraiVerticalTabInactiveBackground] = {
      mixer.GetResultColor(kColorToolbar)};
  mixer[kColorQoraiVerticalTabHoveredBackground] = {
      nala::kColorPrimitiveTorWindow15};
  mixer[kColorQoraiSplitViewTileBackgroundHorizontal] = {
      nala::kColorPrimitiveTorWindow10};
  mixer[kColorQoraiSplitViewTileBackgroundVertical] = {
      nala::kColorPrimitiveTorWindow5};
  mixer[kColorQoraiSplitViewTileDivider] = {nala::kColorPrimitiveTorWindow20};
  mixer[kColorQoraiSplitViewTileBackgroundBorder] = {SK_ColorTRANSPARENT};
}

}  // namespace tabs
