/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_ads/tooltips/ads_tooltips_controller.h"

#include <memory>
#include <utility>

#include "qorai/browser/qorai_ads/tooltips/ads_captcha_tooltip.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_attributes.h"
#include "qorai/browser/ui/qorai_tooltips/qorai_tooltip_popup_handler.h"
#include "components/grit/qorai_components_strings.h"
#include "ui/base/l10n/l10n_util.h"

namespace qorai_ads {

AdsTooltipsController::AdsTooltipsController() = default;

AdsTooltipsController::~AdsTooltipsController() = default;

void AdsTooltipsController::ShowCaptchaTooltip(
    const std::string& payment_id,
    const std::string& captcha_id,
    bool include_cancel_button,
    ShowScheduledCaptchaCallback show_captcha_callback,
    SnoozeScheduledCaptchaCallback snooze_captcha_callback) {
  const std::u16string title = l10n_util::GetStringUTF16(
      IDS_QORAI_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_TITLE);
  const std::u16string body = l10n_util::GetStringUTF16(
      IDS_QORAI_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_BODY);
  const std::u16string ok_button_text = l10n_util::GetStringUTF16(
      IDS_QORAI_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_OK_BUTTON_TEXT);
  std::u16string cancel_button_text = l10n_util::GetStringUTF16(
      IDS_QORAI_ADS_SCHEDULED_CAPTCHA_NOTIFICATION_CANCEL_BUTTON_TEXT);

  qorai_tooltips::QoraiTooltipAttributes tooltip_attributes(
      title, body, ok_button_text,
      include_cancel_button ? cancel_button_text : u"");
  tooltip_attributes.set_cancel_button_enabled(include_cancel_button);
  auto captcha_tooltip = std::make_unique<AdsCaptchaTooltip>(
      std::move(show_captcha_callback), std::move(snooze_captcha_callback),
      tooltip_attributes, payment_id, captcha_id);

  // If there's no delegate, set one so that clicks go back to the appropriate
  // handler
  captcha_tooltip->set_delegate(AsWeakPtr());

  qorai_tooltips::QoraiTooltipPopupHandler::Show(std::move(captcha_tooltip));
}

void AdsTooltipsController::CloseCaptchaTooltip() {
  qorai_tooltips::QoraiTooltipPopupHandler::Close(kScheduledCaptchaTooltipId);
}

base::WeakPtr<qorai_tooltips::QoraiTooltipDelegate>
AdsTooltipsController::AsWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}

void AdsTooltipsController::OnTooltipWidgetDestroyed(
    const std::string& /*tooltip_id*/) {
  qorai_tooltips::QoraiTooltipPopupHandler::Destroy(kScheduledCaptchaTooltipId);
}

}  // namespace qorai_ads
