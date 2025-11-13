/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_THEMES_QORAI_PRIVATE_WINDOW_THEME_SUPPLIER_H_
#define QORAI_BROWSER_THEMES_QORAI_PRIVATE_WINDOW_THEME_SUPPLIER_H_

#include "chrome/browser/themes/custom_theme_supplier.h"

// A theme supplier for private (or tor) window.
class QoraiPrivateWindowThemeSupplier : public CustomThemeSupplier {
 public:
  explicit QoraiPrivateWindowThemeSupplier(bool private_window);

  QoraiPrivateWindowThemeSupplier(const QoraiPrivateWindowThemeSupplier&) =
      delete;
  QoraiPrivateWindowThemeSupplier& operator=(
      const QoraiPrivateWindowThemeSupplier&) = delete;

 protected:
  ~QoraiPrivateWindowThemeSupplier() override;

  void AddColorMixers(ui::ColorProvider* provider,
                      const ui::ColorProviderKey& key) const override;

  // false if this is for tor window.
  bool for_private_window_ = true;
};

#endif  // QORAI_BROWSER_THEMES_QORAI_PRIVATE_WINDOW_THEME_SUPPLIER_H_
