// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_UI_VIEWS_WINDOW_DIALOG_CLIENT_VIEW_H_
#define QORAI_CHROMIUM_SRC_UI_VIEWS_WINDOW_DIALOG_CLIENT_VIEW_H_

class WebDiscoveryDialogClientView;

#define SetupLayout                              \
  SetupLayout_UnUsed() {}                        \
  friend class ::WebDiscoveryDialogClientView;   \
  void SetupButtonsLayoutVertically();           \
                                                 \
 public:                                         \
  void IgnoreNextWindowStationaryStateChanged(); \
                                                 \
 private:                                        \
  virtual void SetupLayout

#include <ui/views/window/dialog_client_view.h>  // IWYU pragma: export

#undef SetupLayout

#endif  // QORAI_CHROMIUM_SRC_UI_VIEWS_WINDOW_DIALOG_CLIENT_VIEW_H_
