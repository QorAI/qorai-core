/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/page_info/qorai_page_info_bubble_view.h"

#include "qorai/browser/ui/page_info/features.h"
#include "qorai/browser/ui/views/page_info/qorai_shields_page_info_view.h"
#include "chrome/browser/ui/views/page_info/page_info_view_factory.h"
#include "components/tabs/public/tab_interface.h"
#include "content/public/browser/navigation_handle.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/views/view_class_properties.h"

using Tab = QoraiPageInfoTabSwitcher::Tab;

QoraiPageInfoBubbleView::~QoraiPageInfoBubbleView() {
  if (auto* shields_tab_helper = GetShieldsTabHelper()) {
    shields_tab_helper->RemoveObserver(this);
  }
}

void QoraiPageInfoBubbleView::OpenShieldsPageAfterRepeatedReloads() {
  shields_page_view_->ShowRepeatedReloadsView();
  SwitchToTab(Tab::kShields);
}

void QoraiPageInfoBubbleView::OpenMainPage(
    base::OnceClosure initialized_callback) {
  PageInfoBubbleView::OpenMainPage(std::move(initialized_callback));
  CustomizeChromiumViews();
  SizeToContents();
}

void QoraiPageInfoBubbleView::AnnouncePageOpened(std::u16string announcement) {
  // This method is called after any PageInfo subpage is opened and allows us to
  // customize child views added by the superclass.
  PageInfoBubbleView::AnnouncePageOpened(std::move(announcement));
  CustomizeChromiumViews();
  SizeToContents();

  // When a subpage is opened programmatically (e.g. when the page info bubble
  // is opened directly to a subpage), ensure that the Site Settings tab is
  // active.
  if (page_info::features::IsShowQoraiShieldsInPageInfoEnabled()) {
    SwitchToTab(Tab::kSiteSettings);
  }
}

gfx::Size QoraiPageInfoBubbleView::CalculatePreferredSize(
    const views::SizeBounds& available_size) const {
  gfx::Size size = PageInfoBubbleView::CalculatePreferredSize(available_size);

  if (page_info::features::IsShowQoraiShieldsInPageInfoEnabled()) {
    // This bubble needs to be larger than the parent class in order to show the
    // full tab switcher and Shields content.
    constexpr int kMinBubbleWidth = 388;
    size.set_width(std::max(size.width(), kMinBubbleWidth));
  }

  return size;
}

void QoraiPageInfoBubbleView::ChildPreferredSizeChanged(View* child) {
  // When child preferred sizes change (e.g. when the Shields page view is auto
  // resized), we need to make sure that layout caches are dropped before
  // calculating the size of the bubble.
  InvalidateLayout();
  SizeToContents();
}

void QoraiPageInfoBubbleView::PrimaryPageChanged(content::Page& page) {
  // The superclass closes the bubble when this event occurs. Since we are
  // displaying the Shields UI and we want users to be able to toggle Shields
  // settings (which reloads the page) without closing the bubble.
}

void QoraiPageInfoBubbleView::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  // Returns true if the page info bubble should be closed for this navigation.
  // Although we want to leave the bubble open when the user toggles Shields
  // settings, we must be careful to not allow the superclass to display stale
  // site information.
  auto should_close_bubble = [&]() {
    // We can ignore any navigation that is not a primary page change.
    const bool is_page_change = navigation_handle->IsInPrimaryMainFrame() &&
                                !navigation_handle->IsSameDocument() &&
                                navigation_handle->HasCommitted();
    if (!is_page_change) {
      return false;
    }

    // Close the bubble if the Shields integration flag is not enabled.
    if (!page_info::features::IsShowQoraiShieldsInPageInfoEnabled()) {
      return true;
    }

    // Always close the bubble if this is a cross-origin navigation, regardless
    // of any other considerations.
    if (!navigation_handle->IsSameOrigin()) {
      return true;
    }

    // We can leave the bubble open if this is a reload (e.g. the user has
    // made a change to Shields settings for the current tab).
    if (navigation_handle->GetReloadType() != content::ReloadType::NONE) {
      return false;
    }

    return true;
  };

  if (should_close_bubble()) {
    CloseBubble();
  }
}

void QoraiPageInfoBubbleView::OnResourcesChanged() {
  CHECK(tab_switcher_);
  tab_switcher_->SetShieldsEnabled(IsShieldsEnabledForWebContents());
}

void QoraiPageInfoBubbleView::OnShieldsEnabledChanged() {
  CHECK(tab_switcher_);
  tab_switcher_->SetShieldsEnabled(IsShieldsEnabledForWebContents());
}

