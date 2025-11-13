/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/extensions/qorai_extensions_menu_main_page_view.h"

#define QORAI_EXTENSIONS_MENU_VIEW_CONTROLLER_OPEN_MAIN_PAGE               \
  {                                                                        \
    auto main_page =                                                       \
        std::make_unique<QoraiExtensionsMenuMainPageView>(browser_, this); \
    UpdateMainPage(main_page.get(), GetActiveWebContents());               \
    PopulateMainPage(main_page.get());                                     \
    SwitchToPage(std::move(main_page));                                    \
    return;                                                                \
  }

#include <chrome/browser/ui/views/extensions/extensions_menu_view_controller.cc>

#undef QORAI_EXTENSIONS_MENU_VIEW_CONTROLLER_OPEN_MAIN_PAGE
