/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_API_QORAI_THEME_API_H_
#define QORAI_BROWSER_EXTENSIONS_API_QORAI_THEME_API_H_

#include "extensions/browser/extension_function.h"

namespace extensions {
namespace api {

class QoraiThemeSetQoraiThemeTypeFunction : public ExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("qoraiTheme.setQoraiThemeType", UNKNOWN)

 protected:
  ~QoraiThemeSetQoraiThemeTypeFunction() override {}

  ResponseAction Run() override;
};

}  // namespace api
}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_API_QORAI_THEME_API_H_
