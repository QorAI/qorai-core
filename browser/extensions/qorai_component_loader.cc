/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/extensions/qorai_component_loader.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "base/check_op.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/json/json_reader.h"
#include "qorai/components/qorai_extension/grit/qorai_extension.h"
#include "qorai/components/constants/qorai_switches.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/constants.h"
#include "extensions/common/mojom/manifest.mojom.h"
#include "ui/base/resource/resource_bundle.h"

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
#include "qorai/components/web_discovery/common/features.h"
#endif

namespace extensions {

QoraiComponentLoader::QoraiComponentLoader(Profile* profile)
    : ComponentLoader(profile),
      profile_(profile),
      profile_prefs_(profile->GetPrefs()) {
  pref_change_registrar_.Init(profile_prefs_);
  pref_change_registrar_.Add(
      kWebDiscoveryEnabled,
      base::BindRepeating(&QoraiComponentLoader::UpdateQoraiExtension,
                          base::Unretained(this)));
}

QoraiComponentLoader::~QoraiComponentLoader() = default;

void QoraiComponentLoader::AddDefaultComponentExtensions(
    bool skip_session_components) {
  ComponentLoader::AddDefaultComponentExtensions(skip_session_components);
  UpdateQoraiExtension();
}

bool QoraiComponentLoader::UseQoraiExtensionBackgroundPage() {
  bool native_enabled = false;
#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  native_enabled = base::FeatureList::IsEnabled(
      web_discovery::features::kQoraiWebDiscoveryNative);
#endif
  return !native_enabled && profile_prefs_->GetBoolean(kWebDiscoveryEnabled);
}

void QoraiComponentLoader::UpdateQoraiExtension() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (command_line.HasSwitch(switches::kDisableQoraiExtension)) {
    return;
  }

  base::FilePath qorai_extension_path(FILE_PATH_LITERAL(""));
  qorai_extension_path =
      qorai_extension_path.Append(FILE_PATH_LITERAL("qorai_extension"));
  auto& resource_bundle = ui::ResourceBundle::GetSharedInstance();
  std::optional<base::Value::Dict> manifest = base::JSONReader::ReadDict(
      resource_bundle.LoadDataResourceString(IDR_QORAI_EXTENSION),
      base::JSON_PARSE_CHROMIUM_EXTENSIONS);
  CHECK(manifest) << "invalid Qorai Extension manifest";

  // The background page is a conditional. Replace MAYBE_background in the
  // manifest to "background" or remove it.
  auto background_value = manifest->Extract("MAYBE_background");
  if (UseQoraiExtensionBackgroundPage() && background_value) {
    manifest->Set("background", std::move(*background_value));
  }

  extensions::ExtensionRegistry* registry =
      extensions::ExtensionRegistry::Get(profile_);
  const Extension* current_extension =
      registry->GetInstalledExtension(qorai_extension_id);

  if (current_extension) {
    const auto* current_manifest = current_extension->manifest();
    if (current_manifest && *current_manifest->value() == *manifest) {
      return;  // Skip reload, nothing is actually changed.
    }
    Remove(qorai_extension_id);
  }

  const auto id = Add(std::move(*manifest), qorai_extension_path);
  CHECK_EQ(id, qorai_extension_id);
}

}  // namespace extensions
