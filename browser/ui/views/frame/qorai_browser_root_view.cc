/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/frame/qorai_browser_root_view.h"

#include "qorai/browser/ui/tabs/features.h"
#include "qorai/browser/ui/views/tabs/vertical_tab_utils.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "ui/base/metadata/metadata_impl_macros.h"

QoraiBrowserRootView::QoraiBrowserRootView(BrowserView* browser_view,
                                           views::Widget* widget)
    : BrowserRootView(browser_view, widget), browser_(browser_view->browser()) {
  if (!browser_->profile()->IsRegularProfile()) {
    theme_observation_.Observe(ui::NativeTheme::GetInstanceForNativeUi());
  }
}

QoraiBrowserRootView::~QoraiBrowserRootView() = default;

bool QoraiBrowserRootView::OnMouseWheel(const ui::MouseWheelEvent& event) {
  // Bypass BrowserRootView::OnMouseWheel() to avoid tab cycling feature.
#if BUILDFLAG(IS_LINUX)
  if (!base::FeatureList::IsEnabled(
          tabs::features::kQoraiChangeActiveTabOnScrollEvent)) {
    return RootView::OnMouseWheel(event);
  }
#endif

  // As vertical tabs are always in a scroll view, we should prefer scrolling
  // to tab cycling.
  if (tabs::utils::ShouldShowVerticalTabs(browser_)) {
    return RootView::OnMouseWheel(event);
  }

  return BrowserRootView::OnMouseWheel(event);
}

void QoraiBrowserRootView::OnNativeThemeUpdated(
    ui::NativeTheme* observed_theme) {
  ThemeChanged();
}

BEGIN_METADATA(QoraiBrowserRootView)
END_METADATA
