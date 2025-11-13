/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/profile_resetter/qorai_profile_resetter.h"

#define ProfileResetter QoraiProfileResetter
#include <chrome/browser/ui/webui/settings/reset_settings_handler.cc>
#undef ProfileResetter
