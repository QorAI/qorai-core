/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_COLOR_QORAI_COLOR_ID_H_
#define QORAI_BROWSER_UI_COLOR_QORAI_COLOR_ID_H_

#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "chrome/browser/ui/color/chrome_color_id.h"

// clang-format off

#define QORAI_COMMON_COLOR_IDS                       \
    E_CPONLY(kColorForTest)                          \
    E_CPONLY(kColorIconBase)                         \
    E_CPONLY(kColorMenuItemSubText)                  \
    E_CPONLY(kColorBookmarkBarInstructionsText)      \
    E_CPONLY(kColorBookmarkBarInstructionsLink)      \
    E_CPONLY(kColorLocationBarFocusRing)             \
    E_CPONLY(kColorLocationBarHoveredShadow)         \
    E_CPONLY(kColorDialogDontAskAgainButton)         \
    E_CPONLY(kColorDialogDontAskAgainButtonHovered)  \
    E_CPONLY(kColorTabGroupBackgroundAlpha)          \
    E_CPONLY(kColorWebDiscoveryInfoBarBackground)    \
    E_CPONLY(kColorWebDiscoveryInfoBarMessage)       \
    E_CPONLY(kColorWebDiscoveryInfoBarLink)          \
    E_CPONLY(kColorWebDiscoveryInfoBarNoThanks)      \
    E_CPONLY(kColorWebDiscoveryInfoBarClose)         \
    E_CPONLY(kColorQoraiDownloadToolbarButtonActive) \
    E_CPONLY(kColorToolbarButtonActivated)

#define QORAI_SEARCH_CONVERSION_COLOR_IDS                             \
    E_CPONLY(kColorSearchConversionCloseButton)                       \
    E_CPONLY(kColorSearchConversionBannerTypeBackground)              \
    E_CPONLY(kColorSearchConversionBannerTypeBackgroundBorder)        \
    E_CPONLY(kColorSearchConversionBannerTypeBackgroundBorderHovered) \
    E_CPONLY(kColorSearchConversionBannerTypeBackgroundGradientFrom)  \
    E_CPONLY(kColorSearchConversionBannerTypeBackgroundGradientTo)    \
    E_CPONLY(kColorSearchConversionBannerTypeDescText)                \
    E_CPONLY(kColorSearchConversionButtonBorder)                      \
    E_CPONLY(kColorSearchConversionButtonBackground)                  \
    E_CPONLY(kColorSearchConversionButtonBackgroundHovered)           \
    E_CPONLY(kColorSearchConversionButtonText)                        \
    E_CPONLY(kColorSearchConversionButtonCaratRight)                  \
    E_CPONLY(kColorSearchConversionButtonCloseButton)                 \
    E_CPONLY(kColorSearchConversionButtonCloseButtonHovered)          \
    E_CPONLY(kColorSearchConversionButtonShadow1)                     \
    E_CPONLY(kColorSearchConversionButtonShadow2)

#define QORAI_SIDEBAR_COLOR_IDS                               \
    E_CPONLY(kColorSidebarAddBubbleBackground)                \
    E_CPONLY(kColorSidebarAddBubbleHeaderText)                \
    E_CPONLY(kColorSidebarAddBubbleItemTextBackgroundHovered) \
    E_CPONLY(kColorSidebarAddBubbleItemTextHovered)           \
    E_CPONLY(kColorSidebarAddBubbleItemTextNormal)            \
    E_CPONLY(kColorSidebarAddButtonDisabled)                  \
    E_CPONLY(kColorSidebarArrowBackgroundHovered)             \
    E_CPONLY(kColorSidebarArrowDisabled)                      \
    E_CPONLY(kColorSidebarArrowNormal)                        \
    E_CPONLY(kColorSidebarButtonBase)                         \
    E_CPONLY(kColorSidebarButtonPressed)                      \
    E_CPONLY(kColorSidebarItemDragIndicator)                  \
    E_CPONLY(kColorSidebarSeparator)                          \
    E_CPONLY(kColorSidebarPanelHeaderSeparator)               \
    E_CPONLY(kColorSidebarPanelHeaderBackground)              \
    E_CPONLY(kColorSidebarPanelHeaderTitle)                   \
    E_CPONLY(kColorSidebarPanelHeaderButton)                  \
    E_CPONLY(kColorSidebarPanelHeaderButtonHovered)

#if BUILDFLAG(ENABLE_SPEEDREADER)
#define QORAI_SPEEDREADER_COLOR_IDS      \
  E_CPONLY(kColorSpeedreaderIcon)        \
  E_CPONLY(kColorSpeedreaderToggleThumb) \
  E_CPONLY(kColorSpeedreaderToggleTrack) \
  E_CPONLY(kColorSpeedreaderToolbarBackground) \
  E_CPONLY(kColorSpeedreaderToolbarBorder) \
  E_CPONLY(kColorSpeedreaderToolbarForeground) \
  E_CPONLY(kColorSpeedreaderToolbarButtonHover) \
  E_CPONLY(kColorSpeedreaderToolbarButtonActive) \
  E_CPONLY(kColorSpeedreaderToolbarButtonActiveText)\
  E_CPONLY(kColorSpeedreaderToolbarButtonBorder)
#else
#define QORAI_SPEEDREADER_COLOR_IDS
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#define QORAI_VPN_COLOR_IDS                        \
   E_CPONLY(kColorQoraiVpnButtonIconConnected)     \
    E_CPONLY(kColorQoraiVpnButtonIconDisconnected) \
    E_CPONLY(kColorQoraiVpnButtonIconError)        \
    E_CPONLY(kColorQoraiVpnButtonBackgroundNormal) \
    E_CPONLY(kColorQoraiVpnButtonErrorBackgroundNormal)
