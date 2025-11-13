// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_AUTOCOMPLETE_PROVIDER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_AUTOCOMPLETE_PROVIDER_H_

// Note: We go negative with the QoraiAutoCompleteTypes, so we don't conflict if
// Chromium adds something new.
#define TYPE_BOOKMARK \
  TYPE_QORAI_COMMANDER = -1 << 0, TYPE_QORAI_QORA = -1 << 1, TYPE_BOOKMARK
#include <components/omnibox/browser/autocomplete_provider.h>  // IWYU pragma: export
#undef TYPE_BOOKMARK

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_AUTOCOMPLETE_PROVIDER_H_
