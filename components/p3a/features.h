/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_P3A_FEATURES_H_
#define QORAI_COMPONENTS_P3A_FEATURES_H_

#include "base/feature_list.h"

namespace p3a {
namespace features {

// See https://github.com/qorai/qorai-browser/issues/31718 for more info.
BASE_DECLARE_FEATURE(kConstellationEnclaveAttestation);

bool IsConstellationEnclaveAttestationEnabled();

}  // namespace features
}  // namespace p3a

#endif  // QORAI_COMPONENTS_P3A_FEATURES_H_
