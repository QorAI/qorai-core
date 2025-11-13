/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_BROWSER_MAIN_EXTRA_PARTS_P3A_H_
#define QORAI_BROWSER_QORAI_BROWSER_MAIN_EXTRA_PARTS_P3A_H_

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chrome_browser_main.h"
#include "chrome/browser/chrome_browser_main_extra_parts.h"

class QoraiBrowserMainExtraPartsP3A : public ChromeBrowserMainExtraParts {
 public:
  QoraiBrowserMainExtraPartsP3A();
  ~QoraiBrowserMainExtraPartsP3A() override;

  QoraiBrowserMainExtraPartsP3A(const QoraiBrowserMainExtraPartsP3A&) = delete;
  QoraiBrowserMainExtraPartsP3A& operator=(
      const QoraiBrowserMainExtraPartsP3A&) = delete;

  // ChromeBrowserMainExtraParts override:
  void PostBrowserStart() override;
};

#endif  // QORAI_BROWSER_QORAI_BROWSER_MAIN_EXTRA_PARTS_P3A_H_
