/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_crash_reporter_client.h"

#include <memory>
#include <string>

#include "base/debug/leak_annotations.h"
#include "base/file_version_info.h"
#include "base/notreached.h"
#include "base/strings/string_util.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_constants.h"
#include "qorai/browser/qorai_vpn/win/qorai_vpn_helper/qorai_vpn_helper_utils.h"
#include "chrome/install_static/install_util.h"
#include "chrome/install_static/product_install_details.h"
#include "chrome/install_static/user_data_dir.h"
#include "components/crash/core/app/crash_switches.h"
#include "components/crash/core/app/crashpad.h"
#include "components/version_info/channel.h"

namespace {
// Split into two places to avoid patching:
// chromium_src\components\crash\core\app\crashpad.cc
// Need keep it in sync.
constexpr char kQorAIVPNHelperProcessType[] = "qorai-vpn-helper";
}  // namespace

QorAIVPNHelperCrashReporterClient::QorAIVPNHelperCrashReporterClient() =
    default;

QorAIVPNHelperCrashReporterClient::~QorAIVPNHelperCrashReporterClient() =
    default;

// static
void QorAIVPNHelperCrashReporterClient::InitializeCrashReportingForProcess(
    const std::string& process_type) {
  static QorAIVPNHelperCrashReporterClient* instance = nullptr;
  if (instance) {
    return;
  }

  instance = new QorAIVPNHelperCrashReporterClient();
  ANNOTATE_LEAKING_OBJECT_PTR(instance);
  // Don't set up Crashpad crash reporting in the Crashpad handler itself, nor
  // in the fallback crash handler for the Crashpad handler process.
  if (process_type == crash_reporter::switches::kCrashpadHandler) {
    return;
  }
  install_static::InitializeProductDetailsForPrimaryModule();
  crash_reporter::SetCrashReporterClient(instance);

  crash_reporter::InitializeCrashpadWithEmbeddedHandler(
      true, kQorAIVPNHelperProcessType,
      install_static::WideToUTF8(
          qorai_vpn::GetVpnHelperServiceProfileDir().value()),
      base::FilePath());
}

bool QorAIVPNHelperCrashReporterClient::GetAlternativeCrashDumpLocation(
    std::wstring* crash_dir) {
  return false;
}

void QorAIVPNHelperCrashReporterClient::GetProductNameAndVersion(
    const std::wstring& exe_path,
    std::wstring* product_name,
    std::wstring* version,
    std::wstring* special_build,
    std::wstring* channel_name) {
  *product_name = qorai_vpn::GetQorAIVpnHelperServiceName();
  std::unique_ptr<FileVersionInfo> version_info(
      FileVersionInfo::CreateFileVersionInfo(base::FilePath(exe_path)));
  if (version_info) {
    *version = base::AsWString(version_info->product_version());
    *special_build = base::AsWString(version_info->special_build());
  } else {
    *version = L"0.0.0.0-devel";
    *special_build = std::wstring();
  }

  *channel_name =
      install_static::GetChromeChannelName(/*with_extended_stable=*/true);
}

bool QorAIVPNHelperCrashReporterClient::GetShouldDumpLargerDumps() {
  // Use large dumps for all but the stable channel.
  return install_static::GetChromeChannel() != version_info::Channel::STABLE;
}

bool QorAIVPNHelperCrashReporterClient::GetCrashDumpLocation(
    std::wstring* crash_dir) {
  auto profile_dir = qorai_vpn::GetVpnHelperServiceProfileDir();
  *crash_dir = (profile_dir.Append(L"Crashpad")).value();
  return !profile_dir.empty();
}

bool QorAIVPNHelperCrashReporterClient::GetCrashMetricsLocation(
    std::wstring* metrics_dir) {
  *metrics_dir = qorai_vpn::GetVpnHelperServiceProfileDir().value();
  return !metrics_dir->empty();
}

bool QorAIVPNHelperCrashReporterClient::IsRunningUnattended() {
  return false;
}

bool QorAIVPNHelperCrashReporterClient::GetCollectStatsConsent() {
  return install_static::GetCollectStatsConsent();
}

bool QorAIVPNHelperCrashReporterClient::GetCollectStatsInSample() {
  return install_static::GetCollectStatsInSample();
}

bool QorAIVPNHelperCrashReporterClient::ReportingIsEnforcedByPolicy(
    bool* enabled) {
  return install_static::ReportingIsEnforcedByPolicy(enabled);
}

bool QorAIVPNHelperCrashReporterClient::ShouldMonitorCrashHandlerExpensively() {
  // The expensive mechanism dedicates a process to be crashpad_handler's own
  // crashpad_handler.
  return false;
}

bool QorAIVPNHelperCrashReporterClient::EnableBreakpadForProcess(
    const std::string& process_type) {
  // This is not used by Crashpad (at least on Windows).
  NOTREACHED();
}
