/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_HISTORY_QUICK_PROVIDER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_HISTORY_QUICK_PROVIDER_H_

#define DoAutocomplete                    \
  DoAutocompleteUnused();                 \
  friend class QoraiHistoryQuickProvider; \
  void DoAutocomplete

#include <components/omnibox/browser/history_quick_provider.h>  // IWYU pragma: export

#undef DoAutocomplete

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_HISTORY_QUICK_PROVIDER_H_
