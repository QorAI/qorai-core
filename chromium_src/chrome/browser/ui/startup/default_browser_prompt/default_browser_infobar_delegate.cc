/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_shell_integration.h"

#define DefaultBrowserWorker QoraiDefaultBrowserWorker
#include <chrome/browser/ui/startup/default_browser_prompt/default_browser_infobar_delegate.cc>
#undef DefaultBrowserWorker
