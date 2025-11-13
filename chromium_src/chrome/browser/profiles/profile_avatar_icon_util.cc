// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "chrome/browser/profiles/profile_avatar_icon_util.h"

#include <array>

#include "base/check_op.h"
#include "base/values.h"
#include "qorai/app/vector_icons/vector_icons.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "build/build_config.h"
#include "chrome/grit/theme_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/native_theme/native_theme.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/grit/qorai_theme_resources.h"
#endif

// First, define anything that patches will rely on.
namespace profiles {

struct IconResourceInfo;

const IconResourceInfo* GetQoraiDefaultAvatarIconResourceInfo(
    size_t chromium_index);

size_t GetQoraiAvatarIconStartIndex();

#define QORAI_GET_DEFAULT_AVATAR_ICON_RESOURCE_INFO              \
  size_t qorai_start_index =                                     \
      kDefaultAvatarIconsCount - kQoraiDefaultAvatarIconsCount;  \
  if (index >= qorai_start_index) {                              \
    size_t qorai_icon_index = index - qorai_start_index;         \
    const IconResourceInfo* qorai_icon =                         \
        GetQoraiDefaultAvatarIconResourceInfo(qorai_icon_index); \
    if (qorai_icon)                                              \
      return qorai_icon;                                         \
  }

#define QORAI_GET_MODERN_AVATAR_ICON_START_INDEX \
  return GetQoraiAvatarIconStartIndex();

#define QORAI_GET_ICONS_AND_LABELS_FOR_PROFILE_AVATAR_SELECTOR_NOT_SIGNED_IN \
  avatars.erase(avatars.begin());                                            \
  generic_avatar_info = GetDefaultProfileAvatarIconAndLabel_Qorai(           \
      colors.default_avatar_fill_color, colors.default_avatar_stroke_color,  \
      selected_avatar_idx == GetPlaceholderAvatarIndex());                   \
  avatars.Insert(avatars.begin(), base::Value(std::move(generic_avatar_info)));

// It is necessary to match the declaration for this function to be referred to
// by the translation unit, otherwise it cannot tell that the last argument can
// have a default value.
gfx::Image GetPlaceholderAvatarIconWithColors_ChromiumImpl(
    SkColor fill_color,
    SkColor stroke_color,
    int size,
    const PlaceholderAvatarIconParams& icon_params = {});

}  // namespace profiles

// Override some functions (see implementations for details).
#define IsDefaultAvatarIconUrl IsDefaultAvatarIconUrl_ChromiumImpl
#define GetGuestAvatar GetGuestAvatar_ChromiumImpl
#define GetPlaceholderAvatarIconWithColors \
  GetPlaceholderAvatarIconWithColors_ChromiumImpl
#define GetDefaultProfileAvatarIconAndLabel \
  GetDefaultProfileAvatarIconAndLabel_ChromiumImpl
#define GetPlaceholderAvatarIconVisibleAgainstBackground \
  GetPlaceholderAvatarIconVisibleAgainstBackground_ChromiumImpl

#include <chrome/browser/profiles/profile_avatar_icon_util.cc>
#undef GetPlaceholderAvatarIconVisibleAgainstBackground
#undef GetDefaultProfileAvatarIconAndLabel
#undef GetPlaceholderAvatarIconWithColors
#undef GetGuestAvatar
#undef IsDefaultAvatarIconUrl
#undef QORAI_GET_ICONS_AND_LABELS_FOR_PROFILE_AVATAR_SELECTOR_NOT_SIGNED_IN
#undef QORAI_GET_MODERN_AVATAR_ICON_START_INDEX
#undef QORAI_GET_DEFAULT_AVATAR_ICON_RESOURCE_INFO

