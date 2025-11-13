/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_rewards/android/qorai_rewards_native_worker.h"

#include <algorithm>
#include <utility>

#include "base/android/jni_android.h"
#include "base/android/jni_array.h"
#include "base/android/jni_string.h"
#include "base/containers/contains.h"
#include "base/containers/flat_map.h"
#include "base/feature_list.h"
#include "base/json/json_writer.h"
#include "base/time/time.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/components/qorai_adaptive_captcha/qorai_adaptive_captcha_service.h"
#include "qorai/components/qorai_adaptive_captcha/server_util.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_rewards/content/rewards_p3a.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_rewards/core/engine/global_constants.h"
#include "qorai/components/qorai_rewards/core/features.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_rewards/core/rewards_util.h"
#include "chrome/android/chrome_jni_headers/QoraiRewardsNativeWorker_jni.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/url_data_source.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

#define DEFAULT_ADS_PER_HOUR 2

namespace chrome {
namespace android {

QoraiRewardsNativeWorker::QoraiRewardsNativeWorker(JNIEnv* env,
    const base::android::JavaRef<jobject>& obj):
    weak_java_qorai_rewards_native_worker_(env, obj),
    weak_factory_(this) {
  Java_QoraiRewardsNativeWorker_setNativePtr(env, obj,
    reinterpret_cast<intptr_t>(this));

  qorai_rewards_service_ = qorai_rewards::RewardsServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
  if (qorai_rewards_service_) {
    rewards_service_observation_.Observe(qorai_rewards_service_);

    if (auto* notification_service =
            qorai_rewards_service_->GetNotificationService()) {
      rewards_notification_service_observation_.Observe(notification_service);
    }
  }
}

QoraiRewardsNativeWorker::~QoraiRewardsNativeWorker() {
}

void QoraiRewardsNativeWorker::Destroy(JNIEnv* env) {
  delete this;
}

bool QoraiRewardsNativeWorker::IsSupported(JNIEnv* env) {
  return qorai_rewards::IsSupported(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile()->GetPrefs(),
      qorai_rewards::IsSupportedOptions::kNone);
}

bool QoraiRewardsNativeWorker::IsSupportedSkipRegionCheck(JNIEnv* env) {
  return qorai_rewards::IsSupported(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile()->GetPrefs(),
      qorai_rewards::IsSupportedOptions::kSkipRegionCheck);
}

std::string QoraiRewardsNativeWorker::StringifyResult(
    qorai_rewards::mojom::CreateRewardsWalletResult result) {
  switch (result) {
    case qorai_rewards::mojom::CreateRewardsWalletResult::kSuccess:
      return "success";
    case qorai_rewards::mojom::CreateRewardsWalletResult::
        kWalletGenerationDisabled:
      return "wallet-generation-disabled";
    case qorai_rewards::mojom::CreateRewardsWalletResult::
        kGeoCountryAlreadyDeclared:
      return "country-already-declared";
    case qorai_rewards::mojom::CreateRewardsWalletResult::kUnexpected:
      return "unexpected-error";
  }
}

bool QoraiRewardsNativeWorker::IsRewardsEnabled(JNIEnv* env) {
  return ProfileManager::GetActiveUserProfile()
      ->GetOriginalProfile()
      ->GetPrefs()
      ->GetBoolean(qorai_rewards::prefs::kEnabled);
}

bool QoraiRewardsNativeWorker::ShouldShowSelfCustodyInvite(JNIEnv* env) {
  bool is_self_custody_invite_dismissed =
      ProfileManager::GetActiveUserProfile()
          ->GetOriginalProfile()
          ->GetPrefs()
          ->GetBoolean(qorai_rewards::prefs::kSelfCustodyInviteDismissed);

  if (is_self_custody_invite_dismissed) {
    return false;
  }

  std::string country_code = qorai_rewards_service_->GetCountryCode();
  const std::vector<std::string> providers =
      qorai_rewards_service_->GetExternalWalletProviders();
  if (!base::Contains(providers,
                      qorai_rewards::internal::constant::kWalletSolana)) {
    return false;
  }

  const auto& regions = parameters_->wallet_provider_regions.at(
      qorai_rewards::internal::constant::kWalletSolana);
  if (!regions) {
    return true;
  }

  const auto& [allow, block] = *regions;
  if (allow.empty() && block.empty()) {
    return true;
  }

  return base::Contains(allow, country_code) ||
         (!block.empty() && !base::Contains(block, country_code));
}

void QoraiRewardsNativeWorker::CreateRewardsWallet(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& country_code) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->CreateRewardsWallet(
        base::android::ConvertJavaStringToUTF8(env, country_code),
        base::BindOnce(&QoraiRewardsNativeWorker::OnCreateRewardsWallet,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnCreateRewardsWallet(
    qorai_rewards::mojom::CreateRewardsWalletResult result) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onCreateRewardsWallet(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, StringifyResult(result)));
}

void QoraiRewardsNativeWorker::GetRewardsParameters(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetRewardsParameters(
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetRewardsParameters,
                       weak_factory_.GetWeakPtr(), qorai_rewards_service_));
  }
}

