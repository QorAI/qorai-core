/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/extensions/qorai_extensions_browser_api_provider.h"

#include "qorai/browser/extensions/api/generated_api_registration.h"
#include "extensions/browser/extension_function_registry.h"

namespace extensions {

QoraiExtensionsBrowserAPIProvider::QoraiExtensionsBrowserAPIProvider() =
    default;
QoraiExtensionsBrowserAPIProvider::~QoraiExtensionsBrowserAPIProvider() =
    default;

void QoraiExtensionsBrowserAPIProvider::RegisterExtensionFunctions(
    ExtensionFunctionRegistry* registry) {
  // Generated APIs from Qorai.
  api::QoraiGeneratedFunctionRegistry::RegisterAll(registry);
}

}  // namespace extensions
