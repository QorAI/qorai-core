/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_SERVICE_H_
#define QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_SERVICE_H_

#include <memory>
#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/api_request_helper/api_request_helper.h"
#include "qorai/components/qorai_adaptive_captcha/qorai_adaptive_captcha_delegate.h"
#include "qorai/components/qorai_adaptive_captcha/get_adaptive_captcha_challenge.h"
#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "qorai/components/qorai_rewards/content/rewards_service_observer.h"
#include "components/keyed_service/core/keyed_service.h"

namespace network {
class SharedURLLoaderFactory;
}  // namespace network

class PrefRegistrySimple;
class PrefService;

namespace qorai_adaptive_captcha {
// This manages the adaptive captcha functionality. Adaptive captchas provide a
// mechanism for the server to provide new types of captchas without requiring
// client changes.
class QoraiAdaptiveCaptchaService
    : public KeyedService,
      public qorai_rewards::RewardsServiceObserver {
 public:
  QoraiAdaptiveCaptchaService(
      PrefService* prefs,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
      qorai_rewards::RewardsService* rewards_service,
      std::unique_ptr<QoraiAdaptiveCaptchaDelegate> delegate);
  ~QoraiAdaptiveCaptchaService() override;

  QoraiAdaptiveCaptchaService(const QoraiAdaptiveCaptchaService&) = delete;
  QoraiAdaptiveCaptchaService& operator=(const QoraiAdaptiveCaptchaService&) =
      delete;

  static void RegisterProfilePrefs(PrefRegistrySimple* registry);

  // Retrieves the captcha scheduled for the given |payment_id|, if
  // any. If there is a scheduled captcha that the user must solve in
  // order to proceed, |callback| will return the captcha id;
  // otherwise, |callback| will return the empty string.
  void GetScheduledCaptcha(const std::string& payment_id,
                           OnGetAdaptiveCaptchaChallenge callback);

  // Gets the metadata associated with the currently scheduled captcha.
  bool GetScheduledCaptchaInfo(std::string* url, bool* max_attempts_exceeded);

  // Updates the result for the currently scheduled captcha.
  void UpdateScheduledCaptchaResult(bool result);

  // Shows the scheduled captcha with the given |payment_id| and |captcha_id|.
  void ShowScheduledCaptcha(const std::string& payment_id,
                            const std::string& captcha_id);

  // Snoozes the captcha.
  void SnoozeScheduledCaptcha();

  // Clears the currently scheduled captcha, if any.
  void ClearScheduledCaptcha();

 private:
  // qorai_rewards::RewardsServiceObserver:
  void OnCompleteReset(const bool success) override;

  raw_ptr<PrefService> prefs_ = nullptr;
  raw_ptr<qorai_rewards::RewardsService> rewards_service_ =
      nullptr;  // NOT OWNED
  std::unique_ptr<QoraiAdaptiveCaptchaDelegate> delegate_;
  api_request_helper::APIRequestHelper api_request_helper_;
  std::unique_ptr<GetAdaptiveCaptchaChallenge> get_captcha_challenge_;
};

}  // namespace qorai_adaptive_captcha

#endif  // QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_SERVICE_H_