void QoraiRewardsNativeWorker::OnGetRewardsParameters(
    qorai_rewards::RewardsService* rewards_service,
    qorai_rewards::mojom::RewardsParametersPtr parameters) {
  if (parameters) {
    parameters_ = std::move(parameters);
  }

  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onRewardsParameters(
      env, weak_java_qorai_rewards_native_worker_.get(env));
}

void QoraiRewardsNativeWorker::OnTermsOfServiceUpdateAccepted() {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onTermsOfServiceUpdateAccepted(
      env, weak_java_qorai_rewards_native_worker_.get(env));
}

double QoraiRewardsNativeWorker::GetVqorDeadline(JNIEnv* env) {
  if (parameters_) {
    if (!parameters_->vqor_deadline.is_null()) {
      return floor(parameters_->vqor_deadline.InSecondsFSinceUnixEpoch() *
                   base::Time::kMillisecondsPerSecond);
    }
  }
  return 0.0;
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetPayoutStatus(JNIEnv* env) {
  std::string wallet_type;
  std::string payout_status;
  if (qorai_rewards_service_) {
    wallet_type = qorai_rewards_service_->GetExternalWalletType();
    if (parameters_) {
      if (!parameters_->payout_status.empty()) {
        payout_status = parameters_->payout_status.at(wallet_type);
      }
    }
  }
  return base::android::ConvertUTF8ToJavaString(env, payout_status);
}

void QoraiRewardsNativeWorker::GetUserType(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetUserType(base::BindOnce(
        &QoraiRewardsNativeWorker::OnGetUserType, weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnGetUserType(
    const qorai_rewards::mojom::UserType user_type) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onGetUserType(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      static_cast<int>(user_type));
}

void QoraiRewardsNativeWorker::FetchBalance(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->FetchBalance(base::BindOnce(
        &QoraiRewardsNativeWorker::OnBalance, weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnBalance(
    qorai_rewards::mojom::BalancePtr balance) {
  if (balance) {
    balance_ = *balance;
  }

  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onBalance(
      env, weak_java_qorai_rewards_native_worker_.get(env), !!balance);
}

void QoraiRewardsNativeWorker::GetPublisherInfo(
    JNIEnv* env,
    int tabId,
    const base::android::JavaParamRef<jstring>& host) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->NotifyPublisherPageVisit(
        tabId, base::android::ConvertJavaStringToUTF8(env, host), "", "");
  }
}

void QoraiRewardsNativeWorker::OnPanelPublisherInfo(
    qorai_rewards::RewardsService* rewards_service,
    const qorai_rewards::mojom::Result result,
    const qorai_rewards::mojom::PublisherInfo* info,
    uint64_t tabId) {
  if (!info) {
    return;
  }
  qorai_rewards::mojom::PublisherInfoPtr pi = info->Clone();
  map_publishers_info_[tabId] = std::move(pi);
  JNIEnv* env = base::android::AttachCurrentThread();
  base::android::ScopedJavaLocalRef<jstring> res =
      base::android::ConvertUTF8ToJavaString(env, info->id);
  Java_QoraiRewardsNativeWorker_onPublisherInfo(
      env, weak_java_qorai_rewards_native_worker_.get(env), tabId, res);
}

void QoraiRewardsNativeWorker::OnReconcileComplete(
    qorai_rewards::RewardsService* rewards_service,
    const qorai_rewards::mojom::Result result,
    const std::string& contribution_id,
    const double amount,
    const qorai_rewards::mojom::RewardsType type,
    const qorai_rewards::mojom::ContributionProcessor processor) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onReconcileComplete(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      static_cast<int>(result), static_cast<int>(type), amount);
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetPublisherURL(JNIEnv* env, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env, iter->second->url);
  }

  return res;
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetPublisherFavIconURL(JNIEnv* env, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env,
      iter->second->favicon_url);
  }

  return res;
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetCaptchaSolutionURL(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& paymentId,
    const base::android::JavaParamRef<jstring>& captchaId) {
  const std::string path =
      absl::StrFormat("/v3/captcha/solution/%s/%s",
                      base::android::ConvertJavaStringToUTF8(env, paymentId),
                      base::android::ConvertJavaStringToUTF8(env, captchaId));
  std::string captcha_solution_url =
      qorai_adaptive_captcha::ServerUtil::GetInstance()->GetServerUrl(path);

  return base::android::ConvertUTF8ToJavaString(env, captcha_solution_url);
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetAttestationURL(JNIEnv* env) {
  const std::string path = "/v1/attestations/android";
  std::string captcha_solution_url =
      qorai_adaptive_captcha::ServerUtil::GetInstance()->GetServerUrl(path);

  return base::android::ConvertUTF8ToJavaString(env, captcha_solution_url);
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetAttestationURLWithPaymentId(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& paymentId) {
  const std::string path =
      base::StrCat({"/v1/attestations/android/",
                    base::android::ConvertJavaStringToUTF8(env, paymentId)});
  std::string captcha_solution_url =
      qorai_adaptive_captcha::ServerUtil::GetInstance()->GetServerUrl(path);

  return base::android::ConvertUTF8ToJavaString(env, captcha_solution_url);
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetPublisherName(JNIEnv* env, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env, iter->second->name);
  }

  return res;
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetPublisherId(JNIEnv* env, uint64_t tabId) {
  base::android::ScopedJavaLocalRef<jstring> res =
    base::android::ConvertUTF8ToJavaString(env, "");

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = base::android::ConvertUTF8ToJavaString(env, iter->second->id);
  }

  return res;
}

int QoraiRewardsNativeWorker::GetPublisherPercent(JNIEnv* env, uint64_t tabId) {
  int res = 0;

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = iter->second->percent;
  }

  return res;
}

bool QoraiRewardsNativeWorker::GetPublisherExcluded(JNIEnv* env,
                                                    uint64_t tabId) {
  bool res = false;

  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    res = iter->second->excluded ==
          qorai_rewards::mojom::PublisherExclude::EXCLUDED;
  }

  return res;
}

int QoraiRewardsNativeWorker::GetPublisherStatus(JNIEnv* env, uint64_t tabId) {
  int res =
      static_cast<int>(qorai_rewards::mojom::PublisherStatus::NOT_VERIFIED);
  PublishersInfoMap::const_iterator iter = map_publishers_info_.find(tabId);
  if (iter != map_publishers_info_.end()) {
    res = static_cast<int>(iter->second->status);
  }
  return res;
}

void QoraiRewardsNativeWorker::RemovePublisherFromMap(JNIEnv* env,
                                                      uint64_t tabId) {
  PublishersInfoMap::const_iterator iter(map_publishers_info_.find(tabId));
  if (iter != map_publishers_info_.end()) {
    map_publishers_info_.erase(iter);
  }
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetWalletBalance(JNIEnv* env) {
  base::Value::Dict root;
  root.Set("total", balance_.total);

  base::Value::Dict json_wallets;
  for (const auto & item : balance_.wallets) {
    json_wallets.Set(item.first, item.second);
  }
  root.SetByDottedPath("wallets", std::move(json_wallets));

  return base::android::ConvertUTF8ToJavaString(
      env, base::WriteJson(root).value_or(""));
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetExternalWalletType(JNIEnv* env) {
  std::string wallet_type;
  if (qorai_rewards_service_) {
    wallet_type = qorai_rewards_service_->GetExternalWalletType();
  }

  return base::android::ConvertUTF8ToJavaString(env, wallet_type);
}

void QoraiRewardsNativeWorker::GetAdsAccountStatement(JNIEnv* env) {
  auto* ads_service = qorai_ads::AdsServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
  if (!ads_service) {
    return;
  }
  ads_service->GetStatementOfAccounts(
      base::BindOnce(&QoraiRewardsNativeWorker::OnGetAdsAccountStatement,
                     weak_factory_.GetWeakPtr()));
}

void QoraiRewardsNativeWorker::OnGetAdsAccountStatement(
    qorai_ads::mojom::StatementInfoPtr statement) {
  JNIEnv* env = base::android::AttachCurrentThread();
  if (!statement) {
    Java_QoraiRewardsNativeWorker_onGetAdsAccountStatement(
        env, weak_java_qorai_rewards_native_worker_.get(env),
        /* success */ false, 0.0, 0, 0.0, 0.0, 0.0, 0.0);
    return;
  }

  Java_QoraiRewardsNativeWorker_onGetAdsAccountStatement(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      /* success */ true,
      statement->next_payment_date.InSecondsFSinceUnixEpoch() * 1000,
      statement->ads_received_this_month, statement->min_earnings_this_month,
      statement->max_earnings_this_month,
      statement->min_earnings_previous_month,
      statement->max_earnings_previous_month);
}

bool QoraiRewardsNativeWorker::CanConnectAccount(JNIEnv* env) {
  if (!parameters_ || !qorai_rewards_service_) {
    return true;
  }
  std::string country_code = qorai_rewards_service_->GetCountryCode();
  return std::ranges::any_of(
      qorai_rewards_service_->GetExternalWalletProviders(),
      [this, &country_code](const std::string& provider) {
        if (!parameters_->wallet_provider_regions.count(provider)) {
          return true;
        }

        const auto& regions = parameters_->wallet_provider_regions.at(provider);
        if (!regions) {
          return true;
        }

        const auto& [allow, block] = *regions;
        if (allow.empty() && block.empty()) {
          return true;
        }

        return base::Contains(allow, country_code) ||
               (!block.empty() && !base::Contains(block, country_code));
      });
}

base::android::ScopedJavaLocalRef<jdoubleArray>
QoraiRewardsNativeWorker::GetTipChoices(JNIEnv* env) {
  return base::android::ToJavaDoubleArray(
      env, parameters_ ? parameters_->tip_choices : std::vector<double>());
}

double QoraiRewardsNativeWorker::GetWalletRate(JNIEnv* env) {
  return parameters_ ? parameters_->rate : 0.0;
}

void QoraiRewardsNativeWorker::GetCurrentBalanceReport(JNIEnv* env) {
  if (qorai_rewards_service_) {
    auto now = base::Time::Now();
    base::Time::Exploded exploded;
    now.LocalExplode(&exploded);

    qorai_rewards_service_->GetBalanceReport(
        exploded.month, exploded.year,
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetCurrentBalanceReport,
                       weak_factory_.GetWeakPtr(), qorai_rewards_service_));
  }
}

void QoraiRewardsNativeWorker::OnGetCurrentBalanceReport(
    qorai_rewards::RewardsService* rewards_service,
    const qorai_rewards::mojom::Result result,
    qorai_rewards::mojom::BalanceReportInfoPtr report) {
  base::android::ScopedJavaLocalRef<jdoubleArray> java_array;
  JNIEnv* env = base::android::AttachCurrentThread();
  if (report) {
    std::vector<double> values;
    values.push_back(report->earning_from_ads);
    values.push_back(report->auto_contribute);
    values.push_back(report->recurring_donation);
    values.push_back(report->one_time_donation);
    java_array = base::android::ToJavaDoubleArray(env, values);
  }
  Java_QoraiRewardsNativeWorker_onGetCurrentBalanceReport(
      env, weak_java_qorai_rewards_native_worker_.get(env), java_array);
}

void QoraiRewardsNativeWorker::Donate(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& publisher_key,
    double amount,
    bool recurring) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->SendContribution(
        base::android::ConvertJavaStringToUTF8(env, publisher_key), amount,
        recurring,
        base::BindOnce(&QoraiRewardsNativeWorker::OnSendContribution,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnSendContribution(bool result) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onSendContribution(
      env, weak_java_qorai_rewards_native_worker_.get(env), result);
}

void QoraiRewardsNativeWorker::GetAllNotifications(JNIEnv* env) {
  if (rewards_notification_service_observation_.IsObserving()) {
    rewards_notification_service_observation_.GetSource()->GetNotifications();
  }
}

void QoraiRewardsNativeWorker::DeleteNotification(JNIEnv* env,
        const base::android::JavaParamRef<jstring>& notification_id) {
  if (rewards_notification_service_observation_.IsObserving()) {
    rewards_notification_service_observation_.GetSource()->DeleteNotification(
        base::android::ConvertJavaStringToUTF8(env, notification_id));
  }
}

void QoraiRewardsNativeWorker::GetRecurringDonations(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetRecurringTips(
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetRecurringTips,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnGetRecurringTips(
    std::vector<qorai_rewards::mojom::PublisherInfoPtr> list) {
  map_recurrent_publishers_.clear();
  for (const auto& item : list) {
    map_recurrent_publishers_[item->id] = item->Clone();
  }

  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onRecurringDonationUpdated(
      env, weak_java_qorai_rewards_native_worker_.get(env));
}

bool QoraiRewardsNativeWorker::IsCurrentPublisherInRecurrentDonations(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& publisher) {
  return map_recurrent_publishers_.find(
    base::android::ConvertJavaStringToUTF8(env, publisher)) !=
      map_recurrent_publishers_.end();
}

void QoraiRewardsNativeWorker::GetReconcileStamp(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetReconcileStamp(
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetGetReconcileStamp,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::ResetTheWholeState(JNIEnv* env) {
  if (!qorai_rewards_service_) {
    OnResetTheWholeState(false);
    return;
  }
  qorai_rewards_service_->CompleteReset(
      base::BindOnce(&QoraiRewardsNativeWorker::OnResetTheWholeState,
                     weak_factory_.GetWeakPtr()));
}

void QoraiRewardsNativeWorker::OnCompleteReset(const bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_QoraiRewardsNativeWorker_onCompleteReset(
      env, weak_java_qorai_rewards_native_worker_.get(env), success);
}

void QoraiRewardsNativeWorker::OnResetTheWholeState(const bool success) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_QoraiRewardsNativeWorker_onResetTheWholeState(
      env, weak_java_qorai_rewards_native_worker_.get(env), success);
}

double QoraiRewardsNativeWorker::GetPublisherRecurrentDonationAmount(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& publisher) {
  double amount(0.0);
  auto it = map_recurrent_publishers_.find(
    base::android::ConvertJavaStringToUTF8(env, publisher));

  if (it != map_recurrent_publishers_.end()) {
    amount = it->second->weight;
  }
  return  amount;
}

void QoraiRewardsNativeWorker::RemoveRecurring(JNIEnv* env,
    const base::android::JavaParamRef<jstring>& publisher) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->RemoveRecurringTip(
        base::android::ConvertJavaStringToUTF8(env, publisher));
    auto it = map_recurrent_publishers_.find(
        base::android::ConvertJavaStringToUTF8(env, publisher));

    if (it != map_recurrent_publishers_.end()) {
      map_recurrent_publishers_.erase(it);
    }
  }
}

void QoraiRewardsNativeWorker::OnGetGetReconcileStamp(uint64_t timestamp) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_QoraiRewardsNativeWorker_onGetReconcileStamp(
      env, weak_java_qorai_rewards_native_worker_.get(env), timestamp);
}

void QoraiRewardsNativeWorker::OnNotificationAdded(
    qorai_rewards::RewardsNotificationService* rewards_notification_service,
    const qorai_rewards::RewardsNotificationService::RewardsNotification&
      notification) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_QoraiRewardsNativeWorker_onNotificationAdded(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, notification.id_),
      notification.type_, notification.timestamp_,
      base::android::ToJavaArrayOfStrings(env, notification.args_));
}

void QoraiRewardsNativeWorker::OnGetAllNotifications(
    qorai_rewards::RewardsNotificationService* rewards_notification_service,
    const qorai_rewards::RewardsNotificationService::RewardsNotificationsList&
      notifications_list) {
  JNIEnv* env = base::android::AttachCurrentThread();

  // Notify about notifications count
  Java_QoraiRewardsNativeWorker_onNotificationsCount(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      notifications_list.size());

  qorai_rewards::RewardsNotificationService::RewardsNotificationsList::
    const_iterator iter =
      std::max_element(notifications_list.begin(), notifications_list.end(),
        [](const qorai_rewards::RewardsNotificationService::
            RewardsNotification& notification_a,
          const qorai_rewards::RewardsNotificationService::
            RewardsNotification& notification_b) {
        return notification_a.timestamp_ > notification_b.timestamp_;
      });

  if (iter != notifications_list.end()) {
    Java_QoraiRewardsNativeWorker_onGetLatestNotification(
        env, weak_java_qorai_rewards_native_worker_.get(env),
        base::android::ConvertUTF8ToJavaString(env, iter->id_), iter->type_,
        iter->timestamp_,
        base::android::ToJavaArrayOfStrings(env, iter->args_));
  }
}

void QoraiRewardsNativeWorker::OnNotificationDeleted(
      qorai_rewards::RewardsNotificationService* rewards_notification_service,
      const qorai_rewards::RewardsNotificationService::RewardsNotification&
        notification) {
  JNIEnv* env = base::android::AttachCurrentThread();

  Java_QoraiRewardsNativeWorker_onNotificationDeleted(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, notification.id_));
}

