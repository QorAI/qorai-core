// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_AUTHORIZED_BUNDLE_IMPL_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_AUTHORIZED_BUNDLE_IMPL_H_

#include <vector>

#include "base/types/pass_key.h"
#include "qorai/components/qorai_wallet/browser/zcash/rust/lib.rs.h"
#include "qorai/components/qorai_wallet/browser/zcash/rust/orchard_authorized_bundle.h"
#include "third_party/rust/cxx/v1/cxx.h"

namespace qorai_wallet::orchard {

class OrchardAuthorizedBundleImpl : public OrchardAuthorizedBundle {
 public:
  OrchardAuthorizedBundleImpl(
      base::PassKey<class OrchardUnauthorizedBundleImpl>,
      ::rust::Box<CxxOrchardAuthorizedBundle>);
  ~OrchardAuthorizedBundleImpl() override;

  std::vector<uint8_t> GetOrchardRawTxPart() override;

 private:
  ::rust::Box<CxxOrchardAuthorizedBundle> cxx_orchard_authorized_bundle_;
};

}  // namespace qorai_wallet::orchard

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_AUTHORIZED_BUNDLE_IMPL_H_
