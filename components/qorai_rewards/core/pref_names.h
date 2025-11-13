/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_PREF_NAMES_H_

namespace qorai_rewards::prefs {

// Used to enable/disable Rewards via a policy.
inline constexpr char kDisabledByPolicy[] = "qorai.rewards.disabled_by_policy";

// Stores the "Rewards version" in which the user's Rewards account was created.
// This value is intended to be used to distinguish "legacy" users when Rewards
// features are migrated. Note that if the user has not yet created a Rewards
// account, this value will default to the empty string.
inline constexpr char kUserVersion[] = "qorai.rewards.user_version";
inline constexpr char kCurrentUserVersion[] = "2.5";

inline constexpr char kHideButton[] =
    "qorai.hide_qorai_rewards_button";  // DEPRECATED
inline constexpr char kShowButton[] =
    "qorai.show_qorai_rewards_button";  // DEPRECATED
inline constexpr char kShowLocationBarButton[] =
    "qorai.rewards.show_qorai_rewards_button_in_location_bar";
inline constexpr char kEnabled[] = "qorai.rewards.enabled";
inline constexpr char kDeclaredGeo[] = "qorai.rewards.declared_geo";
inline constexpr char kNotifications[] = "qorai.rewards.notifications";
inline constexpr char kNotificationTimerInterval[] =
    "qorai.rewards.notification_timer_interval";
inline constexpr char kBackupNotificationInterval[] =
    "qorai.rewards.backup_notification_interval";  // DEPRECATED
inline constexpr char kBackupSucceeded[] =
    "qorai.rewards.backup_succeeded";  // DEPRECATED
inline constexpr char kUserHasFunded[] =
    "qorai.rewards.user_has_funded";  // DEPRECATED
inline constexpr char kUserHasClaimedGrant[] =
    "qorai.rewards.user_has_claimed_grant";  // DEPRECATED
inline constexpr char kAddFundsNotification[] =
    "qorai.rewards.add_funds_notification";  // DEPRECATED
inline constexpr char kNotificationStartupDelay[] =
    "qorai.rewards.notification_startup_delay";
inline constexpr char kExternalWallets[] =
    "qorai.rewards.external_wallets";  // DEPRECATED

// Defined in core
inline constexpr char kServerPublisherListStamp[] =
    "qorai.rewards.publisher_prefix_list_stamp";
inline constexpr char kUpholdAnonAddress[] =
    "qorai.rewards.uphold_anon_address";  // DEPRECATED
inline constexpr char kBadgeText[] = "qorai.rewards.badge_text";
inline constexpr char kUseRewardsStagingServer[] =
    "qorai.rewards.use_staging_server";
inline constexpr char kExternalWalletType[] =
    "qorai.rewards.external_wallet_type";
inline constexpr char kSelfCustodyAvailable[] =
    "qorai.rewards.self_custody_available";
inline constexpr char kSelfCustodyInviteDismissed[] =
    "qorai.rewards.self_custody_invite_dismissed";
inline constexpr char kP3APanelTriggerCount[] =
    "qorai.rewards.p3a_panel_trigger_count";
inline constexpr char kP3AOfferClickCount[] =
    "qorai.rewards.p3a_offer_click_count";
inline constexpr char kPromotionLastFetchStamp[] =
    "qorai.rewards.promotion_last_fetch_stamp";  // DEPRECATED
inline constexpr char kPromotionCorruptedMigrated[] =
    "qorai.rewards.promotion_corrupted_migrated2";  // DEPRECATED
inline constexpr char kAnonTransferChecked[] =
    "qorai.rewards.anon_transfer_checked";
inline constexpr char kVersion[] = "qorai.rewards.version";
inline constexpr char kMinVisitTime[] = "qorai.rewards.ac.min_visit_time";
inline constexpr char kMinVisits[] = "qorai.rewards.ac.min_visits";
inline constexpr char kAllowNonVerified[] =
    "qorai.rewards.ac.allow_non_verified";  // DEPRECATED
inline constexpr char kAllowVideoContribution[] =
    "qorai.rewards.ac.allow_video_contributions";  // DEPRECATED
inline constexpr char kScoreA[] = "qorai.rewards.ac.score.a";
inline constexpr char kScoreB[] = "qorai.rewards.ac.score.b";
inline constexpr char kAutoContributeEnabled[] = "qorai.rewards.ac.enabled";
inline constexpr char kAutoContributeAmount[] = "qorai.rewards.ac.amount";
inline constexpr char kNextReconcileStamp[] =
    "qorai.rewards.ac.next_reconcile_stamp";
inline constexpr char kCreationStamp[] = "qorai.rewards.creation_stamp";
inline constexpr char kRecoverySeed[] =
    "qorai.rewards.wallet.seed";  // DEPRECATED
inline constexpr char kPaymentId[] =
    "qorai.rewards.wallet.payment_id";  // DEPRECATED
inline constexpr char kInlineTipButtonsEnabled[] =
    "qorai.rewards.inline_tip_buttons_enabled";  // DEPRECATED
inline constexpr char kInlineTipRedditEnabled[] =
    "qorai.rewards.inline_tip.reddit";  // DEPRECATED
inline constexpr char kInlineTipTwitterEnabled[] =
    "qorai.rewards.inline_tip.twitter";  // DEPRECATED
inline constexpr char kInlineTipGithubEnabled[] =
    "qorai.rewards.inline_tip.github";  // DEPRECATED
inline constexpr char kParameters[] = "qorai.rewards.parameters";
inline constexpr char kFetchOldBalance[] =
    "qorai.rewards.fetch_old_balance";  // DEPRECATED
inline constexpr char kEmptyBalanceChecked[] =
    "qorai.rewards.empty_balance_checked";  // DEPRECATED
inline constexpr char kWalletQorai[] = "qorai.rewards.wallets.qorai";
inline constexpr char kWalletUphold[] = "qorai.rewards.wallets.uphold";
inline constexpr char kWalletBitflyer[] = "qorai.rewards.wallets.bitflyer";
inline constexpr char kWalletGemini[] = "qorai.rewards.wallets.gemini";
inline constexpr char kWalletZebPay[] = "qorai.rewards.wallets.zebpay";
inline constexpr char kWalletSolana[] = "qorai.rewards.wallets.solana";
inline constexpr char kWalletCreationEnvironment[] =
    "qorai.rewards.wallet_creation_environment";
inline constexpr char kTosVersion[] = "qorai.rewards.tos_version";

inline constexpr char kRewardsPageViewCount[] =
    "qorai.rewards.p3a_page_view_count";
inline constexpr char kRewardsDesktopPanelViewCount[] =
    "qorai.rewards.p3a_desktop_panel_view_count";

// deprecated p3a prefs
inline constexpr char kAdsWereDisabled[] = "qorai.qorai_ads.were_disabled";
inline constexpr char kHasAdsP3AState[] = "qorai.qorai_ads.has_p3a_state";
inline constexpr char kAdsEnabledTimeDelta[] =
    "qorai.rewards.ads_enabled_time_delta";
inline constexpr char kAdsEnabledTimestamp[] =
    "qorai.rewards.ads_enabled_timestamp";

}  // namespace qorai_rewards::prefs

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_PREF_NAMES_H_
