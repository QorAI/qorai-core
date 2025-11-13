/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_INFOBARS_INFOBAR_CONTAINER_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_INFOBARS_INFOBAR_CONTAINER_VIEW_H_

#include "components/infobars/core/infobar_container.h"

#define PlatformSpecificRemoveInfoBar       \
  PlatformSpecificRemoveInfoBar_UnUsed() {} \
  friend class QoraiInfoBarContainerView;   \
  void PlatformSpecificRemoveInfoBar

#include <chrome/browser/ui/views/infobars/infobar_container_view.h>  // IWYU pragma: export

#undef PlatformSpecificRemoveInfoBar

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_INFOBARS_INFOBAR_CONTAINER_VIEW_H_
