/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_INFOBARS_QORAI_CONFIRM_INFOBAR_CREATOR_H_
#define QORAI_BROWSER_INFOBARS_QORAI_CONFIRM_INFOBAR_CREATOR_H_

#include <memory>

class QoraiConfirmInfoBarDelegate;

namespace infobars {
class InfoBar;
}  // namespace infobars

std::unique_ptr<infobars::InfoBar> CreateQoraiConfirmInfoBar(
    std::unique_ptr<QoraiConfirmInfoBarDelegate> delegate);

#endif  // QORAI_BROWSER_INFOBARS_QORAI_CONFIRM_INFOBAR_CREATOR_H_
