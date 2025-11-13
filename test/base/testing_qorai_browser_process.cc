/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/test/base/testing_qorai_browser_process.h"

#include <utility>

#include "base/check.h"
#include "base/files/file_path.h"
#include "base/functional/callback_helpers.h"
#include "base/memory/scoped_refptr.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/thread_pool.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_manager.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_connection_manager.h"
#endif
namespace tor {
class QoraiTorClientUpdater;
}

// static
TestingQoraiBrowserProcess* TestingQoraiBrowserProcess::GetGlobal() {
  return static_cast<TestingQoraiBrowserProcess*>(g_qorai_browser_process);
}

// static
void TestingQoraiBrowserProcess::CreateInstance() {
  DCHECK(!g_qorai_browser_process);
  TestingQoraiBrowserProcess* process = new TestingQoraiBrowserProcess;
  g_qorai_browser_process = process;
}

// static
void TestingQoraiBrowserProcess::DeleteInstance() {
  QoraiBrowserProcess* browser_process = g_qorai_browser_process;
  g_qorai_browser_process = nullptr;
  delete browser_process;
}

// static
void TestingQoraiBrowserProcess::StartTearDown() {
  // Reset QoraiOriginPolicyManager to prevent dangling pointer to local_state_.
  qorai_origin::QoraiOriginPolicyManager::GetInstance()->Shutdown();
}

// static
void TestingQoraiBrowserProcess::TearDownAndDeleteInstance() {
  TestingQoraiBrowserProcess::StartTearDown();
  TestingQoraiBrowserProcess::DeleteInstance();
}

TestingQoraiBrowserProcess::TestingQoraiBrowserProcess() = default;

TestingQoraiBrowserProcess::~TestingQoraiBrowserProcess() = default;

void TestingQoraiBrowserProcess::StartQoraiServices() {}

qorai_shields::AdBlockService* TestingQoraiBrowserProcess::ad_block_service() {
  if (!ad_block_service_) {
    scoped_refptr<base::SequencedTaskRunner> task_runner(
        base::ThreadPool::CreateSequencedTaskRunner(
            {base::MayBlock(), base::TaskPriority::USER_BLOCKING,
             base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN}));
    ad_block_service_ = std::make_unique<qorai_shields::AdBlockService>(
        /*local_state*/ nullptr, /*locale*/ "en", /*component_updater*/ nullptr,
        task_runner,
        /*subscription_download_manager_getter*/ base::DoNothing(),
        /*profile_dir*/ base::FilePath(FILE_PATH_LITERAL("")));
  }
  return ad_block_service_.get();
}

debounce::DebounceComponentInstaller*
TestingQoraiBrowserProcess::debounce_component_installer() {
  return nullptr;
}

#if BUILDFLAG(ENABLE_REQUEST_OTR)
request_otr::RequestOTRComponentInstallerPolicy*
TestingQoraiBrowserProcess::request_otr_component_installer() {
  return nullptr;
}
#endif

qorai::URLSanitizerComponentInstaller*
TestingQoraiBrowserProcess::URLSanitizerComponentInstaller() {
  return nullptr;
}

https_upgrade_exceptions::HttpsUpgradeExceptionsService*
TestingQoraiBrowserProcess::https_upgrade_exceptions_service() {
  return nullptr;
}

qorai_component_updater::LocalDataFilesService*
TestingQoraiBrowserProcess::local_data_files_service() {
  return nullptr;
}

#if BUILDFLAG(ENABLE_TOR)
tor::QoraiTorClientUpdater* TestingQoraiBrowserProcess::tor_client_updater() {
  return nullptr;
}

tor::QoraiTorPluggableTransportUpdater*
TestingQoraiBrowserProcess::tor_pluggable_transport_updater() {
  return nullptr;
}
#endif

p3a::P3AService* TestingQoraiBrowserProcess::p3a_service() {
  return nullptr;
}

qorai::QoraiReferralsService*
TestingQoraiBrowserProcess::qorai_referrals_service() {
  return nullptr;
}

qorai_stats::QoraiStatsUpdater*
TestingQoraiBrowserProcess::qorai_stats_updater() {
  return nullptr;
}

qorai_ads::QoraiStatsHelper*
TestingQoraiBrowserProcess::ads_qorai_stats_helper() {
  return nullptr;
}

ntp_background_images::NTPBackgroundImagesService*
TestingQoraiBrowserProcess::ntp_background_images_service() {
  return nullptr;
}

#if BUILDFLAG(ENABLE_SPEEDREADER)
speedreader::SpeedreaderRewriterService*
TestingQoraiBrowserProcess::speedreader_rewriter_service() {
  return nullptr;
}
#endif

qorai_ads::ResourceComponent* TestingQoraiBrowserProcess::resource_component() {
  return nullptr;
}

#if BUILDFLAG(ENABLE_QORAI_VPN)
qorai_vpn::QoraiVPNConnectionManager*
TestingQoraiBrowserProcess::qorai_vpn_connection_manager() {
  return qorai_vpn_connection_manager_.get();
}
void TestingQoraiBrowserProcess::SetQoraiVPNConnectionManagerForTesting(
    std::unique_ptr<qorai_vpn::QoraiVPNConnectionManager> manager) {
  qorai_vpn_connection_manager_ = std::move(manager);
}
#endif

misc_metrics::ProcessMiscMetrics*
TestingQoraiBrowserProcess::process_misc_metrics() {
  return nullptr;
}

void TestingQoraiBrowserProcess::SetAdBlockService(
    std::unique_ptr<qorai_shields::AdBlockService> service) {
  ad_block_service_ = std::move(service);
}
///////////////////////////////////////////////////////////////////////////////

TestingQoraiBrowserProcessInitializer::TestingQoraiBrowserProcessInitializer() {
  TestingQoraiBrowserProcess::CreateInstance();
}

TestingQoraiBrowserProcessInitializer::
    ~TestingQoraiBrowserProcessInitializer() {
  TestingQoraiBrowserProcess::DeleteInstance();
}
