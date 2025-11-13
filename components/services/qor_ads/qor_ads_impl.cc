/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/services/qor_ads/qor_ads_impl.h"

#include <memory>
#include <optional>
#include <utility>

#include "base/check.h"
#include "base/types/optional_ref.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/inline_content_ad/inline_content_ad_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/inline_content_ad/inline_content_ad_value_util.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_value_util.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_value_util.h"
#include "qorai/components/qorai_ads/core/public/ads.h"
#include "qorai/components/qorai_ads/core/public/ads_constants.h"
#include "qorai/components/qorai_ads/core/public/ads_observer.h"
#include "qorai/components/services/qor_ads/qor_ads_client_mojo_bridge.h"
#include "qorai/components/services/qor_ads/qor_ads_observer.h"
#include "mojo/public/cpp/bindings/callback_helpers.h"

namespace qor_ads {

class QorAdsImpl::AdsInstance final {
 public:
  AdsInstance(
      const base::FilePath& service_path,
      mojo::PendingAssociatedRemote<mojom::QorAdsClient>
          qor_ads_client_pending_associated_remote,
      mojo::PendingReceiver<mojom::QorAdsClientNotifier> client_notifier)
      : qor_ads_client_mojo_proxy_(std::make_unique<QorAdsClientMojoBridge>(
            std::move(qor_ads_client_pending_associated_remote),
            std::move(client_notifier))),
        ads_(qorai_ads::Ads::CreateInstance(
            *qor_ads_client_mojo_proxy_,
            service_path.AppendASCII(qorai_ads::kDatabaseFilename))) {}

  AdsInstance(const AdsInstance&) = delete;
  AdsInstance& operator=(const AdsInstance&) = delete;

  AdsInstance(AdsInstance&& other) noexcept = delete;
  AdsInstance& operator=(AdsInstance&& other) noexcept = delete;

  ~AdsInstance() = default;

  qorai_ads::Ads* GetAds() { return ads_.get(); }

 private:
  std::unique_ptr<QorAdsClientMojoBridge> qor_ads_client_mojo_proxy_;
  std::unique_ptr<qorai_ads::Ads> ads_;
};

QorAdsImpl::QorAdsImpl(const base::FilePath& service_path,
                       mojo::PendingAssociatedRemote<mojom::QorAdsClient>
                           qor_ads_client_pending_associated_remote,
                       mojo::PendingReceiver<mojom::QorAdsClientNotifier>
                           qor_ads_client_notifier_pending_receiver)
    : ads_instance_(std::unique_ptr<AdsInstance, base::OnTaskRunnerDeleter>(
          new AdsInstance(service_path,
                          std::move(qor_ads_client_pending_associated_remote),
                          std::move(qor_ads_client_notifier_pending_receiver)),
          base::OnTaskRunnerDeleter(
              base::SequencedTaskRunner::GetCurrentDefault()))) {}

QorAdsImpl::~QorAdsImpl() = default;

void QorAdsImpl::AddQorAdsObserver(mojo::PendingRemote<mojom::QorAdsObserver>
                                       qor_ads_observer_pending_remote) {
  std::unique_ptr<qorai_ads::AdsObserver> ads_observer =
      std::make_unique<QorAdsObserver>(
          std::move(qor_ads_observer_pending_remote));
  GetAds()->AddObserver(std::move(ads_observer));
}

void QorAdsImpl::SetSysInfo(qorai_ads::mojom::SysInfoPtr mojom_sys_info) {
  GetAds()->SetSysInfo(std::move(mojom_sys_info));
}

void QorAdsImpl::SetBuildChannel(
    qorai_ads::mojom::BuildChannelInfoPtr mojom_build_channel) {
  GetAds()->SetBuildChannel(std::move(mojom_build_channel));
}

void QorAdsImpl::SetFlags(qorai_ads::mojom::FlagsPtr mojom_flags) {
  GetAds()->SetFlags(std::move(mojom_flags));
}

void QorAdsImpl::SetContentSettings(
    qorai_ads::mojom::ContentSettingsPtr mojom_content_settings) {
  GetAds()->SetContentSettings(std::move(mojom_content_settings));
}

void QorAdsImpl::Initialize(qorai_ads::mojom::WalletInfoPtr mojom_wallet,
                            InitializeCallback callback) {
  GetAds()->Initialize(std::move(mojom_wallet),
                       mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                           std::move(callback), /*success=*/false));
}

void QorAdsImpl::Shutdown(ShutdownCallback callback) {
  GetAds()->Shutdown(mojo::WrapCallbackWithDefaultInvokeIfNotRun(
      std::move(callback), /*success=*/false));
}

