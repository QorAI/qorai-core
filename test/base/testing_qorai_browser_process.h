/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// An implementation of QoraiBrowserProcess for unit tests that fails for most
// services. By preventing creation of services, we reduce dependencies and
// keep the profile clean. Clients of this class must handle the NULL return
// value, however.

#ifndef QORAI_TEST_BASE_TESTING_QORAI_BROWSER_PROCESS_H_
#define QORAI_TEST_BASE_TESTING_QORAI_BROWSER_PROCESS_H_

#include <stdint.h>

#include <memory>
#include <string>

#include "qorai/browser/qorai_browser_process.h"

namespace qorai_shields {
class AdBlockService;
}

namespace qorai_vpn {
class QoraiVPNConnectionManager;
}

class TestingQoraiBrowserProcess : public QoraiBrowserProcess {
 public:
  // Initializes |g_qorai_browser_process| with a new
  // TestingQoraiBrowserProcess.
  static void CreateInstance();

  // Cleanly destroys |g_qorai_browser_process|.
  static void DeleteInstance();

  // Convenience method to get g_qorai_browser_process as a
  // TestingQoraiBrowserProcess*.
  static TestingQoraiBrowserProcess* GetGlobal();

  // Convenience method to both teardown and destroy the TestingBrowserProcess
  // instance
  static void TearDownAndDeleteInstance();

  TestingQoraiBrowserProcess(const TestingQoraiBrowserProcess&) = delete;
  TestingQoraiBrowserProcess& operator=(const TestingQoraiBrowserProcess&) =
      delete;

  // QoraiBrowserProcess overrides:
  void StartQoraiServices() override;
  qorai_shields::AdBlockService* ad_block_service() override;
  debounce::DebounceComponentInstaller* debounce_component_installer() override;
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  request_otr::RequestOTRComponentInstallerPolicy*
  request_otr_component_installer() override;
#endif
  qorai::URLSanitizerComponentInstaller* URLSanitizerComponentInstaller()
      override;
  https_upgrade_exceptions::HttpsUpgradeExceptionsService*
  https_upgrade_exceptions_service() override;
  qorai_component_updater::LocalDataFilesService* local_data_files_service()
      override;
#if BUILDFLAG(ENABLE_TOR)
  tor::QoraiTorClientUpdater* tor_client_updater() override;
  tor::QoraiTorPluggableTransportUpdater* tor_pluggable_transport_updater()
      override;
#endif
  p3a::P3AService* p3a_service() override;
  qorai::QoraiReferralsService* qorai_referrals_service() override;
  qorai_stats::QoraiStatsUpdater* qorai_stats_updater() override;
  qorai_ads::QoraiStatsHelper* ads_qorai_stats_helper() override;
  ntp_background_images::NTPBackgroundImagesService*
  ntp_background_images_service() override;
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderRewriterService* speedreader_rewriter_service()
      override;
#endif
  qorai_ads::ResourceComponent* resource_component() override;
#if BUILDFLAG(ENABLE_QORAI_VPN)
  qorai_vpn::QoraiVPNConnectionManager* qorai_vpn_connection_manager() override;
  void SetQoraiVPNConnectionManagerForTesting(
      std::unique_ptr<qorai_vpn::QoraiVPNConnectionManager> manager);
#endif
  misc_metrics::ProcessMiscMetrics* process_misc_metrics() override;

  // Populate the mock process with services. Consumer is responsible for
  // cleaning these up after completion of a test.
  void SetAdBlockService(std::unique_ptr<qorai_shields::AdBlockService>);

 private:
  // Perform necessary cleanup prior to destruction of |g_browser_process|
  static void StartTearDown();

  // See CreateInstance() and DestroyInstance() above.
  TestingQoraiBrowserProcess();
  ~TestingQoraiBrowserProcess() override;

  std::unique_ptr<qorai_shields::AdBlockService> ad_block_service_;

#if BUILDFLAG(ENABLE_QORAI_VPN)
  std::unique_ptr<qorai_vpn::QoraiVPNConnectionManager>
      qorai_vpn_connection_manager_;
#endif
};

class TestingQoraiBrowserProcessInitializer {
 public:
  TestingQoraiBrowserProcessInitializer();
  TestingQoraiBrowserProcessInitializer(
      const TestingQoraiBrowserProcessInitializer&) = delete;
  TestingQoraiBrowserProcessInitializer& operator=(
      const TestingQoraiBrowserProcessInitializer&) = delete;
  ~TestingQoraiBrowserProcessInitializer();
};

#endif  // QORAI_TEST_BASE_TESTING_QORAI_BROWSER_PROCESS_H_
