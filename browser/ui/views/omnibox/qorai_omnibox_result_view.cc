/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/omnibox/qorai_omnibox_result_view.h"

#include <memory>

#include "base/check.h"
#include "base/time/time.h"
#include "qorai/browser/ui/color/qorai_color_id.h"
#include "qorai/browser/ui/views/omnibox/qorai_omnibox_popup_view_views.h"
#include "qorai/browser/ui/views/omnibox/qorai_search_conversion_promotion_view.h"
#include "qorai/components/omnibox/browser/qora_provider.h"
#include "qorai/components/omnibox/browser/promotion_utils.h"
#include "qorai/grit/qorai_theme_resources.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/ui/omnibox/omnibox_controller.h"
#include "chrome/browser/ui/omnibox/omnibox_edit_model.h"
#include "chrome/browser/ui/views/omnibox/omnibox_match_cell_view.h"
#include "chrome/browser/ui/views/omnibox/omnibox_popup_view_views.h"
#include "chrome/browser/ui/views/omnibox/omnibox_suggestion_button_row_view.h"
#include "components/grit/qorai_components_strings.h"
#include "components/omnibox/browser/autocomplete_controller.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_result.h"
#include "components/omnibox/browser/omnibox_popup_selection.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/window_open_disposition.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/scoped_canvas.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/views/controls/label.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/layout/flex_layout.h"
#include "ui/views/layout/flex_layout_types.h"
#include "ui/views/view_class_properties.h"

QoraiOmniboxResultView::~QoraiOmniboxResultView() = default;

void QoraiOmniboxResultView::ResetChildren() {
  if (qorai_search_promotion_view_) {
    RemoveChildViewT(qorai_search_promotion_view_);
    qorai_search_promotion_view_ = nullptr;
  }

  if (qora_match_label_) {
    qora_match_label_->parent()->RemoveChildViewT(
        qora_match_label_.ExtractAsDangling());
  }

  // Reset children visibility. Their visibility could be configured later
  // based on |match_| and the current input.
  // Reset upstream's layout manager.
  SetLayoutManager(std::make_unique<views::FillLayout>());
  for (auto& child : children()) {
    child->SetVisible(true);
  }
}

void QoraiOmniboxResultView::SetMatch(const AutocompleteMatch& match) {
  ResetChildren();
  OmniboxResultView::SetMatch(match);

  UpdateForQoraiSearchConversion();
  UpdateForQoraMatch();
}

void QoraiOmniboxResultView::OnSelectionStateChanged() {
  OmniboxResultView::OnSelectionStateChanged();

  HandleSelectionStateChangedForPromotionView();
}

gfx::Image QoraiOmniboxResultView::GetIcon() const {
  if (QoraProvider::IsMatchFromQoraProvider(match_)) {
    // As Qora icon has gradient color, we can't use vector icon because it lacks
    // of gradient color.
    return ui::ResourceBundle::GetSharedInstance().GetImageNamed(
        IDR_QORA_FAVICON);
  }
  return OmniboxResultView::GetIcon();
}

void QoraiOmniboxResultView::OnThemeChanged() {
  OmniboxResultView::OnThemeChanged();
  UpdateForQoraMatch();
}

void QoraiOmniboxResultView::OpenMatch() {
  popup_view_->model()->OpenSelection(OmniboxPopupSelection(model_index_),
                                      base::TimeTicks::Now());
}

void QoraiOmniboxResultView::RefreshOmniboxResult() {
  auto* controller = popup_view_->controller()->autocomplete_controller();

  // To refresh autocomplete result, start again with current input.
  controller->Start(controller->input());
}

QoraiOmniboxPopupViewViews* QoraiOmniboxResultView::GetPopupView() {
  return static_cast<QoraiOmniboxPopupViewViews*>(popup_view_);
}

