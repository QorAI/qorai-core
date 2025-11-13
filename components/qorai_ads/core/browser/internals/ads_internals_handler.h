// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_BROWSER_INTERNALS_ADS_INTERNALS_HANDLER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_BROWSER_INTERNALS_ADS_INTERNALS_HANDLER_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "qorai/components/qorai_ads/core/public/service/ads_service_callback.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "components/prefs/pref_change_registrar.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

class PrefService;

namespace qorai_ads {
class AdsService;
}  // namespace qorai_ads

class AdsInternalsHandler final : public qor_ads::mojom::AdsInternals {
 public:
  AdsInternalsHandler(qorai_ads::AdsService* ads_service, PrefService& prefs);

  AdsInternalsHandler(const AdsInternalsHandler&) = delete;
  AdsInternalsHandler& operator=(const AdsInternalsHandler&) = delete;

  ~AdsInternalsHandler() override;

  void BindInterface(
      mojo::PendingReceiver<qor_ads::mojom::AdsInternals> pending_receiver);

 private:
  // qor_ads::mojom::AdsInternals:
  void CreateAdsInternalsPageHandler(
      mojo::PendingRemote<qor_ads::mojom::AdsInternalsPage> page_pending_remote)
      override;
  void GetAdsInternals(GetAdsInternalsCallback callback) override;
  void ClearAdsData(qorai_ads::ClearDataCallback callback) override;

  void GetInternalsCallback(GetAdsInternalsCallback callback,
                            std::optional<base::Value::Dict> internals);

  void OnQoraiRewardsEnabledPrefChanged(const std::string& path);
  void UpdateQoraiRewardsEnabled();

  const raw_ptr<qorai_ads::AdsService> ads_service_;  // Not owned.

  const raw_ref<PrefService> prefs_;

  mojo::Receiver<qor_ads::mojom::AdsInternals> receiver_{this};

  mojo::Remote<qor_ads::mojom::AdsInternalsPage> page_remote_;

  PrefChangeRegistrar pref_change_registrar_;

  base::WeakPtrFactory<AdsInternalsHandler> weak_ptr_factory_{this};
};

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_BROWSER_INTERNALS_ADS_INTERNALS_HANDLER_H_
