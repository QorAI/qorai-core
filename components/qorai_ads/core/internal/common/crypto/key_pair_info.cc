/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/crypto/key_pair_info.h"

namespace qorai_ads::crypto {

KeyPairInfo::KeyPairInfo() = default;

KeyPairInfo::KeyPairInfo(const KeyPairInfo& other) = default;

KeyPairInfo& KeyPairInfo::operator=(const KeyPairInfo& other) = default;

KeyPairInfo::KeyPairInfo(KeyPairInfo&& other) noexcept = default;

KeyPairInfo& KeyPairInfo::operator=(KeyPairInfo&& other) noexcept = default;

KeyPairInfo::~KeyPairInfo() = default;

bool KeyPairInfo::IsValid() const {
  return !public_key.empty() && !secret_key.empty();
}

}  // namespace qorai_ads::crypto
