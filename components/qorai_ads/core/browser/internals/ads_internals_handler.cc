// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_ads/core/browser/internals/ads_internals_handler.h"

#include <utility>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/json/json_writer.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "components/prefs/pref_service.h"

AdsInternalsHandler::AdsInternalsHandler(qorai_ads::AdsService* ads_service,
                                         PrefService& prefs)
    : ads_service_(ads_service), prefs_(prefs) {
  pref_change_registrar_.Init(&*prefs_);
  pref_change_registrar_.Add(
      qorai_rewards::prefs::kEnabled,
      base::BindRepeating(
          &AdsInternalsHandler::OnQoraiRewardsEnabledPrefChanged,
          weak_ptr_factory_.GetWeakPtr()));
}

AdsInternalsHandler::~AdsInternalsHandler() = default;

void AdsInternalsHandler::BindInterface(
    mojo::PendingReceiver<qor_ads::mojom::AdsInternals> pending_receiver) {
  if (receiver_.is_bound()) {
    receiver_.reset();
  }

  receiver_.Bind(std::move(pending_receiver));
}

///////////////////////////////////////////////////////////////////////////////

void AdsInternalsHandler::CreateAdsInternalsPageHandler(
    mojo::PendingRemote<qor_ads::mojom::AdsInternalsPage> page_pending_remote) {
  page_remote_ = mojo::Remote<qor_ads::mojom::AdsInternalsPage>(
      std::move(page_pending_remote));

  UpdateQoraiRewardsEnabled();
}

void AdsInternalsHandler::GetAdsInternals(GetAdsInternalsCallback callback) {
  if (!ads_service_) {
    return std::move(callback).Run(/*ads_internals=*/"{}");
  }

  ads_service_->GetInternals(
      base::BindOnce(&AdsInternalsHandler::GetInternalsCallback,
                     weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
}

void AdsInternalsHandler::ClearAdsData(qorai_ads::ClearDataCallback callback) {
  if (!ads_service_) {
    return std::move(callback).Run(/*success=*/false);
  }

  ads_service_->ClearData(std::move(callback));
}

void AdsInternalsHandler::GetInternalsCallback(
    GetAdsInternalsCallback callback,
    std::optional<base::Value::Dict> internals) {
  // `value` can be nullopt in the following cases:
  // - `qor_ads::mojom::QorAds` associated remote is not bound.
  // - A database query fails.
  std::string json;
  CHECK(base::JSONWriter::Write(
      std::move(internals).value_or(base::Value::Dict{}), &json));
  std::move(callback).Run(json);
}

void AdsInternalsHandler::OnQoraiRewardsEnabledPrefChanged(
    const std::string& /*path*/) {
  UpdateQoraiRewardsEnabled();
}

void AdsInternalsHandler::UpdateQoraiRewardsEnabled() {
  if (!page_remote_) {
    return;
  }

  const bool is_enabled = prefs_->GetBoolean(qorai_rewards::prefs::kEnabled);
  page_remote_->UpdateQoraiRewardsEnabled(is_enabled);
}
