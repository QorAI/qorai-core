/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_browser_process_impl.h"

#include <memory>
#include <string>
#include <utility>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/path_service.h"
#include "base/task/thread_pool.h"
#include "qorai/browser/qorai_ads/analytics/p3a/qorai_stats_helper.h"
#include "qorai/browser/qorai_referrals/referrals_service_delegate.h"
#include "qorai/browser/qorai_shields/ad_block_subscription_download_manager_getter.h"
#include "qorai/browser/qorai_stats/qorai_stats_updater.h"
#include "qorai/browser/qorai_stats/first_run_util.h"
#include "qorai/browser/qorai_wallet/wallet_data_files_installer_delegate_impl.h"
#include "qorai/browser/component_updater/qorai_component_updater_configurator.h"
#include "qorai/browser/misc_metrics/process_misc_metrics.h"
#include "qorai/browser/net/qorai_system_request_handler.h"
#include "qorai/browser/profiles/qorai_profile_manager.h"
#include "qorai/browser/themes/qorai_dark_mode_utils.h"
#include "qorai/common/qorai_channel_info.h"
#include "qorai/components/ai_chat/core/common/buildflags/buildflags.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_ads/browser/component_updater/resource_component.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component_updater_delegate.h"
#include "qorai/components/qorai_component_updater/browser/local_data_files_service.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_manager.h"
#include "qorai/components/qorai_policy/ad_block_only_mode/ad_block_only_mode_policy_manager.h"
#include "qorai/components/qorai_referrals/browser/qorai_referrals_service.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_subscription_service_manager.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_sync/network_time_helper.h"
#include "qorai/components/qorai_wallet/browser/wallet_data_files_installer.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/debounce/core/browser/debounce_component_installer.h"
#include "qorai/components/debounce/core/common/features.h"
#include "qorai/components/https_upgrade_exceptions/browser/https_upgrade_exceptions_service.h"
#include "qorai/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "qorai/components/p3a/histograms_qoraiizer.h"
#include "qorai/components/p3a/p3a_config.h"
#include "qorai/components/p3a/p3a_service.h"
#include "qorai/components/webcompat/content/browser/webcompat_exceptions_service.h"
#include "qorai/components/webcompat/core/common/features.h"
#include "qorai/services/network/public/cpp/system_request_handler.h"
#include "build/build_config.h"
#include "chrome/browser/component_updater/component_updater_utils.h"
#include "chrome/browser/net/system_network_context_manager.h"
#include "chrome/browser/obsolete_system/obsolete_system.h"
#include "chrome/common/buildflags.h"
#include "chrome/common/channel_info.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/common/pref_names.h"
#include "components/component_updater/timer_update_scheduler.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/child_process_security_policy.h"
#include "net/base/features.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
#include "qorai/browser/ai_chat/ai_chat_agent_profile_manager.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/qorai_tor_client_updater.h"
#include "qorai/components/tor/qorai_tor_pluggable_transport_updater.h"
#include "qorai/components/tor/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/speedreader_rewriter_service.h"
#endif

#if BUILDFLAG(IS_ANDROID)
#include "chrome/browser/flags/android/chrome_feature_list.h"
#else
#include "qorai/browser/search_engines/search_engine_provider_util.h"
#include "qorai/browser/ui/qorai_browser_command_controller.h"
#include "chrome/browser/first_run/first_run.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#endif

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "qorai/components/request_otr/browser/request_otr_component_installer.h"
#include "qorai/components/request_otr/common/features.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_connection_manager.h"
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_ANDROID)
#include "qorai/browser/day_zero_browser_ui_expt/day_zero_browser_ui_expt_manager.h"
#endif

#if BUILDFLAG(IS_WIN)
#include "qorai/components/windows_recall/windows_recall.h"
#endif

using qorai_component_updater::QorAIComponent;
using ntp_background_images::NTPBackgroundImagesService;

namespace {

// Initializes callback for SystemRequestHandler
void InitSystemRequestHandlerCallback() {
  network::SystemRequestHandler::OnBeforeSystemRequestCallback
      before_system_request_callback =
          base::BindRepeating(qorai::OnBeforeSystemRequest);
  network::SystemRequestHandler::GetInstance()
      ->RegisterOnBeforeSystemRequestCallback(before_system_request_callback);
}

}  // namespace

using content::BrowserThread;

QorAIBrowserProcessImpl::~QorAIBrowserProcessImpl() = default;

