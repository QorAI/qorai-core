/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_INFOBARS_QORAI_CONFIRM_INFOBAR_H_
#define QORAI_BROWSER_UI_VIEWS_INFOBARS_QORAI_CONFIRM_INFOBAR_H_

#include <memory>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "qorai/components/infobars/core/qorai_confirm_infobar_delegate.h"
#include "chrome/browser/ui/views/infobars/infobar_view.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/button/image_button.h"

namespace views {
class Checkbox;
class Label;
class MdTextButton;
}  // namespace views

// An infobar that shows a message, up to two optional buttons, and an optional,
// right-aligned link.  This is commonly used to do things like:
// "Would you like to do X?  [Yes]  [No]  [<custom button>]    _Learn More_ [x]"
class QoraiConfirmInfoBar : public InfoBarView {
  METADATA_HEADER(QoraiConfirmInfoBar, InfoBarView)
 public:
  explicit QoraiConfirmInfoBar(
      std::unique_ptr<QoraiConfirmInfoBarDelegate> delegate);

  QoraiConfirmInfoBar(const QoraiConfirmInfoBar&) = delete;
  QoraiConfirmInfoBar& operator=(const QoraiConfirmInfoBar&) = delete;

  ~QoraiConfirmInfoBar() override;

  // InfoBarView:
  void Layout(PassKey) override;

  QoraiConfirmInfoBarDelegate* GetDelegate();
  const QoraiConfirmInfoBarDelegate* GetDelegate() const;

 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiConfirmInfoBarTest, CloseButtonOrderTest);

  // InfoBarView:
  int GetContentMinimumWidth() const override;

  void MaybeLayoutMultiLineLabelAndLink();

  void OkButtonPressed();
  void CancelButtonPressed();
  void ExtraButtonPressed();
  void CloseButtonPressed() override;
  void CheckboxPressed();

  views::MdTextButton* GetButtonById(int id);

  // Returns the width of all content other than the label and link.  Layout()
  // uses this to determine how much space the label and link can take.
  int NonLabelWidth() const;

  views::View* close_button_for_testing() const { return close_button_.get(); }

  raw_ptr<views::Label> label_ = nullptr;
  raw_ptr<views::MdTextButton> ok_button_ = nullptr;
  raw_ptr<views::MdTextButton> cancel_button_ = nullptr;
  raw_ptr<views::MdTextButton> extra_button_ = nullptr;
  raw_ptr<views::Link> link_ = nullptr;
  raw_ptr<views::Checkbox> checkbox_ = nullptr;

  base::WeakPtrFactory<QoraiConfirmInfoBar> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_INFOBARS_QORAI_CONFIRM_INFOBAR_H_
