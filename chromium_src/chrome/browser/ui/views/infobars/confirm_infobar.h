/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_INFOBARS_CONFIRM_INFOBAR_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_INFOBARS_CONFIRM_INFOBAR_H_

#define target_height_for_testing              \
  Unused() {                                   \
    return 0;                                  \
  }                                            \
  friend class QoraiSyncAccountDeletedInfoBar; \
  friend class QoraiConfirmInfoBar;            \
  int target_height_for_testing

#define NonLabelWidth virtual NonLabelWidth

#include <chrome/browser/ui/views/infobars/confirm_infobar.h>  // IWYU pragma: export

#undef NonLabelWidth
#undef target_height_for_testing

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_INFOBARS_CONFIRM_INFOBAR_H_