QorAIBrowserProcessImpl::QorAIBrowserProcessImpl(StartupData* startup_data)
    : BrowserProcessImpl(startup_data) {
  g_browser_process = this;
  g_qorai_browser_process = this;

  // early initialize referrals
  qorai_referrals_service();

  // Disabled on mobile platforms, see for instance issues/6176
  // Create P3A Service early to catch more histograms. The full initialization
  // should be started once browser process impl is ready.
  p3a_service();
  histogram_qoraiizer_ = p3a::HistogramsQorAIizer::Create();

  // initialize ads stats helper
  ads_qorai_stats_helper();

  // early initialize qorai stats
  qorai_stats_updater();

  // early initialize misc metrics
  process_misc_metrics();
}

void QorAIBrowserProcessImpl::Init() {
  BrowserProcessImpl::Init();

  UpdateQorAIDarkMode();
  pref_change_registrar_.Add(
      kQorAIDarkMode,
      base::BindRepeating(&QorAIBrowserProcessImpl::OnQorAIDarkModeChanged,
                          base::Unretained(this)));

#if BUILDFLAG(ENABLE_TOR)
  pref_change_registrar_.Add(
      tor::prefs::kTorDisabled,
      base::BindRepeating(&QorAIBrowserProcessImpl::OnTorEnabledChanged,
                          base::Unretained(this)));
#endif

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_ANDROID)
  day_zero_browser_ui_expt_manager_ =
      DayZeroBrowserUIExptManager::Create(profile_manager());
#endif

  InitSystemRequestHandlerCallback();

#if !BUILDFLAG(IS_ANDROID)
  if (!ObsoleteSystem::IsObsoleteNowOrSoon()) {
    // Clear to show unsupported warning infobar again even if user
    // suppressed it from previous os.
    local_state()->ClearPref(prefs::kSuppressUnsupportedOSWarning);
  }

  qorai::PrepareSearchSuggestionsConfig(*local_state(),
                                        first_run::IsChromeFirstRun());
#endif
#if BUILDFLAG(IS_WIN)
  // Initializes the internal static data on start up.
  windows_recall::IsWindowsRecallDisabled(local_state());
#endif

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
  if (ai_chat::features::IsAIChatAgentProfileEnabled()) {
    CreateAIChatAgentProfileManager();
  }
#endif

  // Lazy initialization of AdBlockOnlyModePolicyManager
  qorai_policy::AdBlockOnlyModePolicyManager::GetInstance()->Init(
      local_state());
}

void QorAIBrowserProcessImpl::PreMainMessageLoopRun() {
  BrowserProcessImpl::PreMainMessageLoopRun();

  // Upstream initializes network_time_tracker() at PreMainMessageLoopRun()
  // right above. We are ready to init NetworkTimeHelper now.
  qorai_sync::NetworkTimeHelper::GetInstance()->SetNetworkTimeTracker(
      g_browser_process->network_time_tracker(),
      base::SingleThreadTaskRunner::GetCurrentDefault());
}

#if !BUILDFLAG(IS_ANDROID)
void QorAIBrowserProcessImpl::StartTearDown() {
  qorai_stats_helper_.reset();
  qorai_stats_updater_.reset();
  qorai_referrals_service_.reset();
  if (ntp_background_images_service_) {
    ntp_background_images_service_->StartTearDown();
  }
  if (p3a_service_) {
    p3a_service_->StartTeardown();
  }
#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
  ai_chat_agent_profile_manager_.reset();
#endif
  // Reset QorAIOriginPolicyManager to prevent dangling pointer to local_state_
  qorai_origin::QorAIOriginPolicyManager::GetInstance()->Shutdown();
  qorai_policy::AdBlockOnlyModePolicyManager::GetInstance()->Shutdown();
  qorai_sync::NetworkTimeHelper::GetInstance()->Shutdown();
  BrowserProcessImpl::StartTearDown();
}

void QorAIBrowserProcessImpl::PostDestroyThreads() {
  BrowserProcessImpl::PostDestroyThreads();
  // AdBlockService should outlive its own worker thread.
  ad_block_service_.reset();
}
#endif

qorai_component_updater::QorAIComponent::Delegate*
QorAIBrowserProcessImpl::qorai_component_updater_delegate() {
  if (!qorai_component_updater_delegate_) {
    qorai_component_updater_delegate_ = std::make_unique<
        qorai_component_updater::QorAIComponentUpdaterDelegate>(
        component_updater(), local_state(), GetApplicationLocale());
  }
  return qorai_component_updater_delegate_.get();
}

ProfileManager* QorAIBrowserProcessImpl::profile_manager() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (!created_profile_manager_) {
    CreateProfileManager();
  }
  return profile_manager_.get();
}

