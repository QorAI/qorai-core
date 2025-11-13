/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_FEATURES_H_

#include "base/component_export.h"
#include "base/feature_list.h"

namespace qorai_component_updater {

COMPONENT_EXPORT(QORAI_COMPONENT_UPDATER)
BASE_DECLARE_FEATURE(kUseDevUpdaterUrl);

}  // namespace qorai_component_updater

#endif  // QORAI_COMPONENTS_QORAI_COMPONENT_UPDATER_BROWSER_FEATURES_H_
