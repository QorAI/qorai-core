// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/commands/common/features.h"
#include "base/feature_list.h"

namespace commands::features {

// This feature enables a page a qorai://commands which lists all available
// commands in QorAI, and the shortcut for executing them. In future, this will
// allow configuring the shortcuts for various commands.
BASE_FEATURE(kQorAICommands, base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace commands::features
