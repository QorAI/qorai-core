/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_INFOBARS_CORE_QORAI_CONFIRM_INFOBAR_DELEGATE_H_
#define QORAI_COMPONENTS_INFOBARS_CORE_QORAI_CONFIRM_INFOBAR_DELEGATE_H_

#include <cstddef>
#include <string>
#include <vector>

#include "components/infobars/core/confirm_infobar_delegate.h"

class QoraiConfirmInfoBarDelegate : public ConfirmInfoBarDelegate {
 public:
  QoraiConfirmInfoBarDelegate(const QoraiConfirmInfoBarDelegate&) = delete;
  QoraiConfirmInfoBarDelegate& operator=(const QoraiConfirmInfoBarDelegate&) =
      delete;
  ~QoraiConfirmInfoBarDelegate() override;

  virtual bool HasCheckbox() const;
  virtual std::u16string GetCheckboxText() const;
  virtual void SetCheckboxChecked(bool checked);
  // Returns true when delegate wants to intercept closing.
  // Then closing will be cancelled and delegate should remove infobar
  // after doing something.
  virtual bool InterceptClosing();
  virtual std::vector<int> GetButtonsOrder() const;
  virtual bool IsProminent(int id) const;
  virtual bool ExtraButtonPressed();
  virtual bool ShouldSupportMultiLine() const;
  virtual size_t GetMaxLines() const;

  int GetButtons() const override;

 protected:
  QoraiConfirmInfoBarDelegate();
};

#endif  // QORAI_COMPONENTS_INFOBARS_CORE_QORAI_CONFIRM_INFOBAR_DELEGATE_H_
