// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_WEB_QORAI_WEB_MAIN_PARTS_H_
#define QORAI_IOS_BROWSER_WEB_QORAI_WEB_MAIN_PARTS_H_

#include "ios/chrome/browser/web/model/chrome_main_parts.h"

class QoraiWebMainParts : public IOSChromeMainParts {
 public:
  explicit QoraiWebMainParts(const base::CommandLine& parsed_command_line);
  QoraiWebMainParts(const QoraiWebMainParts&) = delete;
  QoraiWebMainParts& operator=(const QoraiWebMainParts&) = delete;
  ~QoraiWebMainParts() override;

 private:
  // web::WebMainParts implementation.
  void PreCreateMainMessageLoop() override;
  void PreMainMessageLoopRun() override;
};

#endif  // QORAI_IOS_BROWSER_WEB_QORAI_WEB_MAIN_PARTS_H_
