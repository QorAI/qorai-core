/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_PAGE_INFO_TAB_SWITCHER_H_
#define QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_PAGE_INFO_TAB_SWITCHER_H_

#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "qorai/browser/ui/views/page_info/qorai_page_info_view_ids.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/view.h"

namespace gfx {
struct VectorIcon;
}

namespace views {
class LabelButton;
}

// A tab switcher control that allows switching between Shields and Site
// Settings tabs in the page info bubble.
class QoraiPageInfoTabSwitcher : public views::View {
  METADATA_HEADER(QoraiPageInfoTabSwitcher, views::View)

 public:
  enum class Tab {
    kSiteSettings,
    kShields,
  };

  // Callback that is run when the user presses a tab button.
  using TabButtonPressedCallback = base::RepeatingCallback<void(Tab)>;

  explicit QoraiPageInfoTabSwitcher(
      TabButtonPressedCallback on_tab_button_pressed);
  QoraiPageInfoTabSwitcher(const QoraiPageInfoTabSwitcher&) = delete;
  QoraiPageInfoTabSwitcher& operator=(const QoraiPageInfoTabSwitcher&) = delete;
  ~QoraiPageInfoTabSwitcher() override;

  // Returns the currently selected tab.
  Tab GetCurrentTab() const { return current_tab_; }

  // Sets the current tab.
  void SetCurrentTab(Tab tab);

  // Sets whether shields are enabled.
  void SetShieldsEnabled(bool enabled);

  // views::View:
  void Layout(PassKey) override;

 private:
  // Creates a tab button for the specified tab.
  std::unique_ptr<views::LabelButton> CreateTabButton(
      Tab tab,
      QoraiPageInfoViewID view_id);

  // Updates the visual state of all tab buttons.
  void UpdateTabButtons();

  // Updates the visual appearance of a specific tab button.
  void UpdateTabButton(Tab tab);

  // Returns the tab button for the specified tab.
  views::LabelButton* GetButtonForTab(Tab tab);

  // Updates the position of the tab indicator bar under the active button.
  void UpdateTabIndicator();

  // Returns the appropriate text and icon for the specified tab.
  int GetTabButtonText(Tab tab) const;
  const gfx::VectorIcon& GetTabButtonIcon(Tab tab);

  // UI components.
  raw_ptr<views::LabelButton> shields_button_ = nullptr;
  raw_ptr<views::LabelButton> site_settings_button_ = nullptr;
  raw_ptr<views::View> tab_indicator_ = nullptr;

  Tab current_tab_ = Tab::kSiteSettings;
  bool shields_enabled_ = true;
  TabButtonPressedCallback on_tab_button_pressed_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_PAGE_INFO_TAB_SWITCHER_H_
