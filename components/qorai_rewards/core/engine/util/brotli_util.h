/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_BROTLI_UTIL_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_BROTLI_UTIL_H_

#include <string>
#include <string_view>

namespace qorai_rewards::internal {
namespace util {

bool DecodeBrotliString(std::string_view input,
                        size_t uncompressed_size,
                        std::string* output);

bool DecodeBrotliStringWithBuffer(std::string_view input,
                                  size_t buffer_size,
                                  std::string* output);

}  // namespace util
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_BROTLI_UTIL_H_
