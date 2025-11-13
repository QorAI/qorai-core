/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_stats/qorai_stats_updater_params.h"

#include <cmath>

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/system/sys_info.h"
#include "base/time/time.h"
#include "qorai/browser/qorai_stats/features.h"
#include "qorai/browser/qorai_stats/first_run_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_referrals/common/pref_names.h"
#include "qorai/components/qorai_stats/browser/qorai_stats_updater_util.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/headless/headless_mode_util.h"
#include "components/prefs/pref_service.h"
#include "content/public/common/content_switches.h"
#include "net/base/url_util.h"
#include "url/gurl.h"

namespace qorai_stats {

base::Time QoraiStatsUpdaterParams::g_current_time;
bool QoraiStatsUpdaterParams::g_force_first_run = false;
static constexpr base::TimeDelta g_dtoi_delete_delta =
    base::Seconds(30 * 24 * 60 * 60);

bool IsHeadlessOrAutomationMode() {
  return headless::IsHeadlessMode() ||
         base::CommandLine::ForCurrentProcess()->HasSwitch(
             ::switches::kEnableAutomation);
}

QoraiStatsUpdaterParams::QoraiStatsUpdaterParams(
    PrefService* stats_pref_service,
    const ProcessArch arch)
    : QoraiStatsUpdaterParams(stats_pref_service,
                              arch,
                              GetCurrentDateAsYMD(),
                              GetCurrentISOWeekNumber(),
                              GetCurrentMonth()) {}

QoraiStatsUpdaterParams::QoraiStatsUpdaterParams(
    PrefService* stats_pref_service,
    const ProcessArch arch,
    const std::string& ymd,
    int woy,
    int month)
    : stats_pref_service_(stats_pref_service),
      arch_(arch),
      ymd_(ymd),
      woy_(woy),
      month_(month) {
  LoadPrefs();
}

QoraiStatsUpdaterParams::~QoraiStatsUpdaterParams() = default;

std::string QoraiStatsUpdaterParams::GetDailyParam() const {
  return BooleanToString(
      base::CompareCaseInsensitiveASCII(ymd_, last_check_ymd_) == 1);
}

std::string QoraiStatsUpdaterParams::GetWeeklyParam() const {
  return BooleanToString(last_check_woy_ == 0 || woy_ != last_check_woy_);
}

std::string QoraiStatsUpdaterParams::GetMonthlyParam() const {
  return BooleanToString(last_check_month_ == 0 || month_ != last_check_month_);
}

std::string QoraiStatsUpdaterParams::GetFirstCheckMadeParam() const {
  return BooleanToString(!first_check_made_);
}

std::string QoraiStatsUpdaterParams::GetWeekOfInstallationParam() const {
  return week_of_installation_;
}

std::string QoraiStatsUpdaterParams::GetDateOfInstallationParam() const {
  return (GetCurrentTimeNow() - date_of_installation_ >= g_dtoi_delete_delta)
             ? "null"
             : qorai_stats::GetDateAsYMD(date_of_installation_);
}

std::string QoraiStatsUpdaterParams::GetReferralCodeParam() const {
  if (IsHeadlessOrAutomationMode() &&
      features::IsHeadlessClientRefcodeEnabled()) {
    return kHeadlessRefcode;
  }
  return referral_promo_code_.empty() ? "none" : referral_promo_code_;
}

std::string QoraiStatsUpdaterParams::GetAdsEnabledParam() const {
  return BooleanToString(stats_pref_service_->GetBoolean(
      qorai_ads::prefs::kEnabledForLastProfile));
}

std::string QoraiStatsUpdaterParams::GetProcessArchParam() const {
  if (arch_ == ProcessArch::kArchSkip) {
    return "";
  } else if (arch_ == ProcessArch::kArchMetal) {
    return base::SysInfo::OperatingSystemArchitecture();
  } else {
    return "virt";
  }
}

std::string QoraiStatsUpdaterParams::GetWalletEnabledParam() const {
  uint8_t usage_bitset = 0;
  if (wallet_last_unlocked_ > last_reported_wallet_unlock_) {
    usage_bitset = UsageBitfieldFromTimestamp(wallet_last_unlocked_,
                                              last_reported_wallet_unlock_);
  }
  return base::NumberToString(usage_bitset);
}

void QoraiStatsUpdaterParams::LoadPrefs() {
  last_check_ymd_ = stats_pref_service_->GetString(kLastCheckYMD);
  last_check_woy_ = stats_pref_service_->GetInteger(kLastCheckWOY);
  last_check_month_ = stats_pref_service_->GetInteger(kLastCheckMonth);
  first_check_made_ = stats_pref_service_->GetBoolean(kFirstCheckMade);
  week_of_installation_ = stats_pref_service_->GetString(kWeekOfInstallation);
  wallet_last_unlocked_ =
      stats_pref_service_->GetTime(kQoraiWalletLastUnlockTime);
  last_reported_wallet_unlock_ =
      stats_pref_service_->GetTime(kQoraiWalletPingReportedUnlockTime);
  if (week_of_installation_.empty())
    week_of_installation_ = GetLastMondayAsYMD();

  if (ShouldForceFirstRun()) {
    date_of_installation_ = GetCurrentTimeNow();
  } else {
    date_of_installation_ = GetFirstRunTime(stats_pref_service_);
    if (date_of_installation_.is_null()) {
      LOG(WARNING)
          << "Couldn't find the time of first run. This should only happen "
             "when running tests, but never in production code.";
    }
  }

  referral_promo_code_ = stats_pref_service_->GetString(kReferralPromoCode);
}

void QoraiStatsUpdaterParams::SavePrefs() {
  stats_pref_service_->SetString(kLastCheckYMD, ymd_);
  stats_pref_service_->SetInteger(kLastCheckWOY, woy_);
  stats_pref_service_->SetInteger(kLastCheckMonth, month_);
  stats_pref_service_->SetBoolean(kFirstCheckMade, true);
  stats_pref_service_->SetString(kWeekOfInstallation, week_of_installation_);

  last_reported_wallet_unlock_ = wallet_last_unlocked_;
  stats_pref_service_->SetTime(kQoraiWalletPingReportedUnlockTime,
                               last_reported_wallet_unlock_);
}

std::string QoraiStatsUpdaterParams::BooleanToString(bool bool_value) const {
  return bool_value ? "true" : "false";
}

std::string QoraiStatsUpdaterParams::GetCurrentDateAsYMD() const {
  return qorai_stats::GetDateAsYMD(GetCurrentTimeNow());
}

std::string QoraiStatsUpdaterParams::GetLastMondayAsYMD() const {
  base::Time now = GetCurrentTimeNow();
  base::Time last_monday = GetLastMondayTime(now);

  return qorai_stats::GetDateAsYMD(last_monday);
}

int QoraiStatsUpdaterParams::GetCurrentMonth() const {
  base::Time now = GetCurrentTimeNow();
  base::Time::Exploded exploded;
  now.LocalExplode(&exploded);
  return exploded.month;
}

int QoraiStatsUpdaterParams::GetCurrentISOWeekNumber() const {
  return GetIsoWeekNumber(GetCurrentTimeNow());
}

base::Time QoraiStatsUpdaterParams::GetReferenceTime() const {
  return GetCurrentTimeNow() - base::Days(1);
}

base::Time QoraiStatsUpdaterParams::GetCurrentTimeNow() const {
  return g_current_time.is_null() ? base::Time::Now() : g_current_time;
}

GURL QoraiStatsUpdaterParams::GetUpdateURL(
    const GURL& base_update_url,
    std::string_view platform_id,
    std::string_view channel_name,
    std::string_view full_qorai_version) const {
  GURL update_url(base_update_url);
  update_url = net::AppendQueryParameter(update_url, "platform", platform_id);
  update_url = net::AppendQueryParameter(update_url, "channel", channel_name);
  update_url =
      net::AppendQueryParameter(update_url, "version", full_qorai_version);
  update_url = net::AppendQueryParameter(update_url, "daily", GetDailyParam());
  update_url =
      net::AppendQueryParameter(update_url, "weekly", GetWeeklyParam());
  update_url =
      net::AppendQueryParameter(update_url, "monthly", GetMonthlyParam());
  update_url =
      net::AppendQueryParameter(update_url, "first", GetFirstCheckMadeParam());
  update_url = net::AppendQueryParameter(update_url, "woi",
                                         GetWeekOfInstallationParam());
  update_url = net::AppendQueryParameter(update_url, "dtoi",
                                         GetDateOfInstallationParam());
  update_url =
      net::AppendQueryParameter(update_url, "ref", GetReferralCodeParam());
  update_url =
      net::AppendQueryParameter(update_url, "adsEnabled", GetAdsEnabledParam());
  update_url =
      net::AppendQueryParameter(update_url, "arch", GetProcessArchParam());
  update_url =
      net::AppendQueryParameter(update_url, "wallet2", GetWalletEnabledParam());
  return update_url;
}

// static
bool QoraiStatsUpdaterParams::ShouldForceFirstRun() const {
  return g_force_first_run;
}

// static
void QoraiStatsUpdaterParams::SetCurrentTimeForTest(
    const base::Time& current_time) {
  g_current_time = current_time;
}

// static
void QoraiStatsUpdaterParams::SetFirstRunForTest(bool first_run) {
  g_force_first_run = first_run;
}

}  // namespace qorai_stats
