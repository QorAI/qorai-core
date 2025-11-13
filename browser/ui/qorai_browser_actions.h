/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_BROWSER_ACTIONS_H_
#define QORAI_BROWSER_UI_QORAI_BROWSER_ACTIONS_H_

#include "chrome/browser/ui/browser_actions.h"

// Add more side panel actions for our playlist/chat panels.
class QoraiBrowserActions : public BrowserActions {
 public:
  explicit QoraiBrowserActions(BrowserWindowInterface* bwi);
  ~QoraiBrowserActions() override;

 private:
  void InitializeBrowserActions() override;
};

#endif  // QORAI_BROWSER_UI_QORAI_BROWSER_ACTIONS_H_
