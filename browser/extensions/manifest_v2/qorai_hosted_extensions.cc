// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/extensions/manifest_v2/qorai_hosted_extensions.h"

#include "base/containers/map_util.h"

namespace extensions_mv2 {

namespace {

// Checks kQoraiHosted and kWebStoreHosted maps are in consistent state at
// compile time. Keys of one map should be the values of another.
consteval bool CheckExtensionMaps() {
  for (const auto& [qorai_hosted_key, qorai_hosted_value] : kQoraiHosted) {
    if (qorai_hosted_value.empty()) {
      // skip Qorai-hosted extension which doesn't have the WebStore
      // counterpart.
      continue;
    }

    bool ok = false;
    for (const auto& [webstore_hosted_key, webstore_hosted_value] :
         kWebStoreHosted) {
      if (qorai_hosted_value == webstore_hosted_key &&
          qorai_hosted_key == webstore_hosted_value) {
        ok = true;
        break;
      }
    }
    if (!ok) {
      return false;
    }
  }
  return true;
}

static_assert(CheckExtensionMaps(),
              "kQoraiHosted & kWebStoreHosted aren't consistent");
}  // namespace

bool IsKnownQoraiHostedExtension(const extensions::ExtensionId& id) {
  return kQoraiHosted.contains(id);
}

bool IsKnownWebStoreHostedExtension(const extensions::ExtensionId& id) {
  return kWebStoreHosted.contains(id);
}

std::optional<extensions::ExtensionId> GetQoraiHostedExtensionId(
    const extensions::ExtensionId& webstore_extension_id) {
  if (const auto* fnd =
          base::FindOrNull(kWebStoreHosted, webstore_extension_id)) {
    return extensions::ExtensionId(*fnd);
  }
  return std::nullopt;
}

std::optional<extensions::ExtensionId> GetWebStoreHostedExtensionId(
    const extensions::ExtensionId& qorai_hosted_extension_id) {
  if (const auto* fnd =
          base::FindOrNull(kQoraiHosted, qorai_hosted_extension_id)) {
    return extensions::ExtensionId(*fnd);
  }
  return std::nullopt;
}

}  // namespace extensions_mv2
