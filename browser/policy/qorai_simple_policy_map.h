/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_POLICY_QORAI_SIMPLE_POLICY_MAP_H_
#define QORAI_BROWSER_POLICY_QORAI_SIMPLE_POLICY_MAP_H_

#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/de_amp/common/pref_names.h"
#include "qorai/components/debounce/core/common/pref_names.h"
#include "qorai/components/global_privacy_control/pref_names.h"
#include "qorai/components/ipfs/buildflags/buildflags.h"
#include "qorai/components/p3a/pref_names.h"
#include "qorai/components/playlist/core/common/pref_names.h"
#include "qorai/components/query_filter/pref_names.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "build/build_config.h"
#include "components/policy/core/browser/configuration_policy_handler.h"
#include "components/policy/policy_constants.h"

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "qorai/components/qorai_wallet/common/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

#if BUILDFLAG(DEPRECATE_IPFS)
#include "qorai/components/ipfs/ipfs_prefs.h"  // nogncheck
#endif                                         // BUILDFLAG(DEPRECATE_IPFS)

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/speedreader_pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
#include "qorai/components/qorai_wayback_machine/pref_names.h"
#endif

namespace policy {

inline constexpr PolicyToPreferenceMapEntry kQoraiSimplePolicyMap[] = {
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
    {policy::key::kQoraiRewardsDisabled,
     qorai_rewards::prefs::kDisabledByPolicy, base::Value::Type::BOOLEAN},
    {policy::key::kQoraiWalletDisabled, qorai_wallet::prefs::kDisabledByPolicy,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiShieldsDisabledForUrls,
     kManagedQoraiShieldsDisabledForUrls, base::Value::Type::LIST},
    {policy::key::kQoraiShieldsEnabledForUrls,
     kManagedQoraiShieldsEnabledForUrls, base::Value::Type::LIST},
    {policy::key::kQoraiSyncUrl, qorai_sync::kCustomSyncServiceUrl,
     base::Value::Type::STRING},
#endif

#if BUILDFLAG(ENABLE_TOR)
    {policy::key::kTorDisabled, tor::prefs::kTorDisabled,
     base::Value::Type::BOOLEAN},
#endif
#if BUILDFLAG(ENABLE_QORAI_VPN)
    {policy::key::kQoraiVPNDisabled, qorai_vpn::prefs::kManagedQoraiVPNDisabled,
     base::Value::Type::BOOLEAN},
#endif
    {policy::key::kQoraiAIChatEnabled, ai_chat::prefs::kEnabledByPolicy,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiP3AEnabled, p3a::kP3AEnabled,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiStatsPingEnabled, kStatsReportingEnabled,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiPlaylistEnabled, playlist::kPlaylistEnabledPref,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiWebDiscoveryEnabled, kWebDiscoveryEnabled,
     base::Value::Type::BOOLEAN},
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
    {policy::key::kQoraiNewsDisabled,
     qorai_news::prefs::kQoraiNewsDisabledByPolicy, base::Value::Type::BOOLEAN},
    {policy::key::kQoraiTalkDisabled, kQoraiTalkDisabledByPolicy,
     base::Value::Type::BOOLEAN},
#if BUILDFLAG(ENABLE_SPEEDREADER)
    {policy::key::kQoraiSpeedreaderEnabled, speedreader::kSpeedreaderEnabled,
     base::Value::Type::BOOLEAN},
#endif
#endif
#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
    {policy::key::kQoraiWaybackMachineEnabled, kQoraiWaybackMachineEnabled,
     base::Value::Type::BOOLEAN},
#endif
#if BUILDFLAG(DEPRECATE_IPFS)
    {policy::key::kIPFSEnabled, ipfs::prefs::kIPFSEnabledByPolicy,
     base::Value::Type::BOOLEAN},
#endif  // BUILDFLAG(DEPRECATE_IPFS)
    {policy::key::kQoraiReduceLanguageEnabled,
     qorai_shields::prefs::kReduceLanguageEnabled, base::Value::Type::BOOLEAN},
    {policy::key::kQoraiDeAmpEnabled, de_amp::kDeAmpPrefEnabled,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiDebouncingEnabled, debounce::prefs::kDebounceEnabled,
     base::Value::Type::BOOLEAN},
    {policy::key::kDefaultQoraiFingerprintingV2Setting,
     kManagedDefaultQoraiFingerprintingV2, base::Value::Type::INTEGER},
    {policy::key::kQoraiTrackingQueryParametersFilteringEnabled,
     query_filter::kTrackingQueryParametersFilteringEnabled,
     base::Value::Type::BOOLEAN},
    {policy::key::kQoraiGlobalPrivacyControlEnabled,
     global_privacy_control::kGlobalPrivacyControlEnabled,
     base::Value::Type::BOOLEAN},
};

}  // namespace policy

#endif  // QORAI_BROWSER_POLICY_QORAI_SIMPLE_POLICY_MAP_H_