int QoraiRewardsNativeWorker::GetAdsPerHour(JNIEnv* env) {
  auto* ads_service_ = qorai_ads::AdsServiceFactory::GetForProfile(
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile());
  if (!ads_service_) {
    return DEFAULT_ADS_PER_HOUR;
  }
  return ads_service_->GetMaximumNotificationAdsPerHour();
}

void QoraiRewardsNativeWorker::SetAdsPerHour(JNIEnv* env, jint value) {
  ProfileManager::GetActiveUserProfile()
      ->GetOriginalProfile()
      ->GetPrefs()
      ->SetInt64(qorai_ads::prefs::kMaximumNotificationAdsPerHour,
                 static_cast<int64_t>(value));
}

void QoraiRewardsNativeWorker::GetExternalWallet(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetExternalWallet(
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetExternalWallet,
                       weak_factory_.GetWeakPtr()));
  }
}

bool QoraiRewardsNativeWorker::IsTermsOfServiceUpdateRequired(JNIEnv* env) {
  if (!qorai_rewards_service_) {
    return false;
  }
  return qorai_rewards_service_->IsTermsOfServiceUpdateRequired();
}

void QoraiRewardsNativeWorker::AcceptTermsOfServiceUpdate(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->AcceptTermsOfServiceUpdate();
  }
}

