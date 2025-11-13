/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_UNAUTHORIZED_BUNDLE_IMPL_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_UNAUTHORIZED_BUNDLE_IMPL_H_

#include <array>
#include <memory>

#include "base/types/pass_key.h"
#include "qorai/components/qorai_wallet/browser/zcash/rust/lib.rs.h"
#include "qorai/components/qorai_wallet/browser/zcash/rust/orchard_unauthorized_bundle.h"
#include "third_party/rust/cxx/v1/cxx.h"

namespace qorai_wallet::orchard {

class OrchardUnauthorizedBundleImpl : public OrchardUnauthorizedBundle {
 public:
  OrchardUnauthorizedBundleImpl(base::PassKey<class OrchardUnauthorizedBundle>,
                                ::rust::Box<CxxOrchardUnauthorizedBundle>);
  ~OrchardUnauthorizedBundleImpl() override;

  std::array<uint8_t, kZCashDigestSize> GetDigest() override;
  std::unique_ptr<OrchardAuthorizedBundle> Complete(
      const std::array<uint8_t, kZCashDigestSize>& sighash) override;

 private:
  ::rust::Box<CxxOrchardUnauthorizedBundle> cxx_orchard_unauthorized_bundle_;
};

}  // namespace qorai_wallet::orchard

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_UNAUTHORIZED_BUNDLE_IMPL_H_
