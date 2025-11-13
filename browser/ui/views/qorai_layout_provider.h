/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_LAYOUT_PROVIDER_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_LAYOUT_PROVIDER_H_

#include "chrome/browser/ui/views/chrome_layout_provider.h"

class QoraiLayoutProvider : public ChromeLayoutProvider {
 public:
  QoraiLayoutProvider() = default;
  QoraiLayoutProvider(const QoraiLayoutProvider&) = delete;
  QoraiLayoutProvider& operator=(const QoraiLayoutProvider&) = delete;
  ~QoraiLayoutProvider() override = default;

  int GetCornerRadiusMetric(views::Emphasis emphasis,
                            const gfx::Size& size = gfx::Size()) const override;
  int GetDistanceMetric(int metric) const override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_LAYOUT_PROVIDER_H_