namespace profiles {

size_t GetQoraiAvatarIconStartIndex() {
  return kDefaultAvatarIconsCount - kQoraiDefaultAvatarIconsCount;
}

const IconResourceInfo* GetQoraiDefaultAvatarIconResourceInfo(size_t index) {
#if BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_ANDROID)
  return nullptr;
#else
  CHECK_LT(index, kQoraiDefaultAvatarIconsCount);
  // Keep the chromium naming style for compatibility with format compare
  // methods, such as profile::IsDefaultAvatarIconUrl.
  // The ID suffixes should be the only thing that needs to change in this file
  // if the chromium list grows in size.
  // Generated via zsh:
  //   > declare -i a=56
  //   > for file in $(cat < avatarlist); do echo "{IDR_PROFILE_AVATAR_$a,
  //       \"$file\", IDS_QORAI_AVATAR_LABEL_$a},"; a=a+1 done | pbcopy
  static constexpr auto kResourceInfo =
      std::to_array<IconResourceInfo, kQoraiDefaultAvatarIconsCount>(
          {{IDR_PROFILE_AVATAR_56, "avatar_edgy_qorai.png",
            IDS_QORAI_AVATAR_LABEL_56},
           {IDR_PROFILE_AVATAR_57, "avatar_edgy_ocean.png",
            IDS_QORAI_AVATAR_LABEL_57},
           {IDR_PROFILE_AVATAR_58, "avatar_edgy_grass.png",
            IDS_QORAI_AVATAR_LABEL_58},
           {IDR_PROFILE_AVATAR_59, "avatar_edgy_corn.png",
            IDS_QORAI_AVATAR_LABEL_59},
           {IDR_PROFILE_AVATAR_60, "avatar_edgy_royal.png",
            IDS_QORAI_AVATAR_LABEL_60},
           {IDR_PROFILE_AVATAR_61, "avatar_edgy_ninja.png",
            IDS_QORAI_AVATAR_LABEL_61},
           {IDR_PROFILE_AVATAR_62, "avatar_paladin_rewards.png",
            IDS_QORAI_AVATAR_LABEL_62},
           {IDR_PROFILE_AVATAR_63, "avatar_paladin_qorai.png",
            IDS_QORAI_AVATAR_LABEL_63},
           {IDR_PROFILE_AVATAR_64, "avatar_paladin_ocean.png",
            IDS_QORAI_AVATAR_LABEL_64},
           {IDR_PROFILE_AVATAR_65, "avatar_paladin_grass.png",
            IDS_QORAI_AVATAR_LABEL_65},
           {IDR_PROFILE_AVATAR_66, "avatar_paladin_corn.png",
            IDS_QORAI_AVATAR_LABEL_66},
           {IDR_PROFILE_AVATAR_67, "avatar_paladin_royal.png",
            IDS_QORAI_AVATAR_LABEL_67},
           {IDR_PROFILE_AVATAR_68, "avatar_paladin_ninja.png",
            IDS_QORAI_AVATAR_LABEL_68},
           {IDR_PROFILE_AVATAR_69, "avatar_gleam_rewards.png",
            IDS_QORAI_AVATAR_LABEL_69},
           {IDR_PROFILE_AVATAR_70, "avatar_gleam_qorai.png",
            IDS_QORAI_AVATAR_LABEL_70},
           {IDR_PROFILE_AVATAR_71, "avatar_gleam_ocean.png",
            IDS_QORAI_AVATAR_LABEL_71},
           {IDR_PROFILE_AVATAR_72, "avatar_gleam_grass.png",
            IDS_QORAI_AVATAR_LABEL_72},
           {IDR_PROFILE_AVATAR_73, "avatar_gleam_corn.png",
            IDS_QORAI_AVATAR_LABEL_73},
           {IDR_PROFILE_AVATAR_74, "avatar_gleam_royal.png",
            IDS_QORAI_AVATAR_LABEL_74},
           {IDR_PROFILE_AVATAR_75, "avatar_gleam_ninja.png",
            IDS_QORAI_AVATAR_LABEL_75},
           {IDR_PROFILE_AVATAR_76, "avatar_oval_rewards.png",
            IDS_QORAI_AVATAR_LABEL_76},
           {IDR_PROFILE_AVATAR_77, "avatar_oval_qorai.png",
            IDS_QORAI_AVATAR_LABEL_77},
           {IDR_PROFILE_AVATAR_78, "avatar_oval_ocean.png",
            IDS_QORAI_AVATAR_LABEL_78},
           {IDR_PROFILE_AVATAR_79, "avatar_oval_grass.png",
            IDS_QORAI_AVATAR_LABEL_79},
           {IDR_PROFILE_AVATAR_80, "avatar_oval_corn.png",
            IDS_QORAI_AVATAR_LABEL_80},
           {IDR_PROFILE_AVATAR_81, "avatar_oval_royal.png",
            IDS_QORAI_AVATAR_LABEL_81},
           {IDR_PROFILE_AVATAR_82, "avatar_oval_ninja.png",
            IDS_QORAI_AVATAR_LABEL_82},
           {IDR_PROFILE_AVATAR_83, "avatar_bonbon_rewards.png",
            IDS_QORAI_AVATAR_LABEL_83},
           {IDR_PROFILE_AVATAR_84, "avatar_bonbon_qorai.png",
            IDS_QORAI_AVATAR_LABEL_84},
           {IDR_PROFILE_AVATAR_85, "avatar_bonbon_ocean.png",
            IDS_QORAI_AVATAR_LABEL_85},
           {IDR_PROFILE_AVATAR_86, "avatar_bonbon_grass.png",
            IDS_QORAI_AVATAR_LABEL_86},
           {IDR_PROFILE_AVATAR_87, "avatar_bonbon_corn.png",
            IDS_QORAI_AVATAR_LABEL_87},
           {IDR_PROFILE_AVATAR_88, "avatar_bonbon_royal.png",
            IDS_QORAI_AVATAR_LABEL_88},
           {IDR_PROFILE_AVATAR_89, "avatar_bonbon_ninja.png",
            IDS_QORAI_AVATAR_LABEL_89}});
  static_assert((kResourceInfo[kQoraiDefaultAvatarIconsCount - 1].resource_id ==
                 IDR_PROFILE_AVATAR_89),
                "IconResourceInfo entries for Qorai avatars is less than"
                "kQoraiDefaultAvatarIconsCount but should be the same.");
  return &kResourceInfo[index];
#endif
}

bool IsDefaultAvatarIconUrl(std::string_view url, size_t* icon_index) {
  // Qorai supports user choosing the placeholder avatar, Chromium does not.
  if (url.compare(GetPlaceholderAvatarIconUrl()) == 0) {
    *icon_index = GetPlaceholderAvatarIndex();
    return true;
  }
  return IsDefaultAvatarIconUrl_ChromiumImpl(url, icon_index);
}

ui::ImageModel GetGuestAvatar(int size) {
  return ui::ImageModel::FromVectorIcon(kUserMenuGuestIcon, ui::kColorIcon,
                                        size);
}

gfx::Image GetPlaceholderAvatarIconWithColors(
    SkColor fill_color,
    SkColor stroke_color,
    int size,
    const PlaceholderAvatarIconParams& icon_params) {
  return ui::ResourceBundle::GetSharedInstance().GetImageNamed(
      GetPlaceholderAvatarIconResourceID());
}

gfx::Image GetPlaceholderAvatarIconVisibleAgainstBackground(
    SkColor profile_color_seed,
    int size,
    AvatarVisibilityAgainstBackground visibility) {
  return ui::ResourceBundle::GetSharedInstance().GetImageNamed(
      GetPlaceholderAvatarIconResourceID());
}

// Have to redo implementation here because of the re-definition of the
// GetPlaceholderAvatarIconWithColors function above which is used in this
// function. Also, changes the label from "Default Avatar" to our placeholder
// avatar name.
base::Value::Dict GetDefaultProfileAvatarIconAndLabel(SkColor fill_color,
                                                      SkColor stroke_color,
                                                      bool selected) {
  gfx::Image icon = profiles::GetPlaceholderAvatarIconWithColors(
      fill_color, stroke_color, kAvatarIconSize);
  size_t index = profiles::GetPlaceholderAvatarIndex();
  return GetAvatarIconAndLabelDict(
      webui::GetBitmapDataUrl(icon.AsBitmap()),
      l10n_util::GetStringUTF16(IDS_QORAI_AVATAR_LABEL_PLACEHOLDER), index,
      selected, /*is_gaia_avatar=*/false);
}
base::Value::Dict GetDefaultProfileAvatarIconAndLabel_Qorai(
    SkColor fill_color,
    SkColor stroke_color,
    bool selected) {
  return GetDefaultProfileAvatarIconAndLabel(fill_color, stroke_color,
                                             selected);
}

}  // namespace profiles
