/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSION_PROVIDER_H_
#define QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSION_PROVIDER_H_

#include <string>

#include "extensions/browser/management_policy.h"

namespace extensions {

class QoraiExtensionProvider : public ManagementPolicy::Provider {
 public:
  QoraiExtensionProvider();
  QoraiExtensionProvider(const QoraiExtensionProvider&) = delete;
  QoraiExtensionProvider& operator=(const QoraiExtensionProvider&) = delete;
  ~QoraiExtensionProvider() override;
  std::string GetDebugPolicyProviderName() const override;
  bool MustRemainInstalled(const Extension* extension,
                           std::u16string* error) const override;
};

}  // namespace extensions

#endif  // QORAI_BROWSER_EXTENSIONS_QORAI_EXTENSION_PROVIDER_H_
