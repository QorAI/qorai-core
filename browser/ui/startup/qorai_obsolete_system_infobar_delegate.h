/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_STARTUP_QORAI_OBSOLETE_SYSTEM_INFOBAR_DELEGATE_H_
#define QORAI_BROWSER_UI_STARTUP_QORAI_OBSOLETE_SYSTEM_INFOBAR_DELEGATE_H_

#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "qorai/components/infobars/core/qorai_confirm_infobar_delegate.h"

namespace infobars {
class ContentInfoBarManager;
}  // namespace infobars

class QoraiObsoleteSystemInfoBarDelegate : public QoraiConfirmInfoBarDelegate {
 public:
  static void Create(infobars::ContentInfoBarManager* infobar_manager);

  QoraiObsoleteSystemInfoBarDelegate(
      const QoraiObsoleteSystemInfoBarDelegate&) = delete;
  QoraiObsoleteSystemInfoBarDelegate& operator=(
      const QoraiObsoleteSystemInfoBarDelegate&) = delete;

 private:
  QoraiObsoleteSystemInfoBarDelegate();
  ~QoraiObsoleteSystemInfoBarDelegate() override;

  // QoraiConfirmInfoBarDelegate overrides:
  bool HasCheckbox() const override;
  std::u16string GetCheckboxText() const override;
  void SetCheckboxChecked(bool checked) override;
  bool InterceptClosing() override;
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  std::u16string GetLinkText() const override;
  GURL GetLinkURL() const override;
  std::u16string GetMessageText() const override;
  int GetButtons() const override;
  std::vector<int> GetButtonsOrder() const override;
  bool ShouldExpire(const NavigationDetails& details) const override;

  void OnConfirmDialogClosing(bool suppress);

  bool launch_confirmation_dialog_ = false;

  base::WeakPtrFactory<QoraiObsoleteSystemInfoBarDelegate> weak_factory_{this};
};

#endif  // QORAI_BROWSER_UI_STARTUP_QORAI_OBSOLETE_SYSTEM_INFOBAR_DELEGATE_H_
