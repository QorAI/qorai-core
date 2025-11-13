/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_NOTIFICATIONS_NOTIFICATION_KEYS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_NOTIFICATIONS_NOTIFICATION_KEYS_H_

namespace qorai_rewards::internal {
namespace notifications {

inline constexpr char kWalletDisconnected[] = "wallet_disconnected";
inline constexpr char kSelfCustodyAvailable[] = "self_custody_available";

}  // namespace notifications
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_NOTIFICATIONS_NOTIFICATION_KEYS_H_
