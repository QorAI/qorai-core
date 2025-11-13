/* Copyright (c) 2018 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <optional>

#include "qorai/browser/ui/qorai_layout_constants.h"

// Forward declaration
int GetLayoutConstant_ChromiumImpl(LayoutConstant constant);
gfx::Insets GetLayoutInsets_ChromiumImpl(LayoutInset inset);

#define LayoutConstant LayoutConstant constant) {                            \
    const std::optional<int> qoraiOption = GetQoraiLayoutConstant(constant); \
    if (qoraiOption) {                                                       \
      return qoraiOption.value();                                            \
    }                                                                        \
                                                                             \
    return GetLayoutConstant_ChromiumImpl(constant);                         \
  }                                                                          \
                                                                             \
  int GetLayoutConstant_ChromiumImpl(LayoutConstant

#define LayoutInset LayoutInset inset) {           \
    const std::optional<gfx::Insets> qoraiOption = \
        GetQoraiLayoutInsets(inset);               \
    if (qoraiOption) {                             \
      return qoraiOption.value();                  \
    }                                              \
                                                   \
    return GetLayoutInsets_ChromiumImpl(inset);    \
  }                                                \
                                                   \
  gfx::Insets GetLayoutInsets_ChromiumImpl(LayoutInset

#include <chrome/browser/ui/layout_constants.cc>
#undef LayoutInset
#undef LayoutConstant
