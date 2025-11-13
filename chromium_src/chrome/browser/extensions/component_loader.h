/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_

#define AddDefaultComponentExtensions virtual AddDefaultComponentExtensions
#define AddNetworkSpeechSynthesisExtension    \
  AddNetworkSpeechSynthesisExtensionUnused(); \
  friend class QoraiComponentLoader;          \
  void AddNetworkSpeechSynthesisExtension

#include <chrome/browser/extensions/component_loader.h>  // IWYU pragma: export
#undef AddDefaultComponentExtensions
#undef AddNetworkSpeechSynthesisExtension

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_
