/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_WIN_H_
#define QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_WIN_H_

#include "base/callback_list.h"
#include "base/win/windows_types.h"
#include "qorai/components/qorai_ads/browser/application_state/background_helper.h"

namespace qorai_ads {

class BackgroundHelperWin final : public BackgroundHelper {
 public:
  BackgroundHelperWin(const BackgroundHelperWin&) = delete;
  BackgroundHelperWin& operator=(const BackgroundHelperWin&) = delete;

  ~BackgroundHelperWin() override;

 protected:
  friend class BackgroundHelperHolder;

  BackgroundHelperWin();

 private:
  void OnWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

  // BackgroundHelper:
  bool IsForeground() const override;

  base::CallbackListSubscription hwnd_subscription_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_QORAI_ADS_APPLICATION_STATE_BACKGROUND_HELPER_BACKGROUND_HELPER_WIN_H_
