// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_user_agent/common/features.h"

#include "base/feature_list.h"

namespace qorai_user_agent::features {

BASE_FEATURE(kUseQoraiUserAgent,
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace qorai_user_agent::features
