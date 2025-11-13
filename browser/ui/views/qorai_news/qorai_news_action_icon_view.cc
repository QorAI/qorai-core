// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/views/qorai_news/qorai_news_action_icon_view.h"

#include <memory>
#include <utility>
#include <vector>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/functional/callback_forward.h"
#include "qorai/browser/qorai_news/qorai_news_tab_helper.h"
#include "qorai/browser/ui/views/qorai_news/qorai_news_bubble_controller.h"
#include "qorai/browser/ui/views/qorai_news/qorai_news_bubble_view.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/vector_icons/vector_icons.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/views/page_action/page_action_icon_view.h"
#include "components/grit/qorai_components_strings.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/gfx/color_utils.h"
#include "ui/gfx/geometry/skia_conversions.h"
#include "ui/native_theme/native_theme.h"
#include "ui/views/bubble/bubble_dialog_delegate_view.h"

namespace {

constexpr SkColor kSubscribedLightColor = SkColorSetRGB(76, 84, 210);
constexpr SkColor kSubscribedDarkColor = SkColorSetRGB(115, 122, 222);

}  // namespace

QoraiNewsActionIconView::QoraiNewsActionIconView(
    Profile* profile,
    IconLabelBubbleView::Delegate* icon_label_bubble_delegate,
    PageActionIconView::Delegate* page_action_icon_delegate)
    : PageActionIconView(/*command_updater=*/nullptr,
                         /*command_id=*/0,
                         icon_label_bubble_delegate,
                         page_action_icon_delegate,
                         "QoraiNewsFollow") {
  SetLabel(l10n_util::GetStringUTF16(IDS_QORAI_NEWS_ACTION_VIEW_TOOLTIP));

  should_show_.Init(qorai_news::prefs::kShouldShowToolbarButton,
                    profile->GetPrefs(),
                    base::BindRepeating(&QoraiNewsActionIconView::UpdateImpl,
                                        base::Unretained(this)));
  opted_in_.Init(qorai_news::prefs::kQoraiNewsOptedIn, profile->GetPrefs(),
                 base::BindRepeating(&QoraiNewsActionIconView::UpdateImpl,
                                     base::Unretained(this)));
  news_enabled_.Init(qorai_news::prefs::kNewTabPageShowToday,
                     profile->GetPrefs(),
                     base::BindRepeating(&QoraiNewsActionIconView::UpdateImpl,
                                         base::Unretained(this)));

  Update();
}

QoraiNewsActionIconView::~QoraiNewsActionIconView() = default;

void QoraiNewsActionIconView::UpdateImpl() {
  auto* contents = GetWebContents();
  QoraiNewsTabHelper* tab_helper =
      contents ? QoraiNewsTabHelper::FromWebContents(contents) : nullptr;

  // When the active tab changes, subscribe to notification when
  // it has found a feed.
  if (contents && tab_helper) {
    // Observe QoraiNewsTabHelper for feed changes
    if (!page_feeds_observer_.IsObservingSource(tab_helper)) {
      page_feeds_observer_.Reset();
      page_feeds_observer_.Observe(tab_helper);
    }
    // Observe WebContentsObserver for WebContentsDestroyed
    if (web_contents() != contents) {
      Observe(contents);
    }
  } else {
    // Unobserve WebContentsObserver
    if (web_contents()) {
      Observe(nullptr);
    }
    // Unobserve QoraiNewsTabHelper
    if (page_feeds_observer_.IsObserving()) {
      page_feeds_observer_.Reset();
    }
  }

  // Don't show the icon if preferences don't allow
  if (!tab_helper || !should_show_.GetValue() || !news_enabled_.GetValue() ||
      !opted_in_.GetValue()) {
    SetVisible(false);
    return;
  }

  // Verify observing QoraiNewsTabHelper
  DCHECK(page_feeds_observer_.IsObservingSource(tab_helper));
  // Verify observing for WebContentsDestroyed
  DCHECK(web_contents());

  // Icon color changes if any feeds are being followed
  UpdateIconColor(tab_helper->IsSubscribed());

  // Don't show icon if there are no feeds
  const bool has_feeds = !tab_helper->GetAvailableFeedUrls().empty();
  const bool is_visible = has_feeds || IsBubbleShowing();
  SetVisible(is_visible);
}

void QoraiNewsActionIconView::WebContentsDestroyed() {
  page_feeds_observer_.Reset();
  Observe(nullptr);
}

const gfx::VectorIcon& QoraiNewsActionIconView::GetVectorIcon() const {
  return kQoraRssIcon;
}

std::u16string QoraiNewsActionIconView::GetTextForTooltipAndAccessibleName()
    const {
  return l10n_util::GetStringUTF16(IDS_QORAI_NEWS_ACTION_VIEW_TOOLTIP);
}

bool QoraiNewsActionIconView::ShouldShowLabel() const {
  return false;
}

void QoraiNewsActionIconView::OnAvailableFeedsChanged(
    const std::vector<GURL>& feeds) {
  Update();
}

void QoraiNewsActionIconView::OnThemeChanged() {
  bool subscribed = false;
  if (auto* contents = GetWebContents()) {
    subscribed = QoraiNewsTabHelper::FromWebContents(contents)->IsSubscribed();
  }
  UpdateIconColor(subscribed);
  PageActionIconView::OnThemeChanged();
}

void QoraiNewsActionIconView::OnExecuting(
    PageActionIconView::ExecuteSource execute_source) {
  ShowQoraiNewsBubble();
}

void QoraiNewsActionIconView::UpdateIconColor(bool subscribed) {
  SkColor icon_color;
  if (subscribed) {
    auto is_dark = GetNativeTheme()->preferred_color_scheme() ==
                   ui::NativeTheme::PreferredColorScheme::kDark;
    icon_color = is_dark ? kSubscribedDarkColor : kSubscribedLightColor;
  } else {
    icon_color = color_utils::DeriveDefaultIconColor(GetCurrentTextColor());
  }
  SetIconColor(icon_color);
}

qorai_news::QoraiNewsBubbleController* QoraiNewsActionIconView::GetController()
    const {
  auto* web_contents = GetWebContents();
  return web_contents ? qorai_news::QoraiNewsBubbleController::
                            CreateOrGetFromWebContents(web_contents)
                      : nullptr;
}

views::BubbleDialogDelegate* QoraiNewsActionIconView::GetBubble() const {
  auto* controller = GetController();
  return controller ? controller->GetBubble() : nullptr;
}

void QoraiNewsActionIconView::ShowQoraiNewsBubble() {
  if (auto* controller = GetController()) {
    controller->ShowBubble(AsWeakPtr());
  }
}

base::WeakPtr<QoraiNewsActionIconView> QoraiNewsActionIconView::AsWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}

BEGIN_METADATA(QoraiNewsActionIconView)
END_METADATA
