/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_DAT_FILE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_DAT_FILE_UTIL_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/component_export.h"
#include "base/files/file_path.h"

namespace qorai_component_updater {

using DATFileDataBuffer = std::vector<unsigned char>;

COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER)
std::string GetDATFileAsString(const base::FilePath& file_path);

COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER)
DATFileDataBuffer ReadDATFileData(const base::FilePath& dat_file_path);

}  // namespace qorai_component_updater

#endif  // QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_DAT_FILE_UTIL_H_