void QorAIBrowserProcessImpl::StartQorAIServices() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  resource_component();

  if (base::FeatureList::IsEnabled(net::features::kQorAIHttpsByDefault)) {
    https_upgrade_exceptions_service();
  }

  if (base::FeatureList::IsEnabled(
          webcompat::features::kQorAIWebcompatExceptionsService)) {
    webcompat::WebcompatExceptionsService::CreateInstance(
        local_data_files_service());
  }

  debounce_component_installer();
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  request_otr_component_installer();
#endif
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader_rewriter_service();
#endif
  URLSanitizerComponentInstaller();
  // Now start the local data files service, which calls all observers.
  local_data_files_service()->Start();

  qorai_wallet::WalletDataFilesInstaller::GetInstance().SetDelegate(
      std::make_unique<qorai_wallet::WalletDataFilesInstallerDelegateImpl>());
}

qorai_shields::AdBlockService* QorAIBrowserProcessImpl::ad_block_service() {
  if (!ad_block_service_) {
    scoped_refptr<base::SequencedTaskRunner> task_runner(
        base::ThreadPool::CreateSequencedTaskRunner(
            {base::MayBlock(), base::TaskPriority::USER_BLOCKING,
             base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN}));
    ad_block_service_ = std::make_unique<qorai_shields::AdBlockService>(
        local_state(), GetApplicationLocale(), component_updater(), task_runner,
        AdBlockSubscriptionDownloadManagerGetter(),
        profile_manager()->user_data_dir().Append(
            profile_manager()->GetInitialProfileDir()));
  }
  return ad_block_service_.get();
}

NTPBackgroundImagesService*
QorAIBrowserProcessImpl::ntp_background_images_service() {
  if (!ntp_background_images_service_) {
    ntp_background_images_service_ =
        std::make_unique<NTPBackgroundImagesService>(
            variations_service(), component_updater(), local_state());
    ntp_background_images_service_->Init();
  }

  return ntp_background_images_service_.get();
}

https_upgrade_exceptions::HttpsUpgradeExceptionsService*
QorAIBrowserProcessImpl::https_upgrade_exceptions_service() {
  if (!https_upgrade_exceptions_service_) {
    https_upgrade_exceptions_service_ =
        https_upgrade_exceptions::HttpsUpgradeExceptionsServiceFactory(
            local_data_files_service());
  }
  return https_upgrade_exceptions_service_.get();
}

debounce::DebounceComponentInstaller*
QorAIBrowserProcessImpl::debounce_component_installer() {
  if (!base::FeatureList::IsEnabled(debounce::features::kQorAIDebounce)) {
    return nullptr;
  }
  if (!debounce_component_installer_) {
    debounce_component_installer_ =
        std::make_unique<debounce::DebounceComponentInstaller>(
            local_data_files_service());
  }
  return debounce_component_installer_.get();
}

#if BUILDFLAG(ENABLE_REQUEST_OTR)
request_otr::RequestOTRComponentInstallerPolicy*
QorAIBrowserProcessImpl::request_otr_component_installer() {
  if (!base::FeatureList::IsEnabled(
          request_otr::features::kQorAIRequestOTRTab)) {
    return nullptr;
  }
  if (!request_otr_component_installer_) {
    request_otr_component_installer_ =
        std::make_unique<request_otr::RequestOTRComponentInstallerPolicy>(
            local_data_files_service());
  }
  return request_otr_component_installer_.get();
}
#endif

qorai::URLSanitizerComponentInstaller*
QorAIBrowserProcessImpl::URLSanitizerComponentInstaller() {
  if (!url_sanitizer_component_installer_) {
    url_sanitizer_component_installer_ =
        std::make_unique<qorai::URLSanitizerComponentInstaller>(
            local_data_files_service());
  }
  return url_sanitizer_component_installer_.get();
}

qorai_component_updater::LocalDataFilesService*
QorAIBrowserProcessImpl::local_data_files_service() {
  if (!local_data_files_service_) {
    local_data_files_service_ =
        qorai_component_updater::LocalDataFilesServiceFactory(
            qorai_component_updater_delegate());
  }
  return local_data_files_service_.get();
}

void QorAIBrowserProcessImpl::UpdateQorAIDarkMode() {
  // Update with proper system theme to make qorai theme and base ui components
  // theme use same theme.
  dark_mode::SetSystemDarkMode(dark_mode::GetQorAIDarkModeType());
}

void QorAIBrowserProcessImpl::OnQorAIDarkModeChanged() {
  UpdateQorAIDarkMode();
}

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
void QorAIBrowserProcessImpl::CreateAIChatAgentProfileManager() {
  CHECK(ai_chat::features::IsAIChatAgentProfileEnabled());
  ai_chat_agent_profile_manager_ =
      std::make_unique<ai_chat::AIChatAgentProfileManager>(profile_manager());
}
#endif

#if BUILDFLAG(ENABLE_TOR)
tor::QorAITorClientUpdater* QorAIBrowserProcessImpl::tor_client_updater() {
  if (tor_client_updater_) {
    return tor_client_updater_.get();
  }

  base::FilePath user_data_dir;
  base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);

  tor_client_updater_ = std::make_unique<tor::QorAITorClientUpdater>(
      qorai_component_updater_delegate(), local_state(), user_data_dir);
  return tor_client_updater_.get();
}