base::android::ScopedJavaLocalRef<jstring>
QoraiRewardsNativeWorker::GetCountryCode(JNIEnv* env) {
  std::string country_code;
  if (qorai_rewards_service_) {
    country_code = qorai_rewards_service_->GetCountryCode();
  }

  return base::android::ConvertUTF8ToJavaString(env, country_code);
}

void QoraiRewardsNativeWorker::GetAvailableCountries(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetAvailableCountries(
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetAvailableCountries,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnGetAvailableCountries(
    std::vector<std::string> countries) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onGetAvailableCountries(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      base::android::ToJavaArrayOfStrings(env, countries));
}

void QoraiRewardsNativeWorker::GetPublishersVisitedCount(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetPublishersVisitedCount(
        base::BindOnce(&QoraiRewardsNativeWorker::OnGetPublishersVisitedCount,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::OnGetPublishersVisitedCount(int count) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onGetPublishersVisitedCount(
      env, weak_java_qorai_rewards_native_worker_.get(env), count);
}

void QoraiRewardsNativeWorker::GetPublisherBanner(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& publisher_key) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetPublisherBanner(
        base::android::ConvertJavaStringToUTF8(env, publisher_key),
        base::BindOnce(&QoraiRewardsNativeWorker::onPublisherBanner,
                       weak_factory_.GetWeakPtr()));
  }
}

void QoraiRewardsNativeWorker::onPublisherBanner(
    qorai_rewards::mojom::PublisherBannerPtr banner) {
  std::string json_banner_info;
  if (!banner) {
    json_banner_info = "";
  } else {
    base::Value::Dict dict;
    dict.Set("publisher_key", banner->publisher_key);
    dict.Set("title", banner->title);

    dict.Set("name", banner->name);
    dict.Set("description", banner->description);
    dict.Set("background", banner->background);
    dict.Set("logo", banner->logo);
    dict.Set("provider", banner->provider);
    dict.Set("web3_url", banner->web3_url);

    base::Value::Dict links;
    for (auto const& link : banner->links) {
      links.Set(link.first, link.second);
    }
    dict.Set("links", std::move(links));

    dict.Set("status", static_cast<int32_t>(banner->status));
    json_banner_info = base::WriteJson(dict).value_or("");
  }
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onPublisherBanner(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, json_banner_info));
}

