/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_PREF_NAMES_H_

#include "base/component_export.h"
#include "build/build_config.h"

class PrefRegistrySimple;

namespace qorai_origin {

// Base key for all profile-scoped QoraiOrigin policy preferences in local state
inline constexpr char kQoraiOriginPolicies[] = "qorai.qorai_origin.policies";

namespace prefs {

#if BUILDFLAG(IS_ANDROID)
inline constexpr char kQoraiOriginSubscriptionActiveAndroid[] =
    "qorai.origin.subscription_active_android";
inline constexpr char kQoraiOriginPurchaseTokenAndroid[] =
    "qorai.origin.purchase_token_android";
inline constexpr char kQoraiOriginPackageNameAndroid[] =
    "qorai.origin.package_name_android";
inline constexpr char kQoraiOriginProductIdAndroid[] =
    "qorai.origin.product_id_android";
inline constexpr char kQoraiOriginOrderIdAndroid[] =
    "qorai.origin.order_id_android";
inline constexpr char kQoraiOriginSubscriptionLinkStatusAndroid[] =
    "qorai.origin.subscription_link_status_android";
#endif

void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace prefs
}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_PREF_NAMES_H_
