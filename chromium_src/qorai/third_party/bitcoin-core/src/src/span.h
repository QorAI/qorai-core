/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_QORAI_THIRD_PARTY_BITCOIN_CORE_SRC_SRC_SPAN_H_
#define QORAI_CHROMIUM_SRC_QORAI_THIRD_PARTY_BITCOIN_CORE_SRC_SRC_SPAN_H_

// clang-format off
#include <utility>

// Allows passing lint check:
// "Includes STL header(s) but does not reference std::.".
namespace std::qorai {
template <typename T1, typename T2>
using pair = ::std::pair<T1, T2>;
}

#include <qorai/third_party/bitcoin-core/src/src/span.h> // IWYU pragma: export
// clang-format on

#endif  // QORAI_CHROMIUM_SRC_QORAI_THIRD_PARTY_BITCOIN_CORE_SRC_SRC_SPAN_H_
