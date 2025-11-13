// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_SHIELDS_ACTION_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_SHIELDS_ACTION_VIEW_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "chrome/browser/ui/views/bubble/webui_bubble_manager.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/button/label_button.h"
#include "ui/views/controls/button/menu_button_controller.h"
#include "ui/views/widget/widget.h"

class TabStripModel;
class IconWithBadgeImageSource;

class QoraiShieldsActionView
    : public views::LabelButton,
      public qorai_shields::QoraiShieldsTabHelper::Observer,
      public TabStripModelObserver {
  METADATA_HEADER(QoraiShieldsActionView, views::LabelButton)
 public:
  DECLARE_CLASS_ELEMENT_IDENTIFIER_VALUE(kShieldsActionIcon);
  explicit QoraiShieldsActionView(
      BrowserWindowInterface* browser_window_interface);
  QoraiShieldsActionView(const QoraiShieldsActionView&) = delete;
  QoraiShieldsActionView& operator=(const QoraiShieldsActionView&) = delete;
  ~QoraiShieldsActionView() override;

  void Init();
  void Update();

  // views::LabelButton:
  std::unique_ptr<views::LabelButtonBorder> CreateDefaultBorder()
      const override;
  std::u16string GetRenderedTooltipText(const gfx::Point& p) const override;
  void OnThemeChanged() override;

  SkPath GetHighlightPath() const;
  views::Widget* GetBubbleWidget();

 private:
  void ButtonPressed(BrowserWindowInterface* browser_window_interface);
  bool IsPageInReaderMode(content::WebContents* web_contents);
  bool ShouldShowBubble(content::WebContents* web_contents);
  void UpdateIconState();
  gfx::ImageSkia GetIconImage(bool is_enabled);
  std::unique_ptr<IconWithBadgeImageSource> GetImageSource();
  void ShowBubble(GURL webui_url);

  // qorai_shields::QoraiShieldsTabHelper
  void OnResourcesChanged() override;
  void OnShieldsEnabledChanged() override;
  void OnRepeatedReloadsDetected() override;

  // TabStripModelObserver
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;

  const raw_ptr<BrowserWindowInterface> browser_window_interface_ = nullptr;
  raw_ptr<views::MenuButtonController> menu_button_controller_ = nullptr;
  raw_ref<Profile> profile_;
  raw_ref<TabStripModel> tab_strip_model_;
  std::unique_ptr<WebUIBubbleManager> webui_bubble_manager_;
  std::optional<GURL> last_webui_url_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ACTIONS_QORAI_SHIELDS_ACTION_VIEW_H_
