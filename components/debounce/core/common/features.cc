// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/debounce/core/common/features.h"

#include "base/feature_list.h"

namespace debounce::features {

// When enabled, Qorai will try to parse tracking URLs of the form
// https://tracker.example.com/?url=http://final.example.com/
// and automatically redirect to the final URL without sending any
// network requests to the tracker.
BASE_FEATURE(kQoraiDebounce, base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace debounce::features
