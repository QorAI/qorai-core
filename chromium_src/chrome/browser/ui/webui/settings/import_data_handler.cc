/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/importer/qorai_external_process_importer_host.h"
#include "qorai/components/constants/pref_names.h"

#define ExternalProcessImporterHost QoraiExternalProcessImporterHost

// NOTE: When we add new import feature, also consider to add it for importing
// in welcome page.
// See IMPORT_BROWSER_DATA_REQUESTED action in welcome_reducer.ts.
#define QORAI_IMPORT_DATA                                          \
  if (type_dict.FindBool(kImportDialogExtensions).value_or(false)) \
    selected_items |= user_data_importer::EXTENSIONS;              \
  if (type_dict.FindBool(kImportDialogPayments).value_or(false))   \
    selected_items |= user_data_importer::PAYMENTS;

#define QORAI_SEND_BROWSER_PROFILE_DATA                                        \
  browser_profile.Set(                                                         \
      "extensions", (browser_services & user_data_importer::EXTENSIONS) != 0); \
  browser_profile.Set("payments",                                              \
                      (browser_services & user_data_importer::PAYMENTS) != 0);

#include <chrome/browser/ui/webui/settings/import_data_handler.cc>
#undef ExternalProcessImporterHost
#undef QORAI_IMPORT_DATA
#undef QORAI_SEND_BROWSER_PROFILE_DATA
