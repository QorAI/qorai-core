/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/common/extensions/qorai_extensions_api_provider.h"

#include <string_view>

#include "qorai/common/extensions/api/api_features.h"
#include "qorai/common/extensions/api/behavior_features.h"
#include "qorai/common/extensions/api/generated_schemas.h"
#include "qorai/common/extensions/api/grit/qorai_api_resources.h"
#include "qorai/common/extensions/api/manifest_features.h"
#include "extensions/common/features/json_feature_provider_source.h"
#include "extensions/common/permissions/permissions_info.h"

namespace extensions {

QoraiExtensionsAPIProvider::QoraiExtensionsAPIProvider() = default;
QoraiExtensionsAPIProvider::~QoraiExtensionsAPIProvider() = default;

void QoraiExtensionsAPIProvider::AddAPIFeatures(FeatureProvider* provider) {
  AddQoraiAPIFeatures(provider);
}

void QoraiExtensionsAPIProvider::AddManifestFeatures(
    FeatureProvider* provider) {
  AddQoraiManifestFeatures(provider);
}

void QoraiExtensionsAPIProvider::AddPermissionFeatures(
    FeatureProvider* provider) {
}

void QoraiExtensionsAPIProvider::AddBehaviorFeatures(
    FeatureProvider* provider) {
  // No qorai-specific behavior features.
}

void QoraiExtensionsAPIProvider::AddAPIJSONSources(
    JSONFeatureProviderSource* json_source) {
  json_source->LoadJSON(IDR_QORAI_EXTENSION_API_FEATURES);
}

bool QoraiExtensionsAPIProvider::IsAPISchemaGenerated(const std::string& name) {
  return api::QoraiGeneratedSchemas::IsGenerated(name);
}

std::string_view QoraiExtensionsAPIProvider::GetAPISchema(
    const std::string& name) {
  return api::QoraiGeneratedSchemas::Get(name);
}

void QoraiExtensionsAPIProvider::RegisterPermissions(
    PermissionsInfo* permissions_info) {
  // No qorai-specific permissions.
}

void QoraiExtensionsAPIProvider::RegisterManifestHandlers() {
  // No qorai-specific manifest handlers.
}

}  // namespace extensions
