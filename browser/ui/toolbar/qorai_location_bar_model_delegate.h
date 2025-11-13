/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TOOLBAR_QORAI_LOCATION_BAR_MODEL_DELEGATE_H_
#define QORAI_BROWSER_UI_TOOLBAR_QORAI_LOCATION_BAR_MODEL_DELEGATE_H_

#include "base/compiler_specific.h"
#include "chrome/browser/ui/browser_location_bar_model_delegate.h"

class TabStripModel;

class QoraiLocationBarModelDelegate : public BrowserLocationBarModelDelegate {
 public:
  explicit QoraiLocationBarModelDelegate(TabStripModel* tab_strip_model);
  QoraiLocationBarModelDelegate(const QoraiLocationBarModelDelegate&) = delete;
  QoraiLocationBarModelDelegate& operator=(
      const QoraiLocationBarModelDelegate&) = delete;
  ~QoraiLocationBarModelDelegate() override;
  static void FormattedStringFromURL(const GURL& url,
                                     std::u16string* new_formatted_url);

 private:
  std::u16string FormattedStringWithEquivalentMeaning(
      const GURL& url,
      const std::u16string& formatted_url) const override;
  bool GetURL(GURL* url) const override;

  const raw_ptr<TabStripModel> tab_strip_model_;
};

#endif  // QORAI_BROWSER_UI_TOOLBAR_QORAI_LOCATION_BAR_MODEL_DELEGATE_H_
