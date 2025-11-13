/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_BROWSER_PROCESS_IMPL_H_
#define QORAI_BROWSER_QORAI_BROWSER_PROCESS_IMPL_H_

#include <memory>

#include "qorai/browser/qorai_browser_process.h"
#include "qorai/components/ai_chat/core/common/buildflags/buildflags.h"
#include "qorai/components/qorai_component_updater/browser/qorai_component.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/qorai_tor_pluggable_transport_updater.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/url_sanitizer/core/browser/url_sanitizer_component_installer.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process_impl.h"
#include "extensions/buildflags/buildflags.h"

namespace qorai {
class QorAIReferralsService;
}  // namespace qorai

namespace qorai_component_updater {
class LocalDataFilesService;
}  // namespace qorai_component_updater

namespace qorai_shields {
class AdBlockService;
}  // namespace qorai_shields

namespace https_upgrade_exceptions {
class HttpsUpgradeExceptionsService;
}  // namespace https_upgrade_exceptions

namespace qorai_stats {
class QorAIStatsUpdater;
}  // namespace qorai_stats

namespace debounce {
class DebounceComponentInstaller;
}  // namespace debounce

namespace misc_metrics {
class ProcessMiscMetrics;
}  // namespace misc_metrics

namespace request_otr {
#if BUILDFLAG(ENABLE_REQUEST_OTR)
class RequestOTRComponentInstallerPolicy;
#endif
}  // namespace request_otr

namespace ntp_background_images {
class NTPBackgroundImagesService;
}  // namespace ntp_background_images

namespace p3a {
class HistogramsQorAIizer;
class P3AService;
}  // namespace p3a

namespace tor {
class QorAITorClientUpdater;
class QorAITorPluggableTransportUpdater;
}  // namespace tor

namespace speedreader {
class SpeedreaderRewriterService;
}

namespace qorai_ads {
class QorAIStatsHelper;
class ResourceComponent;
}  // namespace qorai_ads

namespace ai_chat {
#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
class AIChatAgentProfileManager;
#endif
}  // namespace ai_chat

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_ANDROID)
class DayZeroBrowserUIExptManager;
#endif

