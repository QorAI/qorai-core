/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_FIRST_RUN_DIALOG_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_FIRST_RUN_DIALOG_H_

#include "base/functional/callback.h"
#include "base/memory/raw_ptr.h"
#include "qorai/browser/shell_integrations/buildflags/buildflags.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/window/dialog_delegate.h"

namespace views {
class Checkbox;
}  // namespace views

class QoraiFirstRunDialog : public views::DialogDelegateView {
  METADATA_HEADER(QoraiFirstRunDialog, views::DialogDelegateView)
 public:

  QoraiFirstRunDialog(const QoraiFirstRunDialog&) = delete;
  QoraiFirstRunDialog& operator=(const QoraiFirstRunDialog&) = delete;

  static void Show(base::RepeatingClosure quit_runloop);

 private:
  explicit QoraiFirstRunDialog(base::RepeatingClosure quit_runloop);
  ~QoraiFirstRunDialog() override;

  // This terminates the nested message-loop.
  void Done();

  // views::DialogDelegate overrides:
  bool Accept() override;

  // views::WidgetDelegate overrides:
  void WindowClosing() override;

  base::RepeatingClosure quit_runloop_;

#if BUILDFLAG(ENABLE_PIN_SHORTCUT)
  raw_ptr<views::Checkbox> pin_shortcut_checkbox_ = nullptr;
#endif
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_FIRST_RUN_DIALOG_H_
