/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/services/network/public/cpp/system_request_handler.h"

#define QORAI_CREATE_LOADER_AND_START \
  network::SystemRequestHandler::GetInstance()->OnBeforeSystemRequest(request)

#include <components/safe_browsing/content/browser/safe_browsing_network_context.cc>

#undef QORAI_CREATE_LOADER_AND_START
