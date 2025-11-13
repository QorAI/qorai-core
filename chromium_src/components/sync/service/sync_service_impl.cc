/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/logging.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "qorai/components/sync/service/qorai_sync_auth_manager.h"
#include "qorai/components/sync/service/qorai_sync_stopped_reporter.h"
#include "components/prefs/pref_service.h"
#include "components/sync/base/sync_util.h"

namespace syncer {

GURL QoraiGetSyncServiceURL(const base::CommandLine& command_line,
                            version_info::Channel channel,
                            PrefService* prefs) {
  // Allow group policy to override sync service URL.
  // This has a higher priority than the --sync-url command-line param.
  // https://github.com/qorai/qorai-browser/issues/20431
  if (prefs && prefs->IsManagedPreference(qorai_sync::kCustomSyncServiceUrl)) {
    std::string value(prefs->GetString(qorai_sync::kCustomSyncServiceUrl));
    if (!value.empty()) {
      GURL custom_sync_url(value);
      // Provided URL must be HTTPS.
      if (custom_sync_url.is_valid() &&
          custom_sync_url.SchemeIs(url::kHttpsScheme)) {
        DVLOG(2) << "Sync URL specified via GPO: "
                 << prefs->GetString(qorai_sync::kCustomSyncServiceUrl);
        return custom_sync_url;
      } else {
        LOG(WARNING) << "The following sync URL specified via GPO "
                     << "is invalid: " << value;
      }
    }
  }

  // Default logic.
  // See `GetSyncServiceURL` in `components/sync/base/sync_util.cc`
  return GetSyncServiceURL(command_line, channel);
}

}  // namespace syncer

#define SyncAuthManager QoraiSyncAuthManager
#define SyncStoppedReporter QoraiSyncStoppedReporter
#define GetSyncServiceURL(...) \
  QoraiGetSyncServiceURL(__VA_ARGS__, sync_client_->GetPrefService())

#include <components/sync/service/sync_service_impl.cc>

#undef SyncAuthManager
#undef SyncStoppedReporter
#undef GetSyncServiceURL
