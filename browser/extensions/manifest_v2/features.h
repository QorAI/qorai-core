// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_EXTENSIONS_MANIFEST_V2_FEATURES_H_
#define QORAI_BROWSER_EXTENSIONS_MANIFEST_V2_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace extensions_mv2::features {

BASE_DECLARE_FEATURE(kExtensionsManifestV2);
BASE_DECLARE_FEATURE_PARAM(bool, kExtensionsManifestV2BackupSettings);
BASE_DECLARE_FEATURE_PARAM(bool, kExtensionsManifestV2BImportSettingsOnInstall);
BASE_DECLARE_FEATURE_PARAM(bool, kExtensionsManifestV2AutoInstallQoraiHosted);

bool IsSettingsBackupEnabled();
bool IsSettingsImportEnabled();
bool IsExtensionReplacementEnabled();

}  // namespace extensions_mv2::features

#endif  // QORAI_BROWSER_EXTENSIONS_MANIFEST_V2_FEATURES_H_
