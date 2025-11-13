/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_IMPL_H_
#define QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_IMPL_H_

#include <memory>
#include <string>

#include "base/task/sequenced_task_runner.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"

namespace qorai_ads {
class Ads;
struct InlineContentAdInfo;
struct NewTabPageAdInfo;
}  // namespace qorai_ads

namespace qor_ads {

class QorAdsClientMojoBridge;

class QorAdsImpl final : public mojom::QorAds {
 public:
  QorAdsImpl(const base::FilePath& service_path,
             mojo::PendingAssociatedRemote<mojom::QorAdsClient>
                 qor_ads_client_pending_associated_remote,
             mojo::PendingReceiver<mojom::QorAdsClientNotifier>
                 qor_ads_client_notifier_pending_receiver);

  QorAdsImpl(const QorAdsImpl&) = delete;
  QorAdsImpl& operator=(const QorAdsImpl&) = delete;

  ~QorAdsImpl() override;

  // mojom::QorAds:
  void AddQorAdsObserver(mojo::PendingRemote<mojom::QorAdsObserver>
                             qor_ads_observer_pending_remote) override;

  void SetSysInfo(qorai_ads::mojom::SysInfoPtr mojom_sys_info) override;
  void SetBuildChannel(
      qorai_ads::mojom::BuildChannelInfoPtr mojom_build_channel) override;
  void SetFlags(qorai_ads::mojom::FlagsPtr mojom_flags) override;
  void SetContentSettings(
      qorai_ads::mojom::ContentSettingsPtr mojom_content_settings) override;

  void Initialize(qorai_ads::mojom::WalletInfoPtr mojom_wallet,
                  InitializeCallback callback) override;
  void Shutdown(ShutdownCallback callback) override;

  void GetInternals(GetInternalsCallback callback) override;

  void GetDiagnostics(GetDiagnosticsCallback callback) override;

  void GetStatementOfAccounts(GetStatementOfAccountsCallback callback) override;

  void MaybeServeInlineContentAd(
      const std::string& dimensions,
      MaybeServeInlineContentAdCallback callback) override;
  void TriggerInlineContentAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      qorai_ads::mojom::InlineContentAdEventType mojom_ad_event_type,
      TriggerInlineContentAdEventCallback callback) override;

  void ParseAndSaveNewTabPageAds(
      base::Value::Dict data,
      ParseAndSaveNewTabPageAdsCallback callback) override;
  void MaybeServeNewTabPageAd(MaybeServeNewTabPageAdCallback callback) override;
  void TriggerNewTabPageAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      qorai_ads::mojom::NewTabPageAdMetricType mojom_ad_metric_type,
      qorai_ads::mojom::NewTabPageAdEventType mojom_ad_event_type,
      TriggerNewTabPageAdEventCallback callback) override;

  void MaybeGetNotificationAd(const std::string& placement_id,
                              MaybeGetNotificationAdCallback callback) override;
  void TriggerNotificationAdEvent(
      const std::string& placement_id,
      qorai_ads::mojom::NotificationAdEventType mojom_ad_event_type,
      TriggerNotificationAdEventCallback callback) override;

  void TriggerPromotedContentAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      qorai_ads::mojom::PromotedContentAdEventType mojom_ad_event_type,
      TriggerPromotedContentAdEventCallback callback) override;

  void MaybeGetSearchResultAd(const std::string& placement_id,
                              MaybeGetSearchResultAdCallback callback) override;
  void TriggerSearchResultAdEvent(
      qorai_ads::mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
      qorai_ads::mojom::SearchResultAdEventType mojom_ad_event_type,
      TriggerSearchResultAdEventCallback callback) override;

  void PurgeOrphanedAdEventsForType(
      qorai_ads::mojom::AdType mojom_ad_type,
      PurgeOrphanedAdEventsForTypeCallback callback) override;

  void GetAdHistory(base::Time from_time,
                    base::Time to_time,
                    GetAdHistoryCallback callback) override;

  void ToggleLikeAd(qorai_ads::mojom::ReactionInfoPtr reaction,
                    ToggleLikeAdCallback callback) override;
  void ToggleDislikeAd(qorai_ads::mojom::ReactionInfoPtr reaction,
                       ToggleDislikeAdCallback callback) override;
  void ToggleLikeSegment(qorai_ads::mojom::ReactionInfoPtr reaction,
                         ToggleLikeSegmentCallback callback) override;
  void ToggleDislikeSegment(qorai_ads::mojom::ReactionInfoPtr reaction,
                            ToggleDislikeSegmentCallback callback) override;
  void ToggleSaveAd(qorai_ads::mojom::ReactionInfoPtr reaction,
                    ToggleSaveAdCallback callback) override;
  void ToggleMarkAdAsInappropriate(
      qorai_ads::mojom::ReactionInfoPtr reaction,
      ToggleMarkAdAsInappropriateCallback callback) override;

 private:
  qorai_ads::Ads* GetAds();

  class AdsInstance;
  std::unique_ptr<AdsInstance, base::OnTaskRunnerDeleter> ads_instance_;
};

}  // namespace qor_ads

#endif  // QORAI_COMPONENTS_SERVICES_QOR_ADS_QOR_ADS_IMPL_H_