void QoraiOmniboxResultView::HandleSelectionStateChangedForPromotionView() {
  if (qorai_search_promotion_view_ && IsQoraiSearchPromotionMatch(match_)) {
    qorai_search_promotion_view_->OnSelectionStateChanged(
        GetMatchSelected() &&
        popup_view_->GetSelection().state == OmniboxPopupSelection::NORMAL);
  }
}

void QoraiOmniboxResultView::UpdateForQoraiSearchConversion() {
  if (!IsQoraiSearchPromotionMatch(match_)) {
    return;
  }

  // Hide upstream children and show our promotion view.
  // It'll be the only visible child view.
  for (auto& child : children()) {
    child->SetVisible(false);
  }

  // To have proper size for promotion view.
  SetLayoutManager(std::make_unique<views::FlexLayout>())
      ->SetOrientation(views::LayoutOrientation::kVertical);

  CHECK(!qorai_search_promotion_view_);
  auto* controller = popup_view_->controller()->autocomplete_controller();
  auto* prefs = controller->autocomplete_provider_client()->GetPrefs();
  qorai_search_promotion_view_ =
      AddChildView(std::make_unique<QoraiSearchConversionPromotionView>(
          this, g_browser_process->local_state(), prefs,
          popup_view_->controller()->client()->GetTemplateURLService()));

  qorai_search_promotion_view_->SetTypeAndInput(
      GetConversionTypeFromMatch(match_),
      popup_view_->controller()->autocomplete_controller()->input().text());
  HandleSelectionStateChangedForPromotionView();
}

void QoraiOmniboxResultView::UpdateForQoraMatch() {
  if (QoraProvider::IsMatchFromQoraProvider(match_)) {
    constexpr int kQoraMatchPadding = 4;
    SetProperty(views::kMarginsKey, gfx::Insets().set_top(kQoraMatchPadding));
    if (auto* cp = GetColorProvider()) {
      SetBorder(views::CreatePaddedBorder(
          views::CreateSolidSidedBorder(
              gfx::Insets().set_top(1),
              cp->GetColor(kColorQoraiOmniboxResultViewSeparator)),
          gfx::Insets().set_top(kQoraMatchPadding)));

      if (!qora_match_label_) {
        // Note: The |suggestion_view_| is a child of suggestion_and_button_row
        // which has a FlexLayout but is not stored in a field, so we have to
        // go via |suggestion_view_->parent()| to add |qora_match_label_|.
        qora_match_label_ = suggestion_view_->parent()->AddChildView(
            std::make_unique<views::Label>(
                l10n_util::GetStringUTF16(IDS_OMNIBOX_SELECT_ASK_QORA_HINT)));
        qora_match_label_->SetHorizontalAlignment(gfx::ALIGN_RIGHT);
        qora_match_label_->SetBorder(
            views::CreateEmptyBorder(gfx::Insets().set_left_right(24, 24)));
        qora_match_label_->SetProperty(
            views::kFlexBehaviorKey,
            views::FlexSpecification(views::LayoutOrientation::kHorizontal,
                                     views::MinimumFlexSizeRule::kPreferred,
                                     views::MaximumFlexSizeRule::kUnbounded));
      }

      // The "Press ↑ to highlight" label should only be visible when pressing
      // up will actually highlight it.
      qora_match_label_->SetVisible(popup_view_->GetSelection().line == 0 &&
                                   !GetMatchSelected());
    }
  } else {
    ClearProperty(views::kMarginsKey);
    SetBorder(nullptr);
  }
}

void QoraiOmniboxResultView::OnPaintBackground(gfx::Canvas* canvas) {
  gfx::ScopedCanvas scoped_canvas(canvas);
  if (QoraProvider::IsMatchFromQoraProvider(match_)) {
    // Clip upper padding
    canvas->ClipRect(GetContentsBounds());
  }

  OmniboxResultView::OnPaintBackground(canvas);
}

BEGIN_METADATA(QoraiOmniboxResultView)
END_METADATA