class QorAIBrowserProcessImpl : public QorAIBrowserProcess,
                                public BrowserProcessImpl {
 public:
  explicit QorAIBrowserProcessImpl(StartupData* startup_data);
  QorAIBrowserProcessImpl(const QorAIBrowserProcessImpl&) = delete;
  QorAIBrowserProcessImpl& operator=(const QorAIBrowserProcessImpl&) = delete;
  ~QorAIBrowserProcessImpl() override;

  // BrowserProcess implementation.

  ProfileManager* profile_manager() override;
  NotificationPlatformBridge* notification_platform_bridge() override;

  // QorAIBrowserProcess implementation.

  void StartQorAIServices() override;
  qorai_shields::AdBlockService* ad_block_service() override;
  https_upgrade_exceptions::HttpsUpgradeExceptionsService*
  https_upgrade_exceptions_service() override;
  debounce::DebounceComponentInstaller* debounce_component_installer() override;
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  request_otr::RequestOTRComponentInstallerPolicy*
  request_otr_component_installer() override;
#endif
  qorai::URLSanitizerComponentInstaller* URLSanitizerComponentInstaller()
      override;
  qorai_component_updater::LocalDataFilesService* local_data_files_service()
      override;
#if BUILDFLAG(ENABLE_TOR)
  tor::QorAITorClientUpdater* tor_client_updater() override;
  tor::QorAITorPluggableTransportUpdater* tor_pluggable_transport_updater()
      override;
#endif
  p3a::P3AService* p3a_service() override;
  qorai::QorAIReferralsService* qorai_referrals_service() override;
  qorai_stats::QorAIStatsUpdater* qorai_stats_updater() override;
  qorai_ads::QorAIStatsHelper* ads_qorai_stats_helper() override;
  ntp_background_images::NTPBackgroundImagesService*
  ntp_background_images_service() override;
  qorai_ads::ResourceComponent* resource_component() override;
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderRewriterService* speedreader_rewriter_service()
      override;
#endif
#if BUILDFLAG(ENABLE_QORAI_VPN)
  qorai_vpn::QorAIVPNConnectionManager* qorai_vpn_connection_manager() override;
#endif
  misc_metrics::ProcessMiscMetrics* process_misc_metrics() override;

 private:
  // BrowserProcessImpl overrides:
  void Init() override;
  void PreMainMessageLoopRun() override;
#if !BUILDFLAG(IS_ANDROID)
  void StartTearDown() override;
  void PostDestroyThreads() override;
#endif

  void CreateProfileManager();

#if BUILDFLAG(ENABLE_TOR)
  void OnTorEnabledChanged();
#endif

  void UpdateQorAIDarkMode();
  void OnQorAIDarkModeChanged();

  void InitQorAIStatsHelper();

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
  void CreateAIChatAgentProfileManager();
#endif

  qorai_component_updater::QorAIComponent::Delegate*
  qorai_component_updater_delegate();

  // Sequence checker must stay on top to avoid UaF issues when data members use
  // `g_browser_process->profile_manager()`.
  SEQUENCE_CHECKER(sequence_checker_);

  // local_data_files_service_ should always be first because it needs
  // to be destroyed last
  std::unique_ptr<qorai_component_updater::LocalDataFilesService>
      local_data_files_service_;
  std::unique_ptr<qorai_component_updater::QorAIComponent::Delegate>
      qorai_component_updater_delegate_;
  std::unique_ptr<qorai_shields::AdBlockService> ad_block_service_;
  std::unique_ptr<https_upgrade_exceptions::HttpsUpgradeExceptionsService>
      https_upgrade_exceptions_service_;
  std::unique_ptr<debounce::DebounceComponentInstaller>
      debounce_component_installer_;
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  std::unique_ptr<request_otr::RequestOTRComponentInstallerPolicy>
      request_otr_component_installer_;
#endif
  std::unique_ptr<qorai::URLSanitizerComponentInstaller>
      url_sanitizer_component_installer_;
  std::unique_ptr<qorai_stats::QorAIStatsUpdater> qorai_stats_updater_;
  std::unique_ptr<qorai::QorAIReferralsService> qorai_referrals_service_;
#if BUILDFLAG(ENABLE_TOR)
  std::unique_ptr<tor::QorAITorClientUpdater> tor_client_updater_;
  std::unique_ptr<tor::QorAITorPluggableTransportUpdater>
      tor_pluggable_transport_updater_;
#endif
  scoped_refptr<p3a::P3AService> p3a_service_;
  scoped_refptr<p3a::HistogramsQorAIizer> histogram_qoraiizer_;
  std::unique_ptr<ntp_background_images::NTPBackgroundImagesService>
      ntp_background_images_service_;
  std::unique_ptr<qorai_ads::ResourceComponent> resource_component_;

#if BUILDFLAG(ENABLE_SPEEDREADER)
  std::unique_ptr<speedreader::SpeedreaderRewriterService>
      speedreader_rewriter_service_;
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
  std::unique_ptr<qorai_vpn::QorAIVPNConnectionManager>
      qorai_vpn_connection_manager_;
#endif

  std::unique_ptr<misc_metrics::ProcessMiscMetrics> process_misc_metrics_;
  std::unique_ptr<qorai_ads::QorAIStatsHelper> qorai_stats_helper_;

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_ANDROID)
  std::unique_ptr<DayZeroBrowserUIExptManager>
      day_zero_browser_ui_expt_manager_;
#endif

#if BUILDFLAG(ENABLE_QORAI_AI_CHAT_AGENT_PROFILE)
  std::unique_ptr<ai_chat::AIChatAgentProfileManager>
      ai_chat_agent_profile_manager_;
#endif
};

#endif  // QORAI_BROWSER_QORAI_BROWSER_PROCESS_IMPL_H_
