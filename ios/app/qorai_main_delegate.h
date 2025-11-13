/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_APP_QORAI_MAIN_DELEGATE_H_
#define QORAI_IOS_APP_QORAI_MAIN_DELEGATE_H_

#include <string>

#include "ios/chrome/app/startup/ios_chrome_main_delegate.h"

class QoraiWebClient;

class QoraiMainDelegate : public IOSChromeMainDelegate {
 public:
  QoraiMainDelegate();
  QoraiMainDelegate(const QoraiMainDelegate&) = delete;
  QoraiMainDelegate& operator=(const QoraiMainDelegate&) = delete;
  ~QoraiMainDelegate() override;

 protected:
  // web::WebMainDelegate implementation:
  void BasicStartupComplete() override;

 private:
};

#endif  // QORAI_IOS_APP_QORAI_MAIN_DELEGATE_H_
