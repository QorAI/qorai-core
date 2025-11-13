/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_RESULT_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_RESULT_VIEW_H_

#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/views/omnibox/omnibox_result_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiSearchConversionPromotionView;
class QoraiOmniboxPopupViewViews;

namespace views {
class Label;
}

// This will render qorai specific matches such as the qorair search conversion
// promotion.
class QoraiOmniboxResultView : public OmniboxResultView {
  METADATA_HEADER(QoraiOmniboxResultView, OmniboxResultView)
 public:
  using OmniboxResultView::OmniboxResultView;
  QoraiOmniboxResultView(const QoraiOmniboxResultView&) = delete;
  QoraiOmniboxResultView& operator=(const QoraiOmniboxResultView&) = delete;
  ~QoraiOmniboxResultView() override;

  void OpenMatch();
  void RefreshOmniboxResult();
  QoraiOmniboxPopupViewViews* GetPopupView();

  // OmniboxResultView overrides:
  void SetMatch(const AutocompleteMatch& match) override;
  void OnSelectionStateChanged() override;
  gfx::Image GetIcon() const override;
  void OnThemeChanged() override;
  void OnPaintBackground(gfx::Canvas* canvas) override;

 private:
  void ResetChildren();
  void UpdateForQoraiSearchConversion();
  void HandleSelectionStateChangedForPromotionView();
  void UpdateForQoraMatch();

  // Qorai search conversion promotion
  raw_ptr<QoraiSearchConversionPromotionView> qorai_search_promotion_view_ =
      nullptr;

  raw_ptr<views::Label> qora_match_label_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_RESULT_VIEW_H_
