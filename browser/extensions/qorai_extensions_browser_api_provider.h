/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSIONS_BROWSER_API_PROVIDER_H_
#define QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSIONS_BROWSER_API_PROVIDER_H_

#include "extensions/browser/extensions_browser_api_provider.h"

namespace extensions {

class QoraiExtensionsBrowserAPIProvider : public ExtensionsBrowserAPIProvider {
 public:
  QoraiExtensionsBrowserAPIProvider();
  QoraiExtensionsBrowserAPIProvider(const QoraiExtensionsBrowserAPIProvider&) =
      delete;
  QoraiExtensionsBrowserAPIProvider& operator=(
      const QoraiExtensionsBrowserAPIProvider&) = delete;
  ~QoraiExtensionsBrowserAPIProvider() override;

  void RegisterExtensionFunctions(ExtensionFunctionRegistry* registry) override;
};

}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSIONS_BROWSER_API_PROVIDER_H_
