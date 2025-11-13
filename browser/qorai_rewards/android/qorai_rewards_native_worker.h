/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_REWARDS_ANDROID_QORAI_REWARDS_NATIVE_WORKER_H_
#define QORAI_BROWSER_QORAI_REWARDS_ANDROID_QORAI_REWARDS_NATIVE_WORKER_H_

#include <jni.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/android/jni_weak_ref.h"
#include "base/containers/flat_map.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_rewards/content/rewards_notification_service_observer.h"
#include "qorai/components/qorai_rewards/content/rewards_service_observer.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards {
class RewardsService;
}

namespace chrome {
namespace android {

typedef std::map<uint64_t, qorai_rewards::mojom::PublisherInfoPtr>
    PublishersInfoMap;

class QoraiRewardsNativeWorker
    : public qorai_rewards::RewardsServiceObserver,
      public qorai_rewards::RewardsNotificationServiceObserver {
 public:
  QoraiRewardsNativeWorker(JNIEnv* env,
                           const base::android::JavaRef<jobject>& obj);
  ~QoraiRewardsNativeWorker() override;

  void Destroy(JNIEnv* env);

  bool IsSupported(JNIEnv* env);
  bool IsSupportedSkipRegionCheck(JNIEnv* env);

  std::string StringifyResult(
      qorai_rewards::mojom::CreateRewardsWalletResult result);

  bool IsRewardsEnabled(JNIEnv* env);

  bool ShouldShowSelfCustodyInvite(JNIEnv* env);

  void CreateRewardsWallet(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& country_code);

  void GetRewardsParameters(JNIEnv* env);

  double GetVqorDeadline(JNIEnv* env);

  base::android::ScopedJavaLocalRef<jstring> GetPayoutStatus(JNIEnv* env);

  void GetUserType(JNIEnv* env);

  void FetchBalance(JNIEnv* env);

  void GetPublisherInfo(JNIEnv* env,
                        int tabId,
                        const base::android::JavaParamRef<jstring>& host);

  base::android::ScopedJavaLocalRef<jstring> GetWalletBalance(JNIEnv* env);

  base::android::ScopedJavaLocalRef<jstring> GetExternalWalletType(JNIEnv* env);

  void GetAdsAccountStatement(JNIEnv* env);

  bool CanConnectAccount(JNIEnv* env);

  base::android::ScopedJavaLocalRef<jdoubleArray> GetTipChoices(JNIEnv* env);

  double GetWalletRate(JNIEnv* env);

  base::android::ScopedJavaLocalRef<jstring> GetPublisherURL(JNIEnv* env,
                                                             uint64_t tabId);

  base::android::ScopedJavaLocalRef<jstring> GetPublisherFavIconURL(
      JNIEnv* env,
      uint64_t tabId);

  base::android::ScopedJavaLocalRef<jstring> GetPublisherName(JNIEnv* env,
                                                              uint64_t tabId);
  base::android::ScopedJavaLocalRef<jstring> GetCaptchaSolutionURL(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& paymentId,
      const base::android::JavaParamRef<jstring>& captchaId);
  base::android::ScopedJavaLocalRef<jstring> GetAttestationURL(JNIEnv* env);
  base::android::ScopedJavaLocalRef<jstring> GetAttestationURLWithPaymentId(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& paymentId);

  base::android::ScopedJavaLocalRef<jstring> GetPublisherId(JNIEnv* env,
                                                            uint64_t tabId);

  int GetPublisherPercent(JNIEnv* env, uint64_t tabId);

  bool GetPublisherExcluded(JNIEnv* env, uint64_t tabId);

  int GetPublisherStatus(JNIEnv* env, uint64_t tabId);

  void GetCurrentBalanceReport(JNIEnv* env);

  void RemovePublisherFromMap(JNIEnv* env, uint64_t tabId);

  void Donate(JNIEnv* env,
              const base::android::JavaParamRef<jstring>& publisher_key,
              double amount,
              bool recurring);

  void GetAllNotifications(JNIEnv* env);

  void DeleteNotification(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& notification_id);

  void GetRecurringDonations(JNIEnv* env);

  bool IsCurrentPublisherInRecurrentDonations(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& publisher);

  void GetReconcileStamp(JNIEnv* env);

  void ResetTheWholeState(JNIEnv* env);

  double GetPublisherRecurrentDonationAmount(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& publisher);

  void RemoveRecurring(JNIEnv* env,
                       const base::android::JavaParamRef<jstring>& publisher);

  int GetAdsPerHour(JNIEnv* env);

  void SetAdsPerHour(JNIEnv* env, jint value);

  void GetExternalWallet(JNIEnv* env);

  bool IsTermsOfServiceUpdateRequired(JNIEnv* env);

  void AcceptTermsOfServiceUpdate(JNIEnv* env);

  base::android::ScopedJavaLocalRef<jstring> GetCountryCode(JNIEnv* env);

  void GetAvailableCountries(JNIEnv* env);

  void GetPublisherBanner(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& publisher_key);

  void GetPublishersVisitedCount(JNIEnv* env);

  void OnGetPublishersVisitedCount(int count);

  void DisconnectWallet(JNIEnv* env);

  void RefreshPublisher(
      JNIEnv* env,
      const base::android::JavaParamRef<jstring>& publisher_key);

  void RecordPanelTrigger(JNIEnv* env);

  void OnCreateRewardsWallet(
      qorai_rewards::mojom::CreateRewardsWalletResult result);

  void OnCompleteReset(const bool success) override;

  void OnResetTheWholeState(const bool success);

  void OnGetGetReconcileStamp(uint64_t timestamp);

  void OnPanelPublisherInfo(qorai_rewards::RewardsService* rewards_service,
                            const qorai_rewards::mojom::Result result,
                            const qorai_rewards::mojom::PublisherInfo* info,
                            uint64_t tabId) override;

  void OnGetCurrentBalanceReport(
      qorai_rewards::RewardsService* rewards_service,
      const qorai_rewards::mojom::Result result,
      qorai_rewards::mojom::BalanceReportInfoPtr report);

  void OnGetRewardsParameters(
      qorai_rewards::RewardsService* rewards_service,
      qorai_rewards::mojom::RewardsParametersPtr parameters);

  void OnTermsOfServiceUpdateAccepted() override;

  void OnReconcileComplete(
      qorai_rewards::RewardsService* rewards_service,
      const qorai_rewards::mojom::Result result,
      const std::string& contribution_id,
      const double amount,
      const qorai_rewards::mojom::RewardsType type,
      const qorai_rewards::mojom::ContributionProcessor processor) override;

  void OnNotificationAdded(
      qorai_rewards::RewardsNotificationService* rewards_notification_service,
      const qorai_rewards::RewardsNotificationService::RewardsNotification&
          notification) override;

  void OnGetAllNotifications(
      qorai_rewards::RewardsNotificationService* rewards_notification_service,
      const qorai_rewards::RewardsNotificationService::RewardsNotificationsList&
          notifications_list) override;

  void OnNotificationDeleted(
      qorai_rewards::RewardsNotificationService* rewards_notification_service,
      const qorai_rewards::RewardsNotificationService::RewardsNotification&
          notification) override;

  void OnGetRecurringTips(
      std::vector<qorai_rewards::mojom::PublisherInfoPtr> list);

  void OnGetExternalWallet(qorai_rewards::mojom::ExternalWalletPtr wallet);

  void OnGetAvailableCountries(std::vector<std::string> countries);

  void onPublisherBanner(qorai_rewards::mojom::PublisherBannerPtr wallet);

  void OnSendContribution(bool result);

  void OnExternalWalletConnected() override;

  void OnExternalWalletLoggedOut() override;

  void OnExternalWalletReconnected() override;

  void OnRefreshPublisher(const qorai_rewards::mojom::PublisherStatus status,
                          const std::string& publisher_key);

 private:
  void OnGetUserType(const qorai_rewards::mojom::UserType user_type);

  void OnBalance(qorai_rewards::mojom::BalancePtr balance);

  void OnGetAdsAccountStatement(qorai_ads::mojom::StatementInfoPtr statement);

  JavaObjectWeakGlobalRef weak_java_qorai_rewards_native_worker_;
  raw_ptr<qorai_rewards::RewardsService> qorai_rewards_service_ = nullptr;
  qorai_rewards::mojom::RewardsParametersPtr parameters_;
  qorai_rewards::mojom::Balance balance_;
  PublishersInfoMap map_publishers_info_;
  std::map<std::string, qorai_rewards::mojom::PublisherInfoPtr>
      map_recurrent_publishers_;
  std::map<std::string, std::string> addresses_;
  base::ScopedObservation<qorai_rewards::RewardsService,
                          qorai_rewards::RewardsServiceObserver>
      rewards_service_observation_{this};
  base::ScopedObservation<qorai_rewards::RewardsNotificationService,
                          qorai_rewards::RewardsNotificationServiceObserver>
      rewards_notification_service_observation_{this};
  base::WeakPtrFactory<QoraiRewardsNativeWorker> weak_factory_;
};

}  // namespace android
}  // namespace chrome

#endif  // QORAI_BROWSER_QORAI_REWARDS_ANDROID_QORAI_REWARDS_NATIVE_WORKER_H_
