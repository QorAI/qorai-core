/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_VARIATIONS_VARIATIONS_IDS_PROVIDER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_VARIATIONS_VARIATIONS_IDS_PROVIDER_H_

#define GetClientDataHeaders                                  \
  GetClientDataHeaders(bool is_signed_in) { return nullptr; } \
  variations::mojom::VariationsHeadersPtr GetClientDataHeaders_Chromium

#include <components/variations/variations_ids_provider.h>  // IWYU pragma: export
#undef GetClientDataHeaders

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_VARIATIONS_VARIATIONS_IDS_PROVIDER_H_
