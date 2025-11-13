/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_WEB_DISCOVERY_BROWSER_PREF_NAMES_H_
#define QORAI_COMPONENTS_WEB_DISCOVERY_BROWSER_PREF_NAMES_H_

#include "base/types/strong_alias.h"

namespace web_discovery {

using RequestQueuePrefName =
    base::StrongAlias<class QueuePrefNameTag, std::string_view>;

// Profile prefs
inline constexpr char kWebDiscoveryEnabled[] = "qorai.web_discovery_enabled";

// The following pref values are used for generating
// anonymous signatures for user submissions.
// Since they are not used for encrypting sensitive data,
// they do not require secure storage.
inline constexpr char kCredentialRSAPrivateKey[] =
    "qorai.web_discovery.rsa_priv_key";
inline constexpr char kAnonymousCredentialsDict[] =
    "qorai.web_discovery.anon_creds";

inline constexpr auto kScheduledDoubleFetches =
    RequestQueuePrefName("qorai.web_discovery.scheduled_double_fetches");
inline constexpr auto kScheduledReports =
    RequestQueuePrefName("qorai.web_discovery.scheduled_reports");
inline constexpr char kUsedBasenameCounts[] =
    "qorai.web_discovery.used_basename_counts";
inline constexpr char kPageCounts[] = "qorai.web_discovery.page_counts";

// Local state

// Stores the last retrieval time of patterns.json from the
// Web Discovery server, in order to schedule the next retrieval/update.
inline constexpr char kPatternsRetrievalTime[] =
    "qorai.web_discovery.patterns_retrieval_time";

}  // namespace web_discovery

#endif  // QORAI_COMPONENTS_WEB_DISCOVERY_BROWSER_PREF_NAMES_H_
