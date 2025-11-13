/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/services/network/public/cpp/system_request_handler.h"

#define QORAI_CREATE_LOADER_AND_START                                  \
  network::SystemRequestHandler::GetInstance()->OnBeforeSystemRequest( \
      url_request)

#include <chrome/browser/net/system_network_context_manager.cc>

#undef QORAI_CREATE_LOADER_AND_START