void QoraiPageInfoBubbleView::InitializeView() {
  if (!page_info::features::IsShowQoraiShieldsInPageInfoEnabled()) {
    return;
  }

  // Obtain a reference to the Shields tab helper and observe it.  This will
  // allow us to customize the view based on the current Shields status.
  auto* shields_tab_helper = GetShieldsTabHelper();
  CHECK(shields_tab_helper);
  shields_tab_helper->AddObserver(this);

  CustomizeChromiumViews();

  // Remove the top margin set by the parent class.
  set_margins(gfx::Insets());

  // Add the tab switcher at the top of the bubble.
  auto tab_switcher =
      std::make_unique<QoraiPageInfoTabSwitcher>(base::BindRepeating(
          &QoraiPageInfoBubbleView::SwitchToTab, base::Unretained(this)));
  tab_switcher_ = AddChildViewAt(std::move(tab_switcher), 0);

  // If the PageInfo bubble was not opened directly to a subpage, then show the
  // Shields tab first.
  tab_switcher_->SetCurrentTab(
      IsSiteSettingsSubpageActive() ? Tab::kSiteSettings : Tab::kShields);
  OnShieldsEnabledChanged();

  // Add the Qorai Shields view.
  auto* tab_interface = tabs::TabInterface::GetFromContents(web_contents());
  shields_page_view_ = AddChildView(std::make_unique<QoraiShieldsPageInfoView>(
      tab_interface->GetBrowserWindowInterface(),
      base::BindRepeating(&PageInfoBubbleView::CloseBubble,
                          base::Unretained(this))));

  UpdateContentVisibilityForCurrentTab();
  SizeToContents();
}

void QoraiPageInfoBubbleView::CustomizeChromiumViews() {
  if (!page_info::features::IsShowQoraiShieldsInPageInfoEnabled()) {
    return;
  }

  // Hide the close button in the page header for the main page or any subpage.
  auto* close_button =
      GetViewByID(PageInfoViewFactory::VIEW_ID_PAGE_INFO_CLOSE_BUTTON);
  if (close_button) {
    close_button->SetVisible(false);
  }

  // Find the first site settings content child and set its top margin.
  for (views::View* child : children()) {
    if (IsSiteSettingsChildView(child)) {
      const int top_margin = IsSiteSettingsSubpageActive() ? 16 : 8;
      child->SetProperty(views::kMarginsKey, gfx::Insets().set_top(top_margin));
      break;
    }
  }
}

void QoraiPageInfoBubbleView::SwitchToTab(Tab tab) {
  CHECK(tab_switcher_);
  tab_switcher_->SetCurrentTab(tab);
  UpdateContentVisibilityForCurrentTab();
  SizeToContents();
}

void QoraiPageInfoBubbleView::UpdateContentVisibilityForCurrentTab() {
  CHECK(tab_switcher_);
  Tab current_tab = tab_switcher_->GetCurrentTab();

  // Show/hide the Qorai Shields page.
  CHECK(shields_page_view_);
  shields_page_view_->SetVisible(current_tab == Tab::kShields);

  // Show/hide Chromium page info content.
  for (views::View* child : children()) {
    if (IsSiteSettingsChildView(child)) {
      child->SetVisible(current_tab == Tab::kSiteSettings);
    }
  }
}

bool QoraiPageInfoBubbleView::IsSiteSettingsChildView(views::View* view) const {
  return view->parent() == this && view != tab_switcher_ &&
         view != shields_page_view_;
}

bool QoraiPageInfoBubbleView::IsSiteSettingsSubpageActive() const {
  // If a back button exists in the view tree, then we known that the view is
  // displaying a subpage.
  auto* back_button =
      GetViewByID(PageInfoViewFactory::VIEW_ID_PAGE_INFO_BACK_BUTTON);
  return back_button;
}

qorai_shields::QoraiShieldsTabHelper*
QoraiPageInfoBubbleView::GetShieldsTabHelper() {
  if (!web_contents()) {
    return nullptr;
  }
  return qorai_shields::QoraiShieldsTabHelper::FromWebContents(web_contents());
}

bool QoraiPageInfoBubbleView::IsShieldsEnabledForWebContents() {
  auto* tab_helper = GetShieldsTabHelper();
  return tab_helper && tab_helper->GetQoraiShieldsEnabled();
}

BEGIN_METADATA(QoraiPageInfoBubbleView)
END_METADATA
