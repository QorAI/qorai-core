/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_BASE_FEATURE_LIST_H_
#define QORAI_CHROMIUM_SRC_BASE_FEATURE_LIST_H_

#define IsFeatureOverridden                                               \
  IsFeatureOverridden_ChromiumImpl(std::string_view feature_name) const;  \
  static FeatureState GetCompileTimeFeatureState(const Feature& feature); \
  bool IsFeatureOverridden

#define GetStateIfOverridden                                 \
  GetStateIfOverridden_ChromiumImpl(const Feature& feature); \
  static std::optional<bool> GetStateIfOverridden

#include <base/feature_list.h>  // IWYU pragma: export

#undef IsFeatureOverridden
#undef GetStateIfOverridden

#endif  // QORAI_CHROMIUM_SRC_BASE_FEATURE_LIST_H_
