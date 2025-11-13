/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_EXTENSIONS_QORAI_EXTENSIONS_MENU_MAIN_PAGE_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_EXTENSIONS_QORAI_EXTENSIONS_MENU_MAIN_PAGE_VIEW_H_

#include "chrome/browser/ui/views/extensions/extensions_menu_main_page_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiExtensionsMenuMainPageView : public ExtensionsMenuMainPageView {
  METADATA_HEADER(QoraiExtensionsMenuMainPageView, ExtensionsMenuMainPageView)

 public:
  QoraiExtensionsMenuMainPageView(Browser* browser,
                                  ExtensionsMenuHandler* menu_handler);
  ~QoraiExtensionsMenuMainPageView() override;

  // QoraiExtensionsMenuMainPageView:
  void OnThemeChanged() override;

 private:
  void UpdateButtons();
};

#endif  // QORAI_BROWSER_UI_VIEWS_EXTENSIONS_QORAI_EXTENSIONS_MENU_MAIN_PAGE_VIEW_H_