tor::QorAITorPluggableTransportUpdater*
QorAIBrowserProcessImpl::tor_pluggable_transport_updater() {
  if (!tor_pluggable_transport_updater_) {
    base::FilePath user_data_dir;
    base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);

    tor_pluggable_transport_updater_ =
        std::make_unique<tor::QorAITorPluggableTransportUpdater>(
            qorai_component_updater_delegate(), local_state(), user_data_dir);
  }
  return tor_pluggable_transport_updater_.get();
}

void QorAIBrowserProcessImpl::OnTorEnabledChanged() {
  // Update all browsers' tor command status.
  for (Browser* browser : *BrowserList::GetInstance()) {
    static_cast<chrome::QorAIBrowserCommandController*>(
        browser->command_controller())
        ->UpdateCommandForTor();
  }
}
#endif

p3a::P3AService* QorAIBrowserProcessImpl::p3a_service() {
  if (p3a_service_) {
    return p3a_service_.get();
  }
  p3a_service_ = base::MakeRefCounted<p3a::P3AService>(
      *local_state(), qorai::GetChannelName(),
      qorai_stats::GetFirstRunTime(local_state()),
      p3a::P3AConfig::LoadFromCommandLine());
  p3a_service()->InitCallbacks();
  return p3a_service_.get();
}

qorai::QorAIReferralsService*
QorAIBrowserProcessImpl::qorai_referrals_service() {
  if (!qorai_referrals_service_) {
    qorai_referrals_service_ = std::make_unique<qorai::QorAIReferralsService>(
        local_state(), qorai_stats::GetAPIKey(),
        qorai_stats::GetPlatformIdentifier());
    qorai_referrals_service_->set_delegate(
        std::make_unique<ReferralsServiceDelegate>(
            qorai_referrals_service_.get()));
  }
  return qorai_referrals_service_.get();
}

qorai_stats::QorAIStatsUpdater* QorAIBrowserProcessImpl::qorai_stats_updater() {
  if (!qorai_stats_updater_) {
    qorai_stats_updater_ = std::make_unique<qorai_stats::QorAIStatsUpdater>(
        local_state(), profile_manager());
  }
  return qorai_stats_updater_.get();
}

qorai_ads::QorAIStatsHelper* QorAIBrowserProcessImpl::ads_qorai_stats_helper() {
  if (!qorai_stats_helper_) {
    qorai_stats_helper_ = std::make_unique<qorai_ads::QorAIStatsHelper>(
        local_state(), profile_manager());
  }
  return qorai_stats_helper_.get();
}

qorai_ads::ResourceComponent* QorAIBrowserProcessImpl::resource_component() {
  if (!resource_component_) {
    resource_component_ = std::make_unique<qorai_ads::ResourceComponent>(
        qorai_component_updater_delegate());
  }
  return resource_component_.get();
}

void QorAIBrowserProcessImpl::CreateProfileManager() {
  DCHECK(!created_profile_manager_ && !profile_manager_);
  created_profile_manager_ = true;

  base::FilePath user_data_dir;
  base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir);
  profile_manager_ = std::make_unique<QorAIProfileManager>(user_data_dir);
}

NotificationPlatformBridge*
QorAIBrowserProcessImpl::notification_platform_bridge() {
  return BrowserProcessImpl::notification_platform_bridge();
}

#if BUILDFLAG(ENABLE_SPEEDREADER)
speedreader::SpeedreaderRewriterService*
QorAIBrowserProcessImpl::speedreader_rewriter_service() {
  if (!speedreader_rewriter_service_) {
    speedreader_rewriter_service_ =
        std::make_unique<speedreader::SpeedreaderRewriterService>();
  }
  return speedreader_rewriter_service_.get();
}
#endif  // BUILDFLAG(ENABLE_SPEEDREADER)

#if BUILDFLAG(ENABLE_QORAI_VPN)
qorai_vpn::QorAIVPNConnectionManager*
QorAIBrowserProcessImpl::qorai_vpn_connection_manager() {
  if (qorai_vpn_connection_manager_) {
    return qorai_vpn_connection_manager_.get();
  }

  qorai_vpn_connection_manager_ = qorai_vpn::CreateQorAIVPNConnectionManager(
      shared_url_loader_factory(), local_state());
  return qorai_vpn_connection_manager_.get();
}
#endif

misc_metrics::ProcessMiscMetrics*
QorAIBrowserProcessImpl::process_misc_metrics() {
  if (!process_misc_metrics_) {
    process_misc_metrics_ =
        std::make_unique<misc_metrics::ProcessMiscMetrics>(local_state());
  }
  return process_misc_metrics_.get();
}
