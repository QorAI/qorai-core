/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_AUTOFILL_CHROME_AUTOFILL_CLIENT_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_AUTOFILL_CHROME_AUTOFILL_CLIENT_H_

#include "components/autofill/content/browser/content_autofill_client.h"

// Note, the _Unused methods below can retain "final" because the base class
// override for components/autofill/content/browser/content_autofill_client.h
// declares them specifically for this purpose.

#define GetAutofillOptimizationGuideDecider             \
  GetAutofillOptimizationGuideDecider() const override; \
  AutofillOptimizationGuideDecider* GetAutofillOptimizationGuideDecider_Unused

#define IsAutofillEnabled             \
  IsAutofillEnabled() const override; \
  bool IsAutofillEnabled_Unused

#define IsAutocompleteEnabled             \
  IsAutocompleteEnabled() const override; \
  bool IsAutocompleteEnabled_Unused

#include <chrome/browser/ui/autofill/chrome_autofill_client.h>  // IWYU pragma: export
#undef IsAutocompleteEnabled
#undef IsAutofillEnabled
#undef GetAutofillOptimizationGuideDecider

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_AUTOFILL_CHROME_AUTOFILL_CLIENT_H_
