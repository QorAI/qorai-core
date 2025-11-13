/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_browser_process.h"

#include <cstddef>

QoraiBrowserProcess* g_qorai_browser_process = nullptr;

QoraiBrowserProcess::QoraiBrowserProcess() = default;

QoraiBrowserProcess::~QoraiBrowserProcess() = default;