void QorAdsImpl::MaybeGetNotificationAd(
    const std::string& placement_id,
    MaybeGetNotificationAdCallback callback) {
  GetAds()->MaybeGetNotificationAd(
      placement_id,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(
          base::BindOnce(
              [](MaybeGetNotificationAdCallback callback,
                 base::optional_ref<const qorai_ads::NotificationAdInfo> ad) {
                if (!ad) {
                  return std::move(callback).Run(/*ad*/ std::nullopt);
                }

                std::optional<base::Value::Dict> dict =
                    qorai_ads::NotificationAdToValue(*ad);
                std::move(callback).Run(std::move(dict));
              },
              std::move(callback)),
          /*value=*/std::nullopt));
}

void QorAdsImpl::TriggerNotificationAdEvent(
    const std::string& placement_id,
    qorai_ads::mojom::NotificationAdEventType mojom_ad_event_type,
    TriggerNotificationAdEventCallback callback) {
  CHECK(qorai_ads::mojom::IsKnownEnumValue(mojom_ad_event_type));

  GetAds()->TriggerNotificationAdEvent(
      placement_id, mojom_ad_event_type,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*success=*/false));
}

void QorAdsImpl::ParseAndSaveNewTabPageAds(
    base::Value::Dict data,
    ParseAndSaveNewTabPageAdsCallback callback) {
  GetAds()->ParseAndSaveNewTabPageAds(
      std::move(data), mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                           std::move(callback), /*success=*/false));
}

void QorAdsImpl::MaybeServeNewTabPageAd(
    MaybeServeNewTabPageAdCallback callback) {
  GetAds()->MaybeServeNewTabPageAd(mojo::WrapCallbackWithDefaultInvokeIfNotRun(
      base::BindOnce(
          [](MaybeServeNewTabPageAdCallback callback,
             base::optional_ref<const qorai_ads::NewTabPageAdInfo> ad) {
            if (!ad) {
              std::move(callback).Run(/*ad*/ std::nullopt);
              return;
            }

            std::optional<base::Value::Dict> dict =
                qorai_ads::NewTabPageAdToValue(*ad);
            std::move(callback).Run(std::move(dict));
          },
          std::move(callback)),
      /*value=*/std::nullopt));
}

void QorAdsImpl::TriggerNewTabPageAdEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    qorai_ads::mojom::NewTabPageAdMetricType mojom_ad_metric_type,
    qorai_ads::mojom::NewTabPageAdEventType mojom_ad_event_type,
    TriggerNewTabPageAdEventCallback callback) {
  CHECK(qorai_ads::mojom::IsKnownEnumValue(mojom_ad_event_type));

  GetAds()->TriggerNewTabPageAdEvent(
      placement_id, creative_instance_id, mojom_ad_metric_type,
      mojom_ad_event_type,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*success=*/false));
}

void QorAdsImpl::TriggerPromotedContentAdEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    qorai_ads::mojom::PromotedContentAdEventType mojom_ad_event_type,
    TriggerPromotedContentAdEventCallback callback) {
  CHECK(qorai_ads::mojom::IsKnownEnumValue(mojom_ad_event_type));

  GetAds()->TriggerPromotedContentAdEvent(
      placement_id, creative_instance_id, mojom_ad_event_type,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*success=*/false));
}

void QorAdsImpl::MaybeServeInlineContentAd(
    const std::string& dimensions,
    MaybeServeInlineContentAdCallback callback) {
  GetAds()->MaybeServeInlineContentAd(
      dimensions,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(
          base::BindOnce(
              [](MaybeServeInlineContentAdCallback callback,
                 const std::string& dimensions,
                 base::optional_ref<const qorai_ads::InlineContentAdInfo> ad) {
                if (!ad) {
                  std::move(callback).Run(dimensions,
                                          /*ads*/ std::nullopt);
                  return;
                }

                std::optional<base::Value::Dict> dict =
                    qorai_ads::InlineContentAdToValue(*ad);
                std::move(callback).Run(dimensions, std::move(dict));
              },
              std::move(callback)),
          /*dimensions=*/std::string(),
          /*value=*/std::nullopt));
}

void QorAdsImpl::TriggerInlineContentAdEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    qorai_ads::mojom::InlineContentAdEventType mojom_ad_event_type,
    TriggerInlineContentAdEventCallback callback) {
  CHECK(qorai_ads::mojom::IsKnownEnumValue(mojom_ad_event_type));

  GetAds()->TriggerInlineContentAdEvent(
      placement_id, creative_instance_id, mojom_ad_event_type,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*success=*/false));
}

