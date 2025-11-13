/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_COMMON_QORAI_VPN_UTILS_H_
#define QORAI_COMPONENTS_QORAI_VPN_COMMON_QORAI_VPN_UTILS_H_

#include <string>

#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#include "build/build_config.h"

class GURL;
class PrefRegistrySimple;
class PrefService;
namespace user_prefs {
class PrefRegistrySyncable;
}  // namespace user_prefs

namespace version_info {
enum class Channel;
}  // namespace version_info

namespace qorai_vpn {

std::string GetQoraiVPNEntryName(version_info::Channel channel);
bool IsQoraiVPNEnabled(PrefService* prefs);
bool IsQoraiVPNFeatureEnabled();
bool IsQoraiVPNDisabledByPolicy(PrefService* prefs);
std::string GetQoraiVPNPaymentsEnv(const std::string& env);
std::string GetManageUrl(const std::string& env);
void MigrateVPNSettings(PrefService* profile_prefs, PrefService* local_prefs);
void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
void MigrateLocalStatePrefs(PrefService* local_prefs);
void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);
void RegisterAndroidProfilePrefs(PrefRegistrySimple* registry);
bool HasValidSubscriberCredential(PrefService* local_prefs);
std::string GetSubscriberCredential(PrefService* local_prefs);
bool HasValidSkusCredential(PrefService* local_prefs);
std::string GetSkusCredential(PrefService* local_prefs);
bool IsQoraiVPNWireguardEnabled(PrefService* local_state);
GURL GetManageURLForUIType(mojom::ManageURLType type, const GURL& manage_url);

#if BUILDFLAG(IS_WIN)
void EnableWireguardIfPossible(PrefService* local_prefs);
#endif  // BUILDFLAG(IS_WIN)
}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_COMMON_QORAI_VPN_UTILS_H_
