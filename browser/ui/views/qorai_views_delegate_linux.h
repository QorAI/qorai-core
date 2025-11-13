/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_VIEWS_DELEGATE_LINUX_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_VIEWS_DELEGATE_LINUX_H_

#include "chrome/browser/ui/views/chrome_views_delegate.h"

class QoraiViewsDelegateLinux : public ChromeViewsDelegate {
 public:
  QoraiViewsDelegateLinux() = default;
  QoraiViewsDelegateLinux(const QoraiViewsDelegateLinux&) = delete;
  QoraiViewsDelegateLinux& operator=(const QoraiViewsDelegateLinux&) = delete;
  ~QoraiViewsDelegateLinux() override = default;
 private:
  // ChromeViewsDelegate overrides:
  gfx::ImageSkia* GetDefaultWindowIcon() const override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_VIEWS_DELEGATE_LINUX_H_
