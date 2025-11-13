/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_BROWSER_ADS_SERVICE_IMPL_H_
#define QORAI_COMPONENTS_QORAI_ADS_BROWSER_ADS_SERVICE_IMPL_H_

#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "qorai/components/qorai_adaptive_captcha/qorai_adaptive_captcha_service.h"
#include "qorai/components/qorai_ads/browser/application_state/background_helper.h"
#include "qorai/components/qorai_ads/browser/component_updater/resource_component_observer.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "qorai/components/qorai_ads/core/browser/service/virtual_pref_provider.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ads_callback.h"
#include "qorai/components/qorai_ads/core/public/service/ads_service_callback.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom-forward.h"
#include "qorai/components/services/qor_ads/public/interfaces/qor_ads.mojom.h"
#include "components/content_settings/core/browser/content_settings_observer.h"
#include "components/content_settings/core/browser/content_settings_type_set.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/history/core/browser/history_service.h"
#include "components/prefs/pref_change_registrar.h"
#include "mojo/public/cpp/bindings/associated_receiver.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "ui/base/idle/idle.h"

class GURL;
class HostContentSettingsMap;
class PrefService;

namespace base {
class OneShotTimer;
class SequencedTaskRunner;
}  // namespace base

namespace qorai_rewards {
class RewardsService;
}  // namespace qorai_rewards

namespace network {
class SimpleURLLoader;
class SharedURLLoaderFactory;
}  // namespace network

