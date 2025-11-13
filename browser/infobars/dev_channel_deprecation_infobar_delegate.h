/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_INFOBARS_DEV_CHANNEL_DEPRECATION_INFOBAR_DELEGATE_H_
#define QORAI_BROWSER_INFOBARS_DEV_CHANNEL_DEPRECATION_INFOBAR_DELEGATE_H_

#include <vector>

#include "qorai/components/infobars/core/qorai_confirm_infobar_delegate.h"

class DevChannelDeprecationInfoBarDelegate
    : public QoraiConfirmInfoBarDelegate {
 public:
  static void CreateIfNeeded(infobars::InfoBarManager* infobar_manager);

  DevChannelDeprecationInfoBarDelegate(
      const DevChannelDeprecationInfoBarDelegate&) = delete;
  DevChannelDeprecationInfoBarDelegate& operator=(
      const DevChannelDeprecationInfoBarDelegate&) = delete;

  ~DevChannelDeprecationInfoBarDelegate() override;

 private:
  DevChannelDeprecationInfoBarDelegate();

  // QoraiConfirmInfoBarDelegate overrides:
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  std::u16string GetMessageText() const override;
  int GetButtons() const override;
  std::vector<int> GetButtonsOrder() const override;
  bool ShouldExpire(const NavigationDetails& details) const override;
  std::u16string GetLinkText() const override;
  GURL GetLinkURL() const override;
};

#endif  // QORAI_BROWSER_INFOBARS_DEV_CHANNEL_DEPRECATION_INFOBAR_DELEGATE_H_
