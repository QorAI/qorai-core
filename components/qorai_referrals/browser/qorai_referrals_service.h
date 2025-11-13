/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REFERRALS_BROWSER_QORAI_REFERRALS_SERVICE_H_
#define QORAI_COMPONENTS_QORAI_REFERRALS_BROWSER_QORAI_REFERRALS_SERVICE_H_

#include <memory>
#include <string>
#include <utility>

#include "base/files/file_path.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/task/sequenced_task_runner.h"
#include "base/timer/timer.h"
#include "build/build_config.h"

#if BUILDFLAG(IS_ANDROID)
#include "qorai/components/qorai_referrals/browser/android_qorai_referrer.h"
#endif

class PrefRegistrySimple;
class PrefService;

namespace network {
namespace mojom {
class URLLoaderFactory;
}  // namespace mojom
class SimpleURLLoader;
}  // namespace network

namespace qorai {

class QoraiReferralsService {
 public:
  class Delegate {
   public:
    Delegate() = default;
    virtual ~Delegate() = default;

    virtual void OnInitialized() = 0;
    virtual base::FilePath GetUserDataDirectory() = 0;
    virtual network::mojom::URLLoaderFactory* GetURLLoaderFactory() = 0;

#if !BUILDFLAG(IS_ANDROID)
    virtual base::OnceCallback<base::Time()>
    GetFirstRunSentinelCreationTimeCallback() = 0;
#endif
  };

  QoraiReferralsService(PrefService* pref_service,
                        const std::string& platform,
                        const std::string& api_key);
  QoraiReferralsService(const QoraiReferralsService&) = delete;
  QoraiReferralsService& operator=(const QoraiReferralsService&) = delete;
  ~QoraiReferralsService();

  void set_delegate(std::unique_ptr<Delegate> delegate) {
    delegate_ = std::move(delegate);
  }

  void Start();
  void Stop();

  using ReferralInitializedCallback =
      base::RepeatingCallback<void(const std::string& download_id)>;

  static void SetReferralInitializedCallbackForTesting(
      ReferralInitializedCallback* referral_initialized_callback);

  static void SetPromoFilePathForTesting(const base::FilePath& path);

  static bool IsDefaultReferralCode(const std::string& code);

 private:
  void GetFirstRunTime();
  void SetFirstRunTime(const base::Time& first_run_timestamp);
  void PerformFinalizationChecks();
  base::FilePath GetPromoCodeFileName() const;
  void MaybeCheckForReferralFinalization();
  void MaybeDeletePromoCodePref() const;
  void InitReferral();
  std::string BuildReferralInitPayload() const;
  std::string BuildReferralFinalizationCheckPayload() const;
  void CheckForReferralFinalization();

  // Invoked from RepeatingTimer when finalization checks timer
  // fires.
  void OnFinalizationChecksTimerFired();

  // Invoked from SimpleURLLoader after referral init load
  // completes.
  void OnReferralInitLoadComplete(std::unique_ptr<std::string> response_body);

  // Invoked from SimpleURLLoader after referral finalization check
  // load completes.
  void OnReferralFinalizationCheckLoadComplete(
      std::unique_ptr<std::string> response_body);

  // Invoked after reading contents of promo code file.
  void OnReadPromoCodeComplete(const std::string& promo_code);

#if BUILDFLAG(IS_ANDROID)
  void InitAndroidReferrer();
  void OnAndroidQoraiReferrerReady();
  android_qorai_referrer::QoraiReferrer android_qorai_referrer_;
#endif

  bool initialized_ = false;
  base::Time first_run_timestamp_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  std::unique_ptr<network::SimpleURLLoader> referral_init_loader_;
  std::unique_ptr<network::SimpleURLLoader> referral_finalization_check_loader_;
  std::unique_ptr<base::OneShotTimer> initialization_timer_;
  std::unique_ptr<base::RepeatingTimer> finalization_checks_timer_;
  ReferralInitializedCallback referral_initialized_callback_;
  std::unique_ptr<Delegate> delegate_;
  raw_ptr<PrefService> pref_service_ = nullptr;
  const std::string api_key_;
  const std::string platform_;
  std::string promo_code_;

  base::WeakPtrFactory<QoraiReferralsService> weak_factory_{this};
};

// Registers the preferences used by QoraiReferralsService
void RegisterPrefsForQoraiReferralsService(PrefRegistrySimple* registry);

}  // namespace qorai

#endif  // QORAI_COMPONENTS_QORAI_REFERRALS_BROWSER_QORAI_REFERRALS_SERVICE_H_
