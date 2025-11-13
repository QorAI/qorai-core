/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// This interface is for managing the global services of the application. Each
// service is lazily created when requested the first time. The service getters
// will return NULL if the service is not available, so callers must check for
// this condition.

#ifndef QORAI_BROWSER_QORAI_BROWSER_PROCESS_H_
#define QORAI_BROWSER_QORAI_BROWSER_PROCESS_H_

#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/request_otr/common/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "build/build_config.h"
#include "extensions/buildflags/buildflags.h"

namespace qorai {
class QoraiReferralsService;
class URLSanitizerComponentInstaller;
}  // namespace qorai

#if BUILDFLAG(ENABLE_QORAI_VPN)
namespace qorai_vpn {
class QoraiVPNConnectionManager;
}  // namespace qorai_vpn
#endif

namespace qorai_component_updater {
class LocalDataFilesService;
}  // namespace qorai_component_updater

namespace qorai_shields {
class AdBlockService;
}  // namespace qorai_shields

namespace qorai_stats {
class QoraiStatsUpdater;
}  // namespace qorai_stats

namespace debounce {
class DebounceComponentInstaller;
}  // namespace debounce

namespace https_upgrade_exceptions {
class HttpsUpgradeExceptionsService;
}  // namespace https_upgrade_exceptions

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
class P3AService;
}  // namespace p3a

namespace tor {
class QoraiTorClientUpdater;
class QoraiTorPluggableTransportUpdater;
}  // namespace tor

namespace speedreader {
class SpeedreaderRewriterService;
}

namespace qorai_ads {
class QoraiStatsHelper;
class ResourceComponent;
}  // namespace qorai_ads

class QoraiBrowserProcess {
 public:
  QoraiBrowserProcess();
  virtual ~QoraiBrowserProcess();
  virtual void StartQoraiServices() = 0;
  virtual qorai_shields::AdBlockService* ad_block_service() = 0;
  virtual https_upgrade_exceptions::HttpsUpgradeExceptionsService*
  https_upgrade_exceptions_service() = 0;
  virtual debounce::DebounceComponentInstaller*
  debounce_component_installer() = 0;
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  virtual request_otr::RequestOTRComponentInstallerPolicy*
  request_otr_component_installer() = 0;
#endif
  virtual qorai::URLSanitizerComponentInstaller*
  URLSanitizerComponentInstaller() = 0;
  virtual qorai_component_updater::LocalDataFilesService*
  local_data_files_service() = 0;
#if BUILDFLAG(ENABLE_TOR)
  virtual tor::QoraiTorClientUpdater* tor_client_updater() = 0;
  virtual tor::QoraiTorPluggableTransportUpdater*
  tor_pluggable_transport_updater() = 0;
#endif
  virtual p3a::P3AService* p3a_service() = 0;
  virtual qorai::QoraiReferralsService* qorai_referrals_service() = 0;
  virtual qorai_stats::QoraiStatsUpdater* qorai_stats_updater() = 0;
  virtual qorai_ads::QoraiStatsHelper* ads_qorai_stats_helper() = 0;
  virtual ntp_background_images::NTPBackgroundImagesService*
  ntp_background_images_service() = 0;
#if BUILDFLAG(ENABLE_SPEEDREADER)
  virtual speedreader::SpeedreaderRewriterService*
  speedreader_rewriter_service() = 0;
#endif
#if BUILDFLAG(ENABLE_QORAI_VPN)
  virtual qorai_vpn::QoraiVPNConnectionManager*
  qorai_vpn_connection_manager() = 0;
#endif
  virtual qorai_ads::ResourceComponent* resource_component() = 0;
  virtual misc_metrics::ProcessMiscMetrics* process_misc_metrics() = 0;
};

extern QoraiBrowserProcess* g_qorai_browser_process;

#endif  // QORAI_BROWSER_QORAI_BROWSER_PROCESS_H_
