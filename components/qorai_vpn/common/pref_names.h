/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_VPN_COMMON_PREF_NAMES_H_

#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "build/build_config.h"

namespace qorai_vpn {
namespace prefs {
inline constexpr char kManagedQoraiVPNDisabled[] =
    "qorai.qorai_vpn.disabled_by_policy";
inline constexpr char kQoraiVPNLocalStateMigrated[] =
    "qorai.qorai_vpn.migrated";
inline constexpr char kQoraiVPNRootPref[] = "qorai.qorai_vpn";
inline constexpr char kQoraiVPNShowButton[] = "qorai.qorai_vpn.show_button";
inline constexpr char kQoraiVPNRegionList[] = "qorai.qorai_vpn.region_list";
// Cached fetched date for trying to refresh region_list once per day
inline constexpr char kQoraiVPNRegionListFetchedDate[] =
    "qorai.qorai_vpn.region_list_fetched_date";
inline constexpr char kQoraiVPNDeviceRegion[] =
    "qorai.qorai_vpn.device_region_name";

// For backward-compatibility, v1's selected region name is preserved.
// If user runs older qorai with migrated profile, it could make crash as
// region data list v1 doesn't have entry for v2's selected region name.
// Retaining only this data only is sufficient for backward compatibility
// because region list and timezone data are fetched again as v2 data becomes
// invalid in old browser.
inline constexpr char kQoraiVPNSelectedRegion[] =
    "qorai.qorai_vpn.selected_region_name";
inline constexpr char kQoraiVPNSelectedRegionV2[] =
    "qorai.qorai_vpn.selected_region_name_v2";
inline constexpr char kQoraiVPNRegionListVersion[] =
    "qorai.qorai_vpn.region_list_version";
#if BUILDFLAG(IS_WIN)
inline constexpr char kQoraiVpnShowDNSPolicyWarningDialog[] =
    "qorai.qorai_vpn.show_dns_policy_warning_dialog";
inline constexpr char kQoraiVPNShowNotificationDialog[] =
    "qorai.qorai_vpn.show_notification_dialog";
inline constexpr char kQoraiVPNWireguardFallbackDialog[] =
    "qorai.qorai_vpn.show_wireguard_fallback_dialog";
#endif  // BUILDFLAG(IS_WIN)
#if BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
inline constexpr char kQoraiVPNWireguardEnabled[] =
    "qorai.qorai_vpn.wireguard_enabled";
#endif

#if BUILDFLAG(IS_MAC)
inline constexpr char kQoraiVPNOnDemandEnabled[] =
    "qorai.qorai_vpn.on_demand_enabled";
#endif

inline constexpr char kQoraiVPNSmartProxyRoutingEnabled[] =
    "qorai.qorai_vpn.smart_proxy_routing_enabled";

inline constexpr char kQoraiVPNWireguardProfileCredentials[] =
    "qorai.qorai_vpn.wireguard.profile_credentials";
inline constexpr char kQoraiVPNEnvironment[] = "qorai.qorai_vpn.env";
// Dict that has subscriber credential its expiration date.
inline constexpr char kQoraiVPNSubscriberCredential[] =
    "qorai.qorai_vpn.subscriber_credential";
// Set the expiry of the last redeemed credential.
// Useful in case redemption fails and person uses all credentials.
inline constexpr char kQoraiVPNLastCredentialExpiry[] =
    "qorai.qorai_vpn.last_credential_expiry";

// Time that session expired occurs.
inline constexpr char kQoraiVPNSessionExpiredDate[] =
    "qorai.qorai_vpn.session_expired_date";

#if BUILDFLAG(IS_ANDROID)
inline constexpr char kQoraiVPNPurchaseTokenAndroid[] =
    "qorai.qorai_vpn.purchase_token_android";
inline constexpr char kQoraiVPNPackageAndroid[] =
    "qorai.qorai_vpn.package_android";
inline constexpr char kQoraiVPNProductIdAndroid[] =
    "qorai.qorai_vpn.product_id_android";
#endif

inline constexpr char kQoraiVPNFirstUseTime[] =
    "qorai.qorai_vpn.first_use_time";
inline constexpr char kQoraiVPNLastUseTime[] = "qorai.qorai_vpn.last_use_time";
inline constexpr char kQoraiVPNUsedSecondDay[] =
    "qorai.qorai_vpn.used_second_day";
inline constexpr char kQoraiVPNDaysInMonthUsed[] =
    "qorai.qorai_vpn.days_in_month_used";
inline constexpr char kQoraiVPNWidgetUsageWeeklyStorage[] =
    "qorai.qorai_vpn.widget_usage";
inline constexpr char kQoraiVPNConnectedMinutesWeeklyStorage[] =
    "qorai.qorai_vpn.connected_minutes";
}  // namespace prefs

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_COMMON_PREF_NAMES_H_
