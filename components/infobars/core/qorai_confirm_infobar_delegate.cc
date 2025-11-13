/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/infobars/core/qorai_confirm_infobar_delegate.h"

QoraiConfirmInfoBarDelegate::QoraiConfirmInfoBarDelegate() = default;
QoraiConfirmInfoBarDelegate::~QoraiConfirmInfoBarDelegate() = default;

int QoraiConfirmInfoBarDelegate::GetButtons() const {
#if !BUILDFLAG(IS_IOS) && !BUILDFLAG(IS_ANDROID)
  return BUTTON_OK | BUTTON_CANCEL | BUTTON_EXTRA;
#else
  return BUTTON_OK | BUTTON_CANCEL;
#endif
}

std::vector<int> QoraiConfirmInfoBarDelegate::GetButtonsOrder() const {
#if !BUILDFLAG(IS_IOS) && !BUILDFLAG(IS_ANDROID)
  return {BUTTON_OK, BUTTON_EXTRA, BUTTON_CANCEL};
#else
  return {BUTTON_OK, BUTTON_CANCEL};
#endif
}

bool QoraiConfirmInfoBarDelegate::IsProminent(int id) const {
  return id == BUTTON_OK;
}

bool QoraiConfirmInfoBarDelegate::HasCheckbox() const {
  return false;
}

std::u16string QoraiConfirmInfoBarDelegate::GetCheckboxText() const {
  return std::u16string();
}

void QoraiConfirmInfoBarDelegate::SetCheckboxChecked(bool checked) {}

bool QoraiConfirmInfoBarDelegate::InterceptClosing() {
  return false;
}

bool QoraiConfirmInfoBarDelegate::ExtraButtonPressed() {
  return true;
}

bool QoraiConfirmInfoBarDelegate::ShouldSupportMultiLine() const {
  return false;
}

size_t QoraiConfirmInfoBarDelegate::GetMaxLines() const {
  // Return 0 to indicate that there is no limit on the number of lines.
  return 0;
}
