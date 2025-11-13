// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_EXTENSIONS_MANIFEST_V2_QORAI_HOSTED_EXTENSIONS_H_
#define QORAI_BROWSER_EXTENSIONS_MANIFEST_V2_QORAI_HOSTED_EXTENSIONS_H_

#include <array>
#include <optional>

#include "base/containers/fixed_flat_map.h"
#include "extensions/common/extension_id.h"

namespace extensions_mv2 {

inline constexpr char kNoScriptId[] = "bgkmgpgeempochogfoddiobpbhdfgkdi";
inline constexpr char kUBlockId[] = "jcokkipkhhgiakinbnnplhkdbjbgcgpe";
inline constexpr char kUMatrixId[] = "fplfeajmkijmaeldaknocljmmoebdgmk";
inline constexpr char kAdGuardId[] = "ejoelgckfgogkoppbgkklbbjdkjdbmen";

inline constexpr char kWebStoreNoScriptId[] =
    "doojmbjmlfjjnbmnoijecmcbfeoakpjm";
inline constexpr char kWebStoreUBlockId[] = "cjpalhdlnbpafiamejdnhcphjbkeiagm";
inline constexpr char kWebStoreUMatrixId[] = "ogfcmafjalglgifnmanfmnieipoejdcf";
inline constexpr char kWebStoreAdGuardId[] = "gfggjaccafhcbfogfkogggoepomehbjl";

inline constexpr auto kQoraiHosted =
    base::MakeFixedFlatMap<std::string_view, std::string_view>(
        {{kNoScriptId, kWebStoreNoScriptId},
         {kUBlockId, kWebStoreUBlockId},
         {kUMatrixId, kWebStoreUMatrixId},
         {kAdGuardId, kWebStoreAdGuardId}});

inline constexpr auto kWebStoreHosted =
    base::MakeFixedFlatMap<std::string_view, std::string_view>(
        {{kWebStoreNoScriptId, kNoScriptId},
         {kWebStoreUBlockId, kUBlockId},
         {kWebStoreUMatrixId, kUMatrixId},
         {kWebStoreAdGuardId, kAdGuardId}});

// In future there can be more qorai-hosted mv2 extensions than published on
// WebStore.
static_assert(kQoraiHosted.size() >= kWebStoreHosted.size());

namespace internal {
consteval std::array<std::string_view, kQoraiHosted.size()>
GetPreconfiguredManifestV2Extensions() {
  // This can be made more idiomatic once Chromium style allows
  // std::views::keys
  std::array<std::string_view, kQoraiHosted.size()> result{};
  std::ranges::transform(kQoraiHosted, result.begin(),
                         [](const auto& p) { return p.first; });
  return result;
}
}  // namespace internal

inline constexpr auto kPreconfiguredManifestV2Extensions =
    internal::GetPreconfiguredManifestV2Extensions();

static_assert(kPreconfiguredManifestV2Extensions.size() == kQoraiHosted.size());

bool IsKnownQoraiHostedExtension(const extensions::ExtensionId& id);
bool IsKnownWebStoreHostedExtension(const extensions::ExtensionId& id);

// Returns the Qorai-hosted extension id for a given WebStore-hosted.
// In case if the given id is unknown returns nullopt.
std::optional<extensions::ExtensionId> GetQoraiHostedExtensionId(
    const extensions::ExtensionId& webstore_extension_id);

// Returns the WebStore-hosted extension id for a given Qorai-hosted.
// In case if the given id is unknown returns nullopt.
std::optional<extensions::ExtensionId> GetWebStoreHostedExtensionId(
    const extensions::ExtensionId& qorai_hosted_extension_id);
}  // namespace extensions_mv2

#endif  // QORAI_BROWSER_EXTENSIONS_MANIFEST_V2_QORAI_HOSTED_EXTENSIONS_H_
