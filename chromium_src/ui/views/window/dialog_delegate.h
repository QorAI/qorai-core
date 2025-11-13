// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_UI_VIEWS_WINDOW_DIALOG_DELEGATE_H_
#define QORAI_CHROMIUM_SRC_UI_VIEWS_WINDOW_DIALOG_DELEGATE_H_

#include "ui/views/widget/widget_delegate.h"

#define ResetViewShownTimeStampForTesting                                 \
  set_should_ignore_snapping(bool should_ignore_snapping) {               \
    should_ignore_snapping_ = should_ignore_snapping;                     \
  }                                                                       \
  bool should_ignore_snapping() const { return should_ignore_snapping_; } \
                                                                          \
 private:                                                                 \
  bool should_ignore_snapping_ = false;                                   \
                                                                          \
 public:                                                                  \
  void ResetViewShownTimeStampForTesting

class QoraiFirstRunDialog;
class CrashReportPermissionAskDialogView;
class WindowClosingConfirmDialogView;
class PlaylistActionDialog;
class TextRecognitionDialogView;
class ObsoleteSystemConfirmDialogView;

namespace qorai_vpn {
class QoraiVpnFallbackDialogView;
class QoraiVpnDnsSettingsNotificiationDialogView;
}  // namespace qorai_vpn

#define CreatePassKey                                                 \
  CreatePassKey_Unused();                                             \
  friend class ::QoraiFirstRunDialog;                                 \
  friend class ::CrashReportPermissionAskDialogView;                  \
  friend class ::WindowClosingConfirmDialogView;                      \
  friend class ::PlaylistActionDialog;                                \
  friend class ::TextRecognitionDialogView;                           \
  friend class ::ObsoleteSystemConfirmDialogView;                     \
  friend class qorai_vpn::QoraiVpnFallbackDialogView;                 \
  friend class qorai_vpn::QoraiVpnDnsSettingsNotificiationDialogView; \
  static DdvPassKey CreatePassKey

#include <ui/views/window/dialog_delegate.h>  // IWYU pragma: export

#undef CreatePassKey
#undef ResetViewShownTimeStampForTesting

#endif  // QORAI_CHROMIUM_SRC_UI_VIEWS_WINDOW_DIALOG_DELEGATE_H_
