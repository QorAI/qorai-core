/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_adaptive_captcha/qorai_adaptive_captcha_service.h"

#include <algorithm>
#include <utility>

#include "base/check.h"
#include "qorai/components/qorai_adaptive_captcha/pref_names.h"
#include "qorai/components/qorai_adaptive_captcha/server_util.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace {

std::string GetScheduledCaptchaUrl(const std::string& payment_id,
                                   const std::string& captcha_id) {
  DCHECK(!payment_id.empty());
  DCHECK(!captcha_id.empty());

  const std::string path =
      absl::StrFormat("/v3/captcha/%s/%s", payment_id, captcha_id);
  return qorai_adaptive_captcha::ServerUtil::GetInstance()->GetServerUrl(path);
}

}  // namespace

namespace qorai_adaptive_captcha {

constexpr int kScheduledCaptchaMaxFailedAttempts = 10;

net::NetworkTrafficAnnotationTag kAnnotationTag =
    net::DefineNetworkTrafficAnnotation("qorai_adaptive_captcha_service", R"(
        semantics {
          sender:
            "Qorai Adaptive Captcha service"
          description:
            "Fetches CAPTCHA data from Qorai."
          trigger:
            "The Qorai service indicates that it's time to solve a CAPTCHA."
          data: "Qorai CAPTCHA data."
          destination: WEBSITE
        }
        policy {
          cookies_allowed: NO
          setting:
            "This feature cannot be disabled by settings."
          policy_exception_justification:
            "Not implemented."
        })");

QoraiAdaptiveCaptchaService::QoraiAdaptiveCaptchaService(
    PrefService* prefs,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    qorai_rewards::RewardsService* rewards_service,
    std::unique_ptr<QoraiAdaptiveCaptchaDelegate> delegate)
    : prefs_(prefs),
      rewards_service_(rewards_service),
      delegate_(std::move(delegate)),
      api_request_helper_(kAnnotationTag, url_loader_factory),
      get_captcha_challenge_(
          std::make_unique<GetAdaptiveCaptchaChallenge>(&api_request_helper_)) {
  DCHECK(prefs);
  DCHECK(rewards_service);

  rewards_service_->AddObserver(this);
}

QoraiAdaptiveCaptchaService::~QoraiAdaptiveCaptchaService() {
  rewards_service_->RemoveObserver(this);
}

void QoraiAdaptiveCaptchaService::GetScheduledCaptcha(
    const std::string& payment_id,
    OnGetAdaptiveCaptchaChallenge callback) {
  get_captcha_challenge_->Request(payment_id, std::move(callback));
}

bool QoraiAdaptiveCaptchaService::GetScheduledCaptchaInfo(
    std::string* url,
    bool* max_attempts_exceeded) {
  DCHECK(url);
  DCHECK(max_attempts_exceeded);

  const std::string payment_id =
      prefs_->GetString(prefs::kScheduledCaptchaPaymentId);
  const std::string captcha_id = prefs_->GetString(prefs::kScheduledCaptchaId);
  if (payment_id.empty() || captcha_id.empty()) {
    return false;
  }

  const int failed_attempts =
      prefs_->GetInteger(prefs::kScheduledCaptchaFailedAttempts);

  *url = GetScheduledCaptchaUrl(payment_id, captcha_id);
  *max_attempts_exceeded =
      failed_attempts >= kScheduledCaptchaMaxFailedAttempts;

  return true;
}

void QoraiAdaptiveCaptchaService::UpdateScheduledCaptchaResult(bool result) {
  if (!result) {
    const int failed_attempts =
        prefs_->GetInteger(prefs::kScheduledCaptchaFailedAttempts) + 1;
    prefs_->SetInteger(
        prefs::kScheduledCaptchaFailedAttempts,
        std::min(failed_attempts, kScheduledCaptchaMaxFailedAttempts));
    if (failed_attempts >= kScheduledCaptchaMaxFailedAttempts) {
      prefs_->SetBoolean(prefs::kScheduledCaptchaPaused, true);
    }
    return;
  }

  ClearScheduledCaptcha();
}

void QoraiAdaptiveCaptchaService::ShowScheduledCaptcha(
    const std::string& payment_id,
    const std::string& captcha_id) {
  if (prefs_->GetBoolean(prefs::kScheduledCaptchaPaused)) {
    return;
  }

  prefs_->SetString(prefs::kScheduledCaptchaPaymentId, payment_id);
  prefs_->SetString(prefs::kScheduledCaptchaId, captcha_id);

  if (delegate_) {
    delegate_->ShowScheduledCaptcha(payment_id, captcha_id);
    return;
  }
}

void QoraiAdaptiveCaptchaService::SnoozeScheduledCaptcha() {
  prefs_->SetString(prefs::kScheduledCaptchaPaymentId, "");
  prefs_->SetString(prefs::kScheduledCaptchaId, "");
}

void QoraiAdaptiveCaptchaService::ClearScheduledCaptcha() {
  prefs_->SetInteger(prefs::kScheduledCaptchaFailedAttempts, 0);
  prefs_->SetString(prefs::kScheduledCaptchaPaymentId, "");
  prefs_->SetString(prefs::kScheduledCaptchaId, "");
  prefs_->SetBoolean(prefs::kScheduledCaptchaPaused, false);
}

void QoraiAdaptiveCaptchaService::OnCompleteReset(const bool success) {
  ClearScheduledCaptcha();
}

// static
void QoraiAdaptiveCaptchaService::RegisterProfilePrefs(
    PrefRegistrySimple* registry) {
  registry->RegisterStringPref(prefs::kScheduledCaptchaId, "");
  registry->RegisterStringPref(prefs::kScheduledCaptchaPaymentId, "");
  registry->RegisterIntegerPref(prefs::kScheduledCaptchaSnoozeCount, 0);
  registry->RegisterIntegerPref(prefs::kScheduledCaptchaFailedAttempts, 0);
  registry->RegisterBooleanPref(prefs::kScheduledCaptchaPaused, false);
}

}  // namespace qorai_adaptive_captcha
