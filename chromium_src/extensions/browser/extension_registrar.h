// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_REGISTRAR_H_
#define QORAI_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_REGISTRAR_H_

#define AddComponentExtension                        \
  AddComponentExtension(const Extension* extension); \
  void AddComponentExtension_ChromiumImpl

#include <extensions/browser/extension_registrar.h>  // IWYU pragma: export

#undef AddComponentExtension

#endif  // QORAI_CHROMIUM_SRC_EXTENSIONS_BROWSER_EXTENSION_REGISTRAR_H_
