/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_PAGE_INFO_PAGE_INFO_DELEGATE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_PAGE_INFO_PAGE_INFO_DELEGATE_H_

#define IsContentDisplayedInVrHeadset                      \
  QoraiShouldShowPermission(ContentSettingsType type) = 0; \
  virtual bool IsContentDisplayedInVrHeadset

#include <components/page_info/page_info_delegate.h>  // IWYU pragma: export
#undef IsContentDisplayedInVrHeadset

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_PAGE_INFO_PAGE_INFO_DELEGATE_H_