namespace qorai_ads {

class AdsTooltipsDelegate;
class QorAdsServiceFactory;
class DeviceId;
class ResourceComponent;
struct NewTabPageAdInfo;
class NewTabPageAdPrefetcher;
class AdsServiceImpl final : public AdsService,
                             public qor_ads::mojom::QorAdsClient,
                             public qor_ads::mojom::QorAdsObserver,
                             BackgroundHelper::Observer,
                             public ResourceComponentObserver,
                             public qorai_rewards::RewardsServiceObserver,
                             public content_settings::Observer {
 public:
  explicit AdsServiceImpl(
      std::unique_ptr<Delegate> delegate,
      PrefService* prefs,
      PrefService* local_state,
      std::unique_ptr<VirtualPrefProvider::Delegate>
          virtual_pref_provider_delegate,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader,
      std::string_view channel_name,
      const base::FilePath& profile_path,
      std::unique_ptr<AdsTooltipsDelegate> ads_tooltips_delegate,
      std::unique_ptr<DeviceId> device_id,
      std::unique_ptr<QorAdsServiceFactory> qor_ads_service_factory,
      ResourceComponent* resource_component,
      history::HistoryService* history_service,
      qorai_rewards::RewardsService* rewards_service,
      HostContentSettingsMap* host_content_settings);

  AdsServiceImpl(const AdsServiceImpl&) = delete;
  AdsServiceImpl& operator=(const AdsServiceImpl&) = delete;

  ~AdsServiceImpl() override;

 private:
  using SimpleURLLoaderList =
      std::list<std::unique_ptr<network::SimpleURLLoader>>;

  bool IsQorAdsServiceBound() const;

  void RegisterResourceComponents();
  void RegisterResourceComponentsForCurrentCountryCode();
  void RegisterResourceComponentsForDefaultLanguageCode();

  void Migrate();

  bool UserHasJoinedQoraiRewards() const;
  bool UserHasOptedInToQoraiNewsAds() const;
  bool UserHasOptedInToNewTabPageAds() const;
  bool UserHasOptedInToNotificationAds() const;
  bool UserHasOptedInToSearchResultAds() const;

  void InitializeNotificationsForCurrentProfile();
  void InitializeNotificationsForCurrentProfileCallback();

  void GetDeviceIdAndMaybeStartQorAdsService();
  void GetDeviceIdAndMaybeStartQorAdsServiceCallback(std::string device_id);

  bool CanStartQorAdsService() const;
  void MaybeStartQorAdsService();
  void StartQorAdsService();
  void DisconnectHandler();
  bool ShouldProceedInitialization(size_t current_start_number) const;
  void QorAdsServiceCreatedCallback(size_t current_start_number);
  void InitializeBasePathDirectoryCallback(size_t current_start_number,
                                           bool success);
  void Initialize(size_t current_start_number);
  void InitializeRewardsWallet(size_t current_start_number);
  void InitializeRewardsWalletCallback(
      size_t current_start_number,
      qorai_rewards::mojom::RewardsWalletPtr mojom_rewards_wallet);
  void InitializeQorAds(
      qorai_rewards::mojom::RewardsWalletPtr mojom_rewards_wallet);
  void InitializeQorAdsCallback(bool success);

  void NotifyDidInitializeAdsService() const;
  void NotifyDidShutdownAdsService() const;
  void NotifyDidClearAdsServiceData() const;

  void ClearDataPrefsAndAdsServiceDataAndMaybeRestart(
      ClearDataCallback callback,
      bool shutdown_succeeded);
  void ClearAllPrefsAndAdsServiceDataAndMaybeRestart(ClearDataCallback callback,
                                                     bool shutdown_succeeded);
  void ClearAdsServiceDataAndMaybeRestart(ClearDataCallback callback);
  void ClearAdsServiceDataAndMaybeRestartCallback(ClearDataCallback callback,
                                                  bool success);

  void OnExternalWalletConnectedCallback(bool success);

  void SetSysInfo();
  void SetBuildChannel();
  void SetFlags();
  void SetContentSettings();

  bool ShouldShowOnboardingNotification();
  void MaybeShowOnboardingNotification();

  void ShowReminder(mojom::ReminderType mojom_reminder_type);

  void CloseAdaptiveCaptcha();

  void InitializeLocalStatePrefChangeRegistrar();
  void InitializePrefChangeRegistrar();
  void InitializeQoraiRewardsPrefChangeRegistrar();
  void InitializeSubdivisionTargetingPrefChangeRegistrar();
  void InitializeQoraiNewsAdsPrefChangeRegistrar();
  void InitializeNewTabPageAdsPrefChangeRegistrar();
  void InitializeNotificationAdsPrefChangeRegistrar();
  void InitializeSearchResultAdsPrefChangeRegistrar();
  void OnOptedInToAdsPrefChanged(const std::string& path);
  void OnVariationsCountryPrefChanged();
  void NotifyPrefChanged(const std::string& path) const;

  void GetRewardsWallet();
  void NotifyRewardsWalletDidUpdate(
      qorai_rewards::mojom::RewardsWalletPtr mojom_rewards_wallet);

  void RefetchNewTabPageAd();
  void RefetchNewTabPageAdCallback(bool success);
  void ResetNewTabPageAd();

  void OnParseAndSaveNewTabPageAdsCallback(
      ParseAndSaveNewTabPageAdsCallback callback,
      bool success);

  // TODO(https://github.com/qorai/qorai-browser/issues/14666) Decouple idle
  // state business logic.
  void CheckIdleStateAfterDelay();
  void CheckIdleState();
  void ProcessIdleState(ui::IdleState idle_state, base::TimeDelta idle_time);

  // TODO(https://github.com/qorai/qorai-browser/issues/23974) Decouple
  // notification ad business logic.
  bool CheckIfCanShowNotificationAds();
  bool ShouldShowCustomNotificationAds();
  void StartNotificationAdTimeOutTimer(const std::string& placement_id);
  bool StopNotificationAdTimeOutTimer(const std::string& placement_id);
  void NotificationAdTimedOut(const std::string& placement_id);
  void CloseAllNotificationAds();

  // TODO(https://github.com/qorai/qorai-browser/issues/26193) Decouple open
  // new tab with ad business logic.
  void MaybeOpenNewTabWithAd();
  void OpenNewTabWithAd(const std::string& placement_id);
  void OpenNewTabWithAdCallback(std::optional<base::Value::Dict> dict);
  void RetryOpeningNewTabWithAd(const std::string& placement_id);
  void OpenNewTabWithUrl(const GURL& url);

  // TODO(https://github.com/qorai/qorai-browser/issues/14676) Decouple URL
  // request business logic.
  void URLRequestCallback(SimpleURLLoaderList::iterator url_loader_iter,
                          UrlRequestCallback callback,
                          std::unique_ptr<std::string> response_body);

  void ShowScheduledCaptchaCallback(const std::string& payment_id,
                                    const std::string& captcha_id);
  void SnoozeScheduledCaptchaCallback();

  void DoRecordNotificationAdPositionMetric();

  void ShutdownAds(ShutdownCallback callback);
  void ShutdownAdsCallback(ShutdownCallback callback, bool success);

  void ShutdownAdsService();

  // KeyedService:
  void Shutdown() override;

  // AdsService:
  void AddQorAdsObserver(mojo::PendingRemote<qor_ads::mojom::QorAdsObserver>
                             qor_ads_observer_pending_remote) override;

  bool IsBrowserUpgradeRequiredToServeAds() const override;

  int64_t GetMaximumNotificationAdsPerHour() const override;

  void OnNotificationAdShown(const std::string& placement_id) override;
  void OnNotificationAdClosed(const std::string& placement_id,
                              bool by_user) override;
  void OnNotificationAdClicked(const std::string& placement_id) override;

  void ClearData(ClearDataCallback callback) override;

  void GetInternals(GetInternalsCallback callback) override;

  void GetDiagnostics(GetDiagnosticsCallback callback) override;

  void GetStatementOfAccounts(GetStatementOfAccountsCallback callback) override;

  void MaybeServeInlineContentAd(
      const std::string& dimensions,
      MaybeServeInlineContentAdCallback callback) override;
  void TriggerInlineContentAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::InlineContentAdEventType mojom_ad_event_type,
      TriggerAdEventCallback callback) override;

