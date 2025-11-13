/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_PAGE_INFO_BUBBLE_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_PAGE_INFO_BUBBLE_VIEW_H_

#include <utility>

#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"
#include "qorai/browser/ui/views/page_info/qorai_page_info_tab_switcher.h"
#include "chrome/browser/ui/views/page_info/page_info_bubble_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiShieldsPageInfoView;

// Qorai-customized version of Chromium's page info bubble, which displays
// shields, permission, and security information for the current site.
class QoraiPageInfoBubbleView
    : public PageInfoBubbleView,
      public qorai_shields::QoraiShieldsTabHelper::Observer {
  METADATA_HEADER(QoraiPageInfoBubbleView, PageInfoBubbleView)

 public:
  QoraiPageInfoBubbleView(const QoraiPageInfoBubbleView&) = delete;
  QoraiPageInfoBubbleView& operator=(const QoraiPageInfoBubbleView&) = delete;

  ~QoraiPageInfoBubbleView() override;

  // Opens the Shields page after Shields has detected repeated reloads.
  void OpenShieldsPageAfterRepeatedReloads();

  // PageInfoBubbleView:
  void OpenMainPage(base::OnceClosure initialized_callback) override;
  void AnnouncePageOpened(std::u16string announcement) override;

  // views::View:
  gfx::Size CalculatePreferredSize(
      const views::SizeBounds& available_size) const override;
  void ChildPreferredSizeChanged(View* child) override;

  // WebContentsObserver:
  void PrimaryPageChanged(content::Page& page) override;
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;

  // qorai_shields::QoraiShieldsTabHelper::Observer:
  void OnResourcesChanged() override;
  void OnShieldsEnabledChanged() override;

 private:
  friend class PageInfoBubbleView;

  template <typename... Args>
  explicit QoraiPageInfoBubbleView(Args&&... args)
      : PageInfoBubbleView(std::forward<Args>(args)...) {
    InitializeView();
  }

  // Performs view initialization.
  void InitializeView();

  // Applies Qorai-specific customizations to the Chromium page info views.
  void CustomizeChromiumViews();

  // Sets the currently active tab.
  void SwitchToTab(QoraiPageInfoTabSwitcher::Tab tab);

  // Updates content visibility based on the current tab.
  void UpdateContentVisibilityForCurrentTab();

  // Returns a value indicating whether the specified child view was created by
  // the parent class and belongs in the "Site settings" tab.
  bool IsSiteSettingsChildView(views::View* view) const;

  // Returns a value indicating whether a subpage is currently active in the
  // site settings tab.
  bool IsSiteSettingsSubpageActive() const;

  // Returns the `QoraiShieldsTabHelper` instance associated with this web
  // contents.
  qorai_shields::QoraiShieldsTabHelper* GetShieldsTabHelper();

  // Returns a value indicating whether Shields is enabled for the current tab.
  bool IsShieldsEnabledForWebContents();

  // UI components.
  raw_ptr<QoraiPageInfoTabSwitcher> tab_switcher_ = nullptr;
  raw_ptr<QoraiShieldsPageInfoView> shields_page_view_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_PAGE_INFO_BUBBLE_VIEW_H_