void QoraiRewardsNativeWorker::OnGetExternalWallet(
    qorai_rewards::mojom::ExternalWalletPtr wallet) {
  std::string json_wallet;
  if (!wallet) {
    // If the user does not have an external wallet, expose a default/empty
    // wallet for backward compatibility with Android code that expects an
    // external wallet structure with a NOT_CONNECTED status.
    base::Value::Dict dict;
    dict.Set("token", "");
    dict.Set("address", "");
    dict.Set("status", static_cast<int32_t>(
                           qorai_rewards::mojom::WalletStatus::kNotConnected));
    dict.Set("type", qorai_rewards_service_->GetExternalWalletType());
    dict.Set("user_name", "");
    dict.Set("account_url", "");
    json_wallet = base::WriteJson(dict).value_or("");
  } else {
    base::Value::Dict dict;
    dict.Set("token", wallet->token);
    dict.Set("address", wallet->address);

    // enum class WalletStatus : int32_t
    dict.Set("status", static_cast<int32_t>(wallet->status));
    dict.Set("type", wallet->type);
    dict.Set("user_name", wallet->user_name);
    dict.Set("account_url", wallet->account_url);
    json_wallet = base::WriteJson(dict).value_or("");
  }
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onGetExternalWallet(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      base::android::ConvertUTF8ToJavaString(env, json_wallet));
}

