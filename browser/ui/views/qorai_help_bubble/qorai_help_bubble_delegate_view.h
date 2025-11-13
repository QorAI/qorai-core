// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_HELP_BUBBLE_QORAI_HELP_BUBBLE_DELEGATE_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_HELP_BUBBLE_QORAI_HELP_BUBBLE_DELEGATE_VIEW_H_

#include <memory>
#include <string>

#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/bubble/bubble_dialog_delegate_view.h"

class QoraiHelpBubbleDelegateView : public views::BubbleDialogDelegateView {
  METADATA_HEADER(QoraiHelpBubbleDelegateView, views::BubbleDialogDelegateView)
 public:

  explicit QoraiHelpBubbleDelegateView(View* anchor_view,
                                       const std::string& text);
  QoraiHelpBubbleDelegateView(const QoraiHelpBubbleDelegateView&) = delete;
  QoraiHelpBubbleDelegateView& operator=(const QoraiHelpBubbleDelegateView&) =
      delete;
  ~QoraiHelpBubbleDelegateView() override;

 private:
  // views::BubbleDialogDelegate
  std::unique_ptr<views::NonClientFrameView> CreateFrameView(
      views::Widget* widget) override;

  void SetUpLabel(views::Label* label,
                  const std::u16string& text,
                  int font_size,
                  gfx::Font::Weight font_weight);
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_HELP_BUBBLE_QORAI_HELP_BUBBLE_DELEGATE_VIEW_H_
