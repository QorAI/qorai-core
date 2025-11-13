/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/extensions/chrome_component_extension_resource_manager.h"

#include "qorai/components/qorai_extension/grit/qorai_extension_generated_map.h"
#include "qorai/components/qorai_extension/grit/qorai_extension_resources_map.h"

#define QORAI_CHROME_COMPONENT_EXTENSION_RESOURCE_MANAGER_DATA_DATA \
  AddComponentResourceEntries(kQoraiExtension);                     \
  AddComponentResourceEntries(kQoraiExtensionGenerated);

#include <chrome/browser/extensions/chrome_component_extension_resource_manager.cc>
#undef QORAI_CHROME_COMPONENT_EXTENSION_RESOURCE_MANAGER_DATA_DATA
