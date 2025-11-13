/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/importer/qorai_external_process_importer_client.h"
#include "qorai/browser/importer/qorai_in_process_importer_bridge.h"

#define ExternalProcessImporterClient QoraiExternalProcessImporterClient
#define InProcessImporterBridge QoraiInProcessImporterBridge
#include <chrome/browser/importer/external_process_importer_host.cc>
#undef ExternalProcessImporterClient
#undef InProcessImporterBridge
