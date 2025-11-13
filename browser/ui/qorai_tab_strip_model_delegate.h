/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_TAB_STRIP_MODEL_DELEGATE_H_
#define QORAI_BROWSER_UI_QORAI_TAB_STRIP_MODEL_DELEGATE_H_

#include <memory>
#include <vector>

#include "chrome/browser/ui/browser_tab_strip_model_delegate.h"

// In order to make it easy to replace BrowserTabStripModelDelegate with our
// QoraiTabStripModelDelegate, wrap this class with chrome namespace.
namespace chrome {

class QoraiTabStripModelDelegate : public BrowserTabStripModelDelegate {
 public:
  using BrowserTabStripModelDelegate::BrowserTabStripModelDelegate;
  QoraiTabStripModelDelegate(const QoraiTabStripModelDelegate&) = delete;
  QoraiTabStripModelDelegate& operator=(const QoraiTabStripModelDelegate&) =
      delete;
  ~QoraiTabStripModelDelegate() override = default;

  // BrowserTabStripModelDelegate:
  bool CanMoveTabsToWindow(const std::vector<int>& indices) override;
};

}  // namespace chrome

#endif  // QORAI_BROWSER_UI_QORAI_TAB_STRIP_MODEL_DELEGATE_H_
