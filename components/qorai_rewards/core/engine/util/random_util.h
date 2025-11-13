/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_RANDOM_UTIL_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_RANDOM_UTIL_H_

#include <stdint.h>

#include <string>

namespace qorai_rewards::internal {
namespace util {

// Generates a random 32-byte hex string.
std::string GenerateRandomHexString();

// Generates a PKCE-compatible code verifier.
std::string GeneratePKCECodeVerifier();

// Generates a PKCE-compatible code challenge based on |code_verifier|.
std::string GeneratePKCECodeChallenge(const std::string& code_verifier);

}  // namespace util
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UTIL_RANDOM_UTIL_H_