#else
#define QORAI_VPN_COLOR_IDS
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
#define QORAI_WAYBACK_MACHINE_COLOR_IDS      \
    E_CPONLY(kColorWaybackMachineURLLoaded)  \
    E_CPONLY(kColorWaybackMachineURLNotAvailable)
#else
#define QORAI_WAYBACK_MACHINE_COLOR_IDS
#endif

// Unfortunately, we can't have a defined(TOOLKIT_VIEWS) guard here
// as qorai_color_mixer depends on this without deps to //ui/views:flags.
// But it's safe have without the guard as this file is included only when
// !is_android.
#define QORAI_VERTICAL_TAB_COLOR_IDS                        \
    E_CPONLY(kColorQoraiVerticalTabSeparator)               \
    E_CPONLY(kColorQoraiVerticalTabActiveBackground)        \
    E_CPONLY(kColorQoraiVerticalTabHoveredBackground)       \
    E_CPONLY(kColorQoraiVerticalTabInactiveBackground)      \
    E_CPONLY(kColorQoraiVerticalTabNTBIconColor)            \
    E_CPONLY(kColorQoraiVerticalTabNTBTextColor)            \
    E_CPONLY(kColorQoraiVerticalTabNTBShortcutTextColor)

#define QORAI_SHARED_PINNED_TAB_COLOR_IDS                    \
    E_CPONLY(kColorQoraiSharedPinnedTabDummyViewBackground)  \
    E_CPONLY(kColorQoraiSharedPinnedTabDummyViewTitle)       \
    E_CPONLY(kColorQoraiSharedPinnedTabDummyViewDescription) \
    E_CPONLY(kColorQoraiSharedPinnedTabDummyViewThumbnailBorder)


#define QORAI_SPLIT_VIEW_COLOR_IDS \
    E_CPONLY(kColorQoraiSplitViewTileBackgroundHorizontal) \
    E_CPONLY(kColorQoraiSplitViewTileBackgroundVertical)   \
    E_CPONLY(kColorQoraiSplitViewTileBackgroundBorder)     \
    E_CPONLY(kColorQoraiSplitViewTileDivider)              \
    E_CPONLY(kColorQoraiSplitViewActiveWebViewBorder)      \
    E_CPONLY(kColorQoraiSplitViewInactiveWebViewBorder)    \
    E_CPONLY(kColorQoraiSplitViewMenuButtonIcon)           \
    E_CPONLY(kColorQoraiSplitViewMenuButtonBackground)     \
    E_CPONLY(kColorQoraiSplitViewMenuButtonBorder)         \
    E_CPONLY(kColorQoraiSplitViewMenuItemIcon)             \
    E_CPONLY(kColorQoraiSplitViewUrl)


#define QORAI_PLAYLIST_COLOR_IDS                                      \
    E_CPONLY(kColorQoraiPlaylistAddedIcon)                            \
    E_CPONLY(kColorQoraiPlaylistCheckedIcon)                          \
    E_CPONLY(kColorQoraiPlaylistSelectedBackground)                   \
    E_CPONLY(kColorQoraiPlaylistListBorder)                           \
    E_CPONLY(kColorQoraiPlaylistMoveDialogDescription)                \
    E_CPONLY(kColorQoraiPlaylistMoveDialogCreatePlaylistAndMoveTitle) \
    E_CPONLY(kColorQoraiPlaylistNewPlaylistDialogNameLabel)           \
    E_CPONLY(kColorQoraiPlaylistNewPlaylistDialogItemsLabel)          \
    E_CPONLY(kColorQoraiPlaylistTextInteractive)

#define QORAI_OMNIBOX_COLOR_IDS \
    E_CPONLY(kColorQoraiOmniboxResultViewSeparator)

#define QORAI_EXTENSION_MENU_COLOR_IDS \
    E_CPONLY(kColorQoraiExtensionMenuIcon)

#define QORAI_APP_MENU_COLOR_IDS \
    E_CPONLY(kColorQoraiAppMenuAccentColor)

#define QORAI_COLOR_IDS               \
    QORAI_COMMON_COLOR_IDS            \
    QORAI_SEARCH_CONVERSION_COLOR_IDS \
    QORAI_SIDEBAR_COLOR_IDS           \
    QORAI_SPEEDREADER_COLOR_IDS       \
    QORAI_VPN_COLOR_IDS               \
    QORAI_VERTICAL_TAB_COLOR_IDS      \
    QORAI_SHARED_PINNED_TAB_COLOR_IDS \
    QORAI_SPLIT_VIEW_COLOR_IDS        \
    QORAI_PLAYLIST_COLOR_IDS          \
    QORAI_OMNIBOX_COLOR_IDS           \
    QORAI_WAYBACK_MACHINE_COLOR_IDS   \
    QORAI_EXTENSION_MENU_COLOR_IDS    \
    QORAI_APP_MENU_COLOR_IDS

#include "ui/color/color_id_macros.inc"

enum QoraiColorIds : ui::ColorId {
  kQoraiColorsStart = kChromeColorsEnd,

  QORAI_COLOR_IDS

  kQoraiColorsEnd,
};

#include "ui/color/color_id_macros.inc"  // NOLINT

// clang-format on

#endif  // QORAI_BROWSER_UI_COLOR_QORAI_COLOR_ID_H_
