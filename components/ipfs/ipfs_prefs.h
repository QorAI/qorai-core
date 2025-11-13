// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_IPFS_IPFS_PREFS_H_
#define QORAI_COMPONENTS_IPFS_IPFS_PREFS_H_

#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace ipfs {

namespace prefs {

// Used to enable/disable IPFS via admin policy. Deprecated
inline constexpr char kIPFSEnabledByPolicy[] = "qorai.ipfs.enabled";

}  // namespace prefs

void RegisterDeprecatedIpfsPrefs(PrefRegistrySimple* registry);

void ClearDeprecatedIpfsPrefs(PrefService* profile_prefs);

}  // namespace ipfs

#endif  // QORAI_COMPONENTS_IPFS_IPFS_PREFS_H_
