/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSIONS_BROWSER_CLIENT_IMPL_H_
#define QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSIONS_BROWSER_CLIENT_IMPL_H_

#include "chrome/browser/extensions/chrome_extensions_browser_client.h"

namespace extensions {

class QoraiExtensionsBrowserClientImpl : public ChromeExtensionsBrowserClient {
 public:
  QoraiExtensionsBrowserClientImpl();
  QoraiExtensionsBrowserClientImpl(const QoraiExtensionsBrowserClientImpl&) =
      delete;
  QoraiExtensionsBrowserClientImpl& operator=(
      const QoraiExtensionsBrowserClientImpl&) = delete;
  ~QoraiExtensionsBrowserClientImpl() override = default;

  void Init() override;
};

}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSIONS_BROWSER_CLIENT_IMPL_H_
