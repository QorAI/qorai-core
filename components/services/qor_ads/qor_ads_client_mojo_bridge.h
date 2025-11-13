/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_CLIENT_MOJO_BRIDGE_H_
#define QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_CLIENT_MOJO_BRIDGE_H_

#include <optional>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "base/values.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client.h"
#include "qorai/components/services/qor_ads/qor_ads_client_notifier_impl.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"

namespace qorai_ads {
class AdsClientNotifierObserver;
struct NotificationAdInfo;
}  // namespace qorai_ads

namespace qor_ads {

class QorAdsClientMojoBridge final : public qorai_ads::AdsClient {
 public:
  explicit QorAdsClientMojoBridge(
      mojo::PendingAssociatedRemote<mojom::QorAdsClient>
          qor_ads_client_pending_associated_remote,
      mojo::PendingReceiver<mojom::QorAdsClientNotifier>
          qor_ads_client_notifier_pending_receiver);

  QorAdsClientMojoBridge(const QorAdsClientMojoBridge&) = delete;
  QorAdsClientMojoBridge& operator=(const QorAdsClientMojoBridge&) = delete;

  ~QorAdsClientMojoBridge() override;

  // qorai_ads::AdsClient:
  void AddObserver(qorai_ads::AdsClientNotifierObserver* observer) override;
  void RemoveObserver(qorai_ads::AdsClientNotifierObserver* observer) override;
  void NotifyPendingObservers() override;

  bool IsNetworkConnectionAvailable() const override;

  bool IsBrowserActive() const override;
  bool IsBrowserInFullScreenMode() const override;

  bool CanShowNotificationAds() const override;
  bool CanShowNotificationAdsWhileBrowserIsBackgrounded() const override;
  void ShowNotificationAd(const qorai_ads::NotificationAdInfo& ad) override;
  void CloseNotificationAd(const std::string& placement_id) override;

  void GetSiteHistory(int max_count,
                      int days_ago,
                      qorai_ads::GetSiteHistoryCallback callback) override;

  void UrlRequest(qorai_ads::mojom::UrlRequestInfoPtr mojom_url_request,
                  qorai_ads::UrlRequestCallback callback) override;

  void Save(const std::string& name,
            const std::string& value,
            qorai_ads::SaveCallback callback) override;
  void Load(const std::string& name, qorai_ads::LoadCallback callback) override;

  void LoadResourceComponent(const std::string& id,
                             int version,
                             qorai_ads::LoadFileCallback callback) override;

  void ShowScheduledCaptcha(const std::string& payment_id,
                            const std::string& captcha_id) override;

  bool FindProfilePref(const std::string& path) const override;
  std::optional<base::Value> GetProfilePref(const std::string& path) override;
  void SetProfilePref(const std::string& path, base::Value value) override;
  void ClearProfilePref(const std::string& path) override;
  bool HasProfilePrefPath(const std::string& path) const override;

  bool FindLocalStatePref(const std::string& path) const override;
  std::optional<base::Value> GetLocalStatePref(
      const std::string& path) override;
  void SetLocalStatePref(const std::string& path, base::Value value) override;
  void ClearLocalStatePref(const std::string& path) override;
  bool HasLocalStatePrefPath(const std::string& path) const override;

  base::Value::Dict GetVirtualPrefs() const override;

  void Log(const char* file,
           int line,
           int verbose_level,
           const std::string& message) override;

 private:
  std::optional<base::Value> CachedProfilePrefValue(
      const std::string& path) const;
  std::optional<base::Value> CachedLocalStatePrefValue(
      const std::string& path) const;

  base::flat_map</*path=*/std::string, /*value=*/base::Value>
      cached_profile_prefs_;
  base::flat_map</*path=*/std::string, /*value=*/base::Value>
      cached_local_state_prefs_;

  mojo::AssociatedRemote<mojom::QorAdsClient> qor_ads_client_associated_remote_;
  QorAdsClientNotifierImpl qor_ads_client_notifier_impl_;
};

}  // namespace qor_ads

#endif  // QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_CLIENT_MOJO_BRIDGE_H_