  std::optional<NewTabPageAdInfo> MaybeGetPrefetchedNewTabPageAd() override;
  void PrefetchNewTabPageAd() override;
  void OnFailedToPrefetchNewTabPageAd(
      const std::string& placement_id,
      const std::string& creative_instance_id) override;
  void ParseAndSaveNewTabPageAds(
      base::Value::Dict dict,
      ParseAndSaveNewTabPageAdsCallback callback) override;
  void MaybeServeNewTabPageAd(MaybeServeNewTabPageAdCallback callback) override;
  void TriggerNewTabPageAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::NewTabPageAdMetricType mojom_ad_metric_type,
      mojom::NewTabPageAdEventType mojom_ad_event_type,
      TriggerAdEventCallback callback) override;

  void TriggerPromotedContentAdEvent(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::PromotedContentAdEventType mojom_ad_event_type,
      TriggerAdEventCallback callback) override;

  void MaybeGetSearchResultAd(const std::string& placement_id,
                              MaybeGetSearchResultAdCallback callback) override;
  void TriggerSearchResultAdEvent(
      mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad,
      mojom::SearchResultAdEventType mojom_ad_event_type,
      TriggerAdEventCallback callback) override;

  void PurgeOrphanedAdEventsForType(
      mojom::AdType mojom_ad_type,
      PurgeOrphanedAdEventsForTypeCallback callback) override;

  void GetAdHistory(base::Time from_time,
                    base::Time to_time,
                    GetAdHistoryForUICallback callback) override;

  void ToggleLikeAd(mojom::ReactionInfoPtr mojom_reaction,
                    ToggleReactionCallback callback) override;
  void ToggleDislikeAd(mojom::ReactionInfoPtr mojom_reaction,
                       ToggleReactionCallback callback) override;
  void ToggleLikeSegment(mojom::ReactionInfoPtr mojom_reaction,
                         ToggleReactionCallback callback) override;
  void ToggleDislikeSegment(mojom::ReactionInfoPtr mojom_reaction,
                            ToggleReactionCallback callback) override;
  void ToggleSaveAd(mojom::ReactionInfoPtr mojom_reaction,
                    ToggleReactionCallback callback) override;
  void ToggleMarkAdAsInappropriate(mojom::ReactionInfoPtr mojom_reaction,
                                   ToggleReactionCallback callback) override;

  void NotifyTabTextContentDidChange(int32_t tab_id,
                                     const std::vector<GURL>& redirect_chain,
                                     const std::string& text) override;
  void NotifyTabHtmlContentDidChange(int32_t tab_id,
                                     const std::vector<GURL>& redirect_chain,
                                     const std::string& html) override;
  void NotifyTabDidStartPlayingMedia(int32_t tab_id) override;
  void NotifyTabDidStopPlayingMedia(int32_t tab_id) override;
  void NotifyTabDidChange(int32_t tab_id,
                          const std::vector<GURL>& redirect_chain,
                          bool is_new_navigation,
                          bool is_restoring,
                          bool is_visible) override;
  void NotifyTabDidLoad(int32_t tab_id, int http_status_code) override;
  void NotifyDidCloseTab(int32_t tab_id) override;

  void NotifyUserGestureEventTriggered(int32_t page_transition_type) override;

  void NotifyBrowserDidBecomeActive() override;
  void NotifyBrowserDidResignActive() override;

  void NotifyDidSolveAdaptiveCaptcha() override;

  // qor_ads::mojom::QorAdsClient:
  void IsNetworkConnectionAvailable(
      IsNetworkConnectionAvailableCallback callback) override;

  void IsBrowserActive(IsBrowserActiveCallback callback) override;
  void IsBrowserInFullScreenMode(
      IsBrowserInFullScreenModeCallback callback) override;

  void CanShowNotificationAds(CanShowNotificationAdsCallback callback) override;
  void CanShowNotificationAdsWhileBrowserIsBackgrounded(
      CanShowNotificationAdsWhileBrowserIsBackgroundedCallback callback)
      override;
  void ShowNotificationAd(base::Value::Dict dict) override;
  void CloseNotificationAd(const std::string& placement_id) override;

  void GetSiteHistory(int max_count,
                      int recent_day_range,
                      GetSiteHistoryCallback callback) override;

  // TODO(https://github.com/qorai/qorai-browser/issues/14676) Decouple URL
  // request business logic.
  void UrlRequest(mojom::UrlRequestInfoPtr mojom_url_request,
                  UrlRequestCallback callback) override;

  // TODO(https://github.com/qorai/qorai-browser/issues/26194) Decouple
  // load/save file business logic.
  void Save(const std::string& name,
            const std::string& value,
            SaveCallback callback) override;
  void Load(const std::string& name, LoadCallback callback) override;

  // TODO(https://github.com/qorai/qorai-browser/issues/26195) Decouple load
  // resources business logic.
  void LoadResourceComponent(const std::string& id,
                             int version,
                             LoadResourceComponentCallback callback) override;

  void ShowScheduledCaptcha(const std::string& payment_id,
                            const std::string& captcha_id) override;

  void FindProfilePref(const std::string& path,
                       FindProfilePrefCallback callback) override;
  void GetProfilePref(const std::string& path,
                      GetProfilePrefCallback callback) override;
  void SetProfilePref(const std::string& path, base::Value value) override;
  void ClearProfilePref(const std::string& path) override;
  void HasProfilePrefPath(const std::string& path,
                          HasProfilePrefPathCallback callback) override;

  void FindLocalStatePref(const std::string& path,
                          FindLocalStatePrefCallback callback) override;
  void GetLocalStatePref(const std::string& path,
                         GetLocalStatePrefCallback callback) override;
  void SetLocalStatePref(const std::string& path, base::Value value) override;
  void ClearLocalStatePref(const std::string& path) override;
  void HasLocalStatePrefPath(const std::string& path,
                             HasLocalStatePrefPathCallback callback) override;

  void GetVirtualPrefs(GetVirtualPrefsCallback callback) override;

  void Log(const std::string& file,
           int32_t line,
           int32_t verbose_level,
           const std::string& message) override;

  // qor_ads::mojom::QorAdsObserver:
  void OnAdRewardsDidChange() override {}
  void OnBrowserUpgradeRequiredToServeAds() override;
  void OnIneligibleWalletToServeAds() override {}
  void OnRemindUser(mojom::ReminderType mojom_reminder_type) override;

  // BackgroundHelper::Observer:
  void OnBrowserDidEnterForeground() override;
  void OnBrowserDidEnterBackground() override;

  // ResourceComponentObserver:
  void OnResourceComponentDidChange(const std::string& manifest_version,
                                    const std::string& id) override;
  void OnDidUnregisterResourceComponent(const std::string& id) override;

  // RewardsServiceObserver:
  void OnRewardsWalletCreated() override;
  void OnExternalWalletConnected() override;
  void OnCompleteReset(bool success) override;

  // content_settings::Observer:
  void OnContentSettingChanged(
      const ContentSettingsPattern& primary_pattern,
      const ContentSettingsPattern& secondary_pattern,
      ContentSettingsTypeSet content_type_set) override;

  bool is_qor_ads_initialized_ = false;

  bool is_shutting_down_ = false;

  bool browser_upgrade_required_to_serve_ads_ = false;

  // Qorai Ads Service starts count is needed to avoid possible double Qorai
  // Ads initialization.
  // TODO(https://github.com/qorai/qorai-browser/issues/30247): Refactor Qorai
  // Ads startup logic.
  size_t service_starts_count_ = 0;

  PrefChangeRegistrar pref_change_registrar_;

  PrefChangeRegistrar local_state_pref_change_registrar_;

  mojom::SysInfo sys_info_;

  base::RepeatingTimer idle_state_timer_;
  ui::IdleState last_idle_state_ = ui::IdleState::IDLE_STATE_ACTIVE;
  base::TimeDelta last_idle_time_;

  std::map<std::string, std::unique_ptr<base::OneShotTimer>>
      notification_ad_timers_;

  std::optional<std::string> retry_opening_new_tab_for_ad_with_placement_id_;

  base::CancelableTaskTracker history_service_task_tracker_;

  SimpleURLLoaderList url_loaders_;

  const raw_ptr<PrefService> prefs_;  // Not owned.

  const raw_ptr<PrefService> local_state_;  // Not owned.

  const std::unique_ptr<VirtualPrefProvider> virtual_pref_provider_;

  scoped_refptr<network::SharedURLLoaderFactory> url_loader_ = nullptr;

  const std::string channel_name_;

  base::ScopedObservation<ResourceComponent, ResourceComponentObserver>
      resource_component_observation_{this};

  const raw_ptr<history::HistoryService> history_service_;  // Not owned.

  const raw_ptr<HostContentSettingsMap>
      host_content_settings_map_;  // Not owned.
  base::ScopedObservation<HostContentSettingsMap, content_settings::Observer>
      host_content_settings_map_observation_{this};

  const std::unique_ptr<AdsTooltipsDelegate> ads_tooltips_delegate_;

  const std::unique_ptr<DeviceId> device_id_;

  std::unique_ptr<NewTabPageAdPrefetcher> new_tab_page_ad_prefetcher_;

  const std::unique_ptr<QorAdsServiceFactory> qor_ads_service_factory_;

  const scoped_refptr<base::SequencedTaskRunner> file_task_runner_;

  const base::FilePath ads_service_path_;

  base::ScopedObservation<qorai_rewards::RewardsService,
                          qorai_rewards::RewardsServiceObserver>
      rewards_service_observation_{this};

  mojo::Receiver<qor_ads::mojom::QorAdsObserver> qor_ads_observer_receiver_{
      this};
  mojo::Remote<qor_ads::mojom::QorAdsService> qor_ads_service_remote_;
  mojo::AssociatedReceiver<qor_ads::mojom::QorAdsClient>
      qor_ads_client_associated_receiver_;
  mojo::AssociatedRemote<qor_ads::mojom::QorAds> qor_ads_associated_remote_;
  mojo::Remote<qor_ads::mojom::QorAdsClientNotifier>
      qor_ads_client_notifier_remote_;
  mojo::PendingReceiver<qor_ads::mojom::QorAdsClientNotifier>
      qor_ads_client_notifier_pending_receiver_;

  base::WeakPtrFactory<AdsServiceImpl> weak_ptr_factory_{this};
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_BROWSER_ADS_SERVICE_IMPL_H_
