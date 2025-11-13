// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/toolbar/app_menu_icons.h"

#include "base/containers/fixed_flat_map.h"
#include "base/containers/map_util.h"
#include "base/no_destructor.h"
#include "qorai/app/qorai_command_ids.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "chrome/app/chrome_command_ids.h"
#include "ui/base/models/image_model.h"
#include "ui/color/color_id.h"
#include "ui/gfx/vector_icon_types.h"
#include "ui/menus/simple_menu_model.h"

namespace {

constexpr int kQoraIconSize = 16;

constexpr auto kCommandIcons =
    base::MakeFixedFlatMap<int, const gfx::VectorIcon*>({
        // The `App` menu
        {IDC_UPGRADE_DIALOG, &kQoraRocketIcon},
        {IDC_NEW_TAB, &kQoraBrowserAddIcon},
        {IDC_NEW_WINDOW, &kQoraWindowTabNewIcon},
        {IDC_NEW_INCOGNITO_WINDOW, &kQoraWindowTabPrivateIcon},
        {IDC_NEW_TOR_CONNECTION_FOR_SITE, &kQoraWindowTabTorIcon},
        {IDC_NEW_OFFTHERECORD_WINDOW_TOR, &kQoraWindowTabTorIcon},
        {IDC_SHOW_QORAI_REWARDS, &kQoraProductBatOutlineIcon},
        {IDC_SHOW_QORAI_WALLET, &kQoraProductQoraiWalletIcon},
        {IDC_TOGGLE_AI_CHAT, &kQoraProductQoraiQoraIcon},
        {IDC_QORAI_VPN_MENU, &kQoraProductVpnIcon},
        {IDC_PASSWORDS_AND_AUTOFILL_MENU, &kQoraKeyIcon},
        {IDC_RECENT_TABS_MENU, &kQoraHistoryIcon},
        {IDC_BOOKMARKS_MENU, &kQoraProductBookmarksIcon},
        {IDC_SHOW_DOWNLOADS, &kQoraDownloadIcon},
        {IDC_MANAGE_EXTENSIONS, &kQoraBrowserExtensionsIcon},
        {IDC_EXTENSIONS_SUBMENU_MANAGE_EXTENSIONS, &kQoraBrowserExtensionsIcon},
        {IDC_EXTENSIONS_SUBMENU_VISIT_CHROME_WEB_STORE, &kQoraShoppingBagIcon},
        {IDC_ZOOM_MENU, &kQoraSearchZoomInIcon},
        {IDC_PRINT, &kQoraPrintIcon},
        {IDC_FIND_AND_EDIT_MENU, &kQoraFileSearchIcon},
        {IDC_SAVE_AND_SHARE_MENU, &kQoraFileDownloadIcon},
        {IDC_MORE_TOOLS_MENU, &kQoraWindowScrewdriverIcon},
        {IDC_OPTIONS, &kQoraSettingsIcon},
        {IDC_HELP_MENU, &kQoraHelpOutlineIcon},
        {IDC_EXIT, &kQoraCloseIcon},

        // The `VPN` submenu
        {IDC_TOGGLE_QORAI_VPN, &kQoraProductVpnIcon},
        {IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON, &kQoraEyeOnIcon},
        {IDC_SHOW_QORAI_VPN_PANEL, &kQoraProductVpnIcon},
        {IDC_SEND_QORAI_VPN_FEEDBACK, &kQoraMessageBubbleHeartIcon},
        {IDC_MANAGE_QORAI_VPN_PLAN, &kQoraLaunchIcon},
        {IDC_ABOUT_QORAI_VPN, &kQoraInfoOutlineIcon},

        // The `Bookmarks` submenu
        {IDC_BOOKMARK_THIS_TAB, &kQoraBrowserBookmarkAddIcon},
        {IDC_BOOKMARK_ALL_TABS, &kQoraBrowserBookmarkPluralIcon},
        {IDC_QORAI_BOOKMARK_BAR_SUBMENU, &kQoraProductBookmarksIcon},
        {IDC_SHOW_BOOKMARK_MANAGER, &kQoraWindowBookmarkIcon},
        {IDC_SHOW_BOOKMARK_SIDE_PANEL, &kQoraProductBookmarksIcon},
        {IDC_IMPORT_SETTINGS, &kQoraImportArrowIcon},
        {IDC_READING_LIST_MENU, &kQoraReadingListIcon},

        // The `History submenu
        {IDC_SHOW_HISTORY, &kQoraHistoryIcon},
        {IDC_CLEAR_BROWSING_DATA, &kQoraTrashIcon},
        {IDC_RECENT_TABS_NO_DEVICE_TABS, &kQoraSmartphoneLaptopIcon},

        // The `Help` submenu
        {IDC_ABOUT, &kQoraQoraiIconMonochromeIcon},
        {IDC_HELP_PAGE_VIA_MENU, &kQoraHelpOutlineIcon},
        {IDC_SHOW_QORAI_WEBCOMPAT_REPORTER, &kQoraWarningTriangleOutlineIcon},

        // The `Passwords and autofill` submenu
        {IDC_SHOW_PASSWORD_MANAGER, &kQoraKeyIcon},
        {IDC_SHOW_PAYMENT_METHODS, &kQoraCreditCardIcon},
        {IDC_SHOW_ADDRESSES, &kQoraLocationOnIcon},

        // The `Find and edit` submenu
        {IDC_FIND, &kQoraSearchIcon},
        // Use when cut icon is ready.
        // {IDC_CUT, &kQoraCutIcon},
        {IDC_COPY, &kQoraCopyIcon},
        {IDC_PASTE, &kQoraClipboardIcon},

        // The `Save and share` submenu
        {IDC_SAVE_PAGE, &kQoraFileDownloadIcon},
        {IDC_INSTALL_PWA, &kQoraPwaInstallIcon},
        {IDC_OPEN_IN_PWA_WINDOW, &kQoraLaunchIcon},
        {IDC_CREATE_SHORTCUT, &kQoraShareWindowsIcon},
        {IDC_COPY_URL, &kQoraLinkNormalIcon},
        {IDC_SEND_TAB_TO_SELF, &kQoraSmartphoneLaptopIcon},
        {IDC_QRCODE_GENERATOR, &kQoraQrCodeIcon},
        {IDC_SHARING_HUB_SCREENSHOT, &kQoraScreenshotIcon},

        // The `Reading list` submenu
        {IDC_READING_LIST_MENU_ADD_TAB, &kQoraReadingListAddIcon},
        {IDC_READING_LIST_MENU_SHOW_UI, &kQoraReadingListIcon},

        // The `More tools` submenu
        {IDC_ADD_NEW_PROFILE, &kQoraUserAddIcon},
        {IDC_OPEN_GUEST_PROFILE, &kQoraUserCircleIcon},
        {IDC_NAME_WINDOW, &kQoraEditBoxIcon},
        {IDC_COMMANDER, &kQoraArrowSmallRightIcon},
        {IDC_SHOW_APPS_PAGE, &kQoraGrid04Icon},
        {IDC_PERFORMANCE, &kQoraNetworkSpeedFastIcon},
        {IDC_DEV_TOOLS, &kQoraCodeIcon},
        {IDC_TASK_MANAGER_APP_MENU, &kQoraWindowBinaryCodeIcon},
        {IDC_SHOW_QORAI_SYNC, &kQoraProductSyncIcon},
        {IDC_ROUTE_MEDIA, &kQoraChromeCastIcon},
        {IDC_SIDEBAR_SHOW_OPTION_MENU, &kQoraBrowserSidebarRightIcon},
    });

}  // namespace

void ApplyQoraIcons(ui::SimpleMenuModel* menu) {
  // Menu can be null in some tests.
  if (!menu) {
    return;
  }

  for (size_t i = 0; i < menu->GetItemCount(); ++i) {
    if (auto* icon =
            base::FindPtrOrNull(kCommandIcons, menu->GetCommandIdAt(i))) {
      menu->SetIcon(i, ui::ImageModel::FromVectorIcon(
                           *icon, ui::ColorIds::kColorMenuIcon, kQoraIconSize));
    }
  }
}