void QorAdsImpl::MaybeGetSearchResultAd(
    const std::string& placement_id,
    MaybeGetSearchResultAdCallback callback) {
  GetAds()->MaybeGetSearchResultAd(
      placement_id, mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                        std::move(callback), /*search_result_ad=*/qorai_ads::
                            mojom::CreativeSearchResultAdInfoPtr()));
}

void QorAdsImpl::TriggerSearchResultAdEvent(
    qorai_ads::mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
    qorai_ads::mojom::SearchResultAdEventType mojom_ad_event_type,
    TriggerSearchResultAdEventCallback callback) {
  CHECK(qorai_ads::mojom::IsKnownEnumValue(mojom_ad_event_type));

  GetAds()->TriggerSearchResultAdEvent(
      std::move(mojom_creative_ad), mojom_ad_event_type,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*success=*/false));
}

void QorAdsImpl::PurgeOrphanedAdEventsForType(
    qorai_ads::mojom::AdType mojom_ad_type,
    PurgeOrphanedAdEventsForTypeCallback callback) {
  CHECK(qorai_ads::mojom::IsKnownEnumValue(mojom_ad_type));

  GetAds()->PurgeOrphanedAdEventsForType(
      mojom_ad_type,
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*success=*/false));
}

void QorAdsImpl::GetAdHistory(base::Time from_time,
                              base::Time to_time,
                              GetAdHistoryCallback callback) {
  GetAds()->GetAdHistory(from_time, to_time,
                         mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                             std::move(callback), /*value=*/std::nullopt));
}

void QorAdsImpl::GetStatementOfAccounts(
    GetStatementOfAccountsCallback callback) {
  GetAds()->GetStatementOfAccounts(mojo::WrapCallbackWithDefaultInvokeIfNotRun(
      std::move(callback), /*mojom_statement=*/nullptr));
}

void QorAdsImpl::GetInternals(GetInternalsCallback callback) {
  GetAds()->GetInternals(
      mojo::WrapCallbackWithDefaultInvokeIfNotRun(std::move(callback),
                                                  /*value=*/std::nullopt));
}

void QorAdsImpl::GetDiagnostics(GetDiagnosticsCallback callback) {
  GetAds()->GetDiagnostics(mojo::WrapCallbackWithDefaultInvokeIfNotRun(
      std::move(callback), /*value=*/std::nullopt));
}

void QorAdsImpl::ToggleLikeAd(qorai_ads::mojom::ReactionInfoPtr reaction,
                              ToggleLikeAdCallback callback) {
  GetAds()->ToggleLikeAd(std::move(reaction),
                         mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                             std::move(callback), /*success=*/false));
}

void QorAdsImpl::ToggleDislikeAd(qorai_ads::mojom::ReactionInfoPtr reaction,
                                 ToggleDislikeAdCallback callback) {
  GetAds()->ToggleDislikeAd(std::move(reaction),
                            mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                                std::move(callback), /*success=*/false));
}

void QorAdsImpl::ToggleLikeSegment(qorai_ads::mojom::ReactionInfoPtr reaction,
                                   ToggleLikeSegmentCallback callback) {
  GetAds()->ToggleLikeSegment(std::move(reaction),
                              mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                                  std::move(callback), /*success=*/false));
}

void QorAdsImpl::ToggleDislikeSegment(
    qorai_ads::mojom::ReactionInfoPtr reaction,
    ToggleDislikeSegmentCallback callback) {
  GetAds()->ToggleDislikeSegment(std::move(reaction),
                                 mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                                     std::move(callback), /*success=*/false));
}

void QorAdsImpl::ToggleSaveAd(qorai_ads::mojom::ReactionInfoPtr reaction,
                              ToggleSaveAdCallback callback) {
  GetAds()->ToggleSaveAd(std::move(reaction),
                         mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                             std::move(callback), /*success=*/false));
}

void QorAdsImpl::ToggleMarkAdAsInappropriate(
    qorai_ads::mojom::ReactionInfoPtr reaction,
    ToggleMarkAdAsInappropriateCallback callback) {
  GetAds()->ToggleMarkAdAsInappropriate(
      std::move(reaction), mojo::WrapCallbackWithDefaultInvokeIfNotRun(
                               std::move(callback), /*success=*/false));
}

qorai_ads::Ads* QorAdsImpl::GetAds() {
  CHECK(ads_instance_);

  CHECK(ads_instance_->GetAds());
  return ads_instance_->GetAds();
}

}  // namespace qor_ads
