// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_wallet/browser/zcash/rust/orchard_authorized_bundle_impl.h"

#include <utility>

namespace qorai_wallet::orchard {

OrchardAuthorizedBundleImpl::OrchardAuthorizedBundleImpl(
    base::PassKey<class OrchardUnauthorizedBundleImpl>,
    ::rust::Box<CxxOrchardAuthorizedBundle> cxx_orchard_authorized_bundle)
    : cxx_orchard_authorized_bundle_(std::move(cxx_orchard_authorized_bundle)) {
}

OrchardAuthorizedBundleImpl::~OrchardAuthorizedBundleImpl() = default;

std::vector<uint8_t> OrchardAuthorizedBundleImpl::GetOrchardRawTxPart() {
  auto data = cxx_orchard_authorized_bundle_->raw_tx();
  return std::vector<uint8_t>(data.begin(), data.end());
}

}  // namespace qorai_wallet::orchard
