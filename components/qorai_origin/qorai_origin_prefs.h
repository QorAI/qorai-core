/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_PREFS_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_PREFS_H_

class PrefRegistrySimple;

namespace qorai_origin {

// Register local state preferences for QorAI Origin system
void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_PREFS_H_
