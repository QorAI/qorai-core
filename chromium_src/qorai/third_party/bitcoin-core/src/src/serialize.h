/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_QORAI_THIRD_PARTY_BITCOIN_CORE_SRC_SRC_SERIALIZE_H_
#define QORAI_CHROMIUM_SRC_QORAI_THIRD_PARTY_BITCOIN_CORE_SRC_SRC_SERIALIZE_H_

#include <ios>
#include <streambuf>
#include <string>
#include <vector>

#include "base/check.h"

namespace std::qorai {
using string = ::std::string;
}

#define throw CHECK(false) <<
#define ios_base qorai
#define failure string
#include <qorai/third_party/bitcoin-core/src/src/serialize.h>  // IWYU pragma: export
#undef throw
#undef ios_base
#undef failure

#endif  // QORAI_CHROMIUM_SRC_QORAI_THIRD_PARTY_BITCOIN_CORE_SRC_SRC_SERIALIZE_H_
