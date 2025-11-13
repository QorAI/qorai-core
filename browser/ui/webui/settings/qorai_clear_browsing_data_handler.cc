// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/settings/qorai_clear_browsing_data_handler.h"

#include "base/check.h"
#include "base/check_op.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"

namespace settings {

QoraiClearBrowsingDataHandler::QoraiClearBrowsingDataHandler(
    content::WebUI* webui,
    Profile* profile)
    : ClearBrowsingDataHandler(webui, profile), profile_(profile) {
  CHECK(profile_);

  pref_change_registrar_.Init(profile_->GetPrefs());
  pref_change_registrar_.Add(
      qorai_rewards::prefs::kEnabled,
      base::BindRepeating(
          &QoraiClearBrowsingDataHandler::OnRewardsEnabledPreferenceChanged,
          base::Unretained(this)));
}

QoraiClearBrowsingDataHandler::~QoraiClearBrowsingDataHandler() = default;

void QoraiClearBrowsingDataHandler::RegisterMessages() {
  ClearBrowsingDataHandler::RegisterMessages();

  web_ui()->RegisterMessageCallback(
      "getQoraiRewardsEnabled",
      base::BindRepeating(
          &QoraiClearBrowsingDataHandler::HandleGetQoraiRewardsEnabled,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "clearQoraiAdsData",
      base::BindRepeating(
          &QoraiClearBrowsingDataHandler::HandleClearQoraiAdsData,
          base::Unretained(this)));
}

void QoraiClearBrowsingDataHandler::HandleGetQoraiRewardsEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);

  const bool rewards_enabled =
      profile_->GetPrefs()->GetBoolean(qorai_rewards::prefs::kEnabled);

  AllowJavascript();
  ResolveJavascriptCallback(args[0], rewards_enabled);
}

void QoraiClearBrowsingDataHandler::HandleClearQoraiAdsData(
    const base::Value::List& /*args*/) {
  if (auto* ads_service =
          qorai_ads::AdsServiceFactory::GetForProfile(profile_)) {
    ads_service->ClearData(/*intentional*/ base::DoNothing());
  }
}

void QoraiClearBrowsingDataHandler::OnRewardsEnabledPreferenceChanged() {
  if (!IsJavascriptAllowed()) {
    return;
  }

  const bool rewards_enabled =
      profile_->GetPrefs()->GetBoolean(qorai_rewards::prefs::kEnabled);
  FireWebUIListener("qorai-rewards-enabled-changed",
                    base::Value(rewards_enabled));
}

}  // namespace settings