void QoraiRewardsNativeWorker::DisconnectWallet(JNIEnv* env) {
  // TODO(zenparsing): Remove disconnect ability from Android UI.
}

void QoraiRewardsNativeWorker::OnExternalWalletConnected() {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onExternalWalletConnected(
      env, weak_java_qorai_rewards_native_worker_.get(env));
}

void QoraiRewardsNativeWorker::OnExternalWalletLoggedOut() {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onExternalWalletLoggedOut(
      env, weak_java_qorai_rewards_native_worker_.get(env));
}

void QoraiRewardsNativeWorker::OnExternalWalletReconnected() {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onExternalWalletReconnected(
      env, weak_java_qorai_rewards_native_worker_.get(env));
}

void QoraiRewardsNativeWorker::RefreshPublisher(
    JNIEnv* env,
    const base::android::JavaParamRef<jstring>& publisher_key) {
  if (!qorai_rewards_service_) {
    return;
  }
  qorai_rewards_service_->RefreshPublisher(
      base::android::ConvertJavaStringToUTF8(env, publisher_key),
      base::BindOnce(&QoraiRewardsNativeWorker::OnRefreshPublisher,
                     weak_factory_.GetWeakPtr()));
}

void QoraiRewardsNativeWorker::OnRefreshPublisher(
    const qorai_rewards::mojom::PublisherStatus status,
    const std::string& publisher_key) {
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_QoraiRewardsNativeWorker_onRefreshPublisher(
      env, weak_java_qorai_rewards_native_worker_.get(env),
      static_cast<int>(status),
      base::android::ConvertUTF8ToJavaString(env, publisher_key));
}

void QoraiRewardsNativeWorker::RecordPanelTrigger(JNIEnv* env) {
  if (qorai_rewards_service_) {
    qorai_rewards_service_->GetP3AConversionMonitor()->RecordPanelTrigger(
        qorai_rewards::p3a::PanelTrigger::kToolbarButton);
  }
}

static void JNI_QoraiRewardsNativeWorker_Init(
    JNIEnv* env,
    const base::android::JavaParamRef<jobject>& jcaller) {
  new QoraiRewardsNativeWorker(env, jcaller);
}

}  // namespace android
}  // namespace chrome
