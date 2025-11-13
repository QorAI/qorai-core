/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_POLICY_QORAI_SIMPLE_POLICY_MAP_IOS_H_
#define QORAI_IOS_BROWSER_POLICY_QORAI_SIMPLE_POLICY_MAP_IOS_H_

#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/common/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/p3a/pref_names.h"
#include "qorai/components/playlist/core/common/pref_names.h"
#include "build/build_config.h"
#include "components/policy/core/browser/configuration_policy_handler.h"
#include "components/policy/policy_constants.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

namespace policy {

inline constexpr PolicyToPreferenceMapEntry kQoraiSimplePolicyMap[] = {
    {
        policy::key::kQoraiWalletDisabled,
        qorai_wallet::prefs::kDisabledByPolicy,
        base::Value::Type::BOOLEAN,
    },
    {
        policy::key::kQoraiAIChatEnabled,
        ai_chat::prefs::kEnabledByPolicy,
        base::Value::Type::BOOLEAN,
    },
    {
        policy::key::kQoraiRewardsDisabled,
        qorai_rewards::prefs::kDisabledByPolicy,
        base::Value::Type::BOOLEAN,
    },
    {
        policy::key::kQoraiTalkDisabled,
        kQoraiTalkDisabledByPolicy,
        base::Value::Type::BOOLEAN,
    },
    {
        policy::key::kQoraiNewsDisabled,
        qorai_news::prefs::kQoraiNewsDisabledByPolicy,
        base::Value::Type::BOOLEAN,
    },
#if BUILDFLAG(ENABLE_QORAI_VPN)
    {
        policy::key::kQoraiVPNDisabled,
        qorai_vpn::prefs::kManagedQoraiVPNDisabled,
        base::Value::Type::BOOLEAN,
    },
#endif
    {
        policy::key::kQoraiP3AEnabled,
        p3a::kP3AEnabled,
        base::Value::Type::BOOLEAN,
    },
    {
        policy::key::kQoraiStatsPingEnabled,
        kStatsReportingEnabled,
        base::Value::Type::BOOLEAN,
    },
    {
        policy::key::kQoraiPlaylistEnabled,
        playlist::kPlaylistEnabledPref,
        base::Value::Type::BOOLEAN,
    },
};

}  // namespace policy

#endif  // QORAI_IOS_BROWSER_POLICY_QORAI_SIMPLE_POLICY_MAP_IOS_H_
