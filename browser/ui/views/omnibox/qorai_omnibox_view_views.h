/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_VIEW_VIEWS_H_
#define QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_VIEW_VIEWS_H_

#include <optional>

#include "base/gtest_prod_util.h"
#include "chrome/browser/ui/views/omnibox/omnibox_view_views.h"
#include "ui/base/metadata/metadata_header_macros.h"

class GURL;

class QoraiOmniboxViewViews : public OmniboxViewViews {
  METADATA_HEADER(QoraiOmniboxViewViews, OmniboxViewViews)

 public:
  using OmniboxViewViews::OmniboxViewViews;

  QoraiOmniboxViewViews(const QoraiOmniboxViewViews&) = delete;
  QoraiOmniboxViewViews& operator=(const QoraiOmniboxViewViews&) = delete;
  ~QoraiOmniboxViewViews() override;

  bool SelectedTextIsURL();
  void CleanAndCopySelectedURL();

 protected:
  std::optional<GURL> GetURLToCopy();
  void CopySanitizedURL(const GURL& url);
#if BUILDFLAG(IS_WIN)
  // View overrides:
  bool AcceleratorPressed(const ui::Accelerator& accelerator) override;
#endif  // BUILDFLAG(IS_WIN)
  bool GetAcceleratorForCommandId(int command_id,
                                  ui::Accelerator* accelerator) const override;

  // ui::views::Textfield
#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_MAC)
  void ExecuteTextEditCommand(ui::TextEditCommand command) override;
#endif
  void ExecuteCommand(int command_id, int event_flags) override;

  // ui::views::TextfieldController:
  void UpdateContextMenu(ui::SimpleMenuModel* menu_contents) override;

 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiOmniboxViewViewsTest, PasteAndSearchTest);

  std::optional<std::u16string> GetClipboardTextForPasteAndSearch();
};

#endif  // QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_VIEW_VIEWS_H_
