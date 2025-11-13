/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_browser_main_extra_parts.h"

#include "base/metrics/histogram_macros.h"
#include "qorai/browser/qorai_browser_process_impl.h"
#include "qorai/browser/misc_metrics/process_misc_metrics.h"
#include "qorai/browser/misc_metrics/uptime_monitor_impl.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/p3a/p3a_service.h"
#include "components/metrics/metrics_pref_names.h"
#include "components/prefs/pref_service.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/importer/qorai_importer_p3a.h"
#include "qorai/browser/p3a/p3a_core_metrics.h"
#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_message_handler.h"
#include "chrome/browser/first_run/first_run.h"
#endif  // !BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "extensions/common/extension.h"
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)

namespace {

// Records default values for some histograms because we want these stats to be
// uploaded anyways. Corresponding components will write new values according
// to their usage scenarios.
//
// For profile specific values, see browser/profiles/profile_util.cc
void RecordInitialP3AValues() {
#if !BUILDFLAG(IS_ANDROID)
  if (first_run::IsChromeFirstRun()) {
    RecordImporterP3A(user_data_importer::ImporterType::TYPE_UNKNOWN);
  }

  QoraiNewTabMessageHandler::RecordInitialP3AValues(
      g_browser_process->local_state());
#endif  // !BUILDFLAG(IS_ANDROID)

  qorai_shields::MaybeRecordShieldsUsageP3A(qorai_shields::kNeverClicked,
                                            g_browser_process->local_state());

  // Record crash reporting status stats.
  const bool crash_reports_enabled = g_browser_process->local_state()->
      GetBoolean(metrics::prefs::kMetricsReportingEnabled);
  UMA_HISTOGRAM_BOOLEAN("Qorai.Core.CrashReportsEnabled",
                        crash_reports_enabled);
}

}  // namespace

QoraiBrowserMainExtraParts::QoraiBrowserMainExtraParts() = default;

QoraiBrowserMainExtraParts::~QoraiBrowserMainExtraParts() = default;

void QoraiBrowserMainExtraParts::PreProfileInit() {
#if BUILDFLAG(ENABLE_EXTENSIONS)
  // Disable warnings related to Manifest V2 deprecation
  extensions::Extension::
      set_silence_deprecated_manifest_version_warnings_for_testing(true);
#endif  // BUILDFLAG(ENABLE_EXTENSIONS)
}

void QoraiBrowserMainExtraParts::PostBrowserStart() {
  g_qorai_browser_process->StartQoraiServices();
}

void QoraiBrowserMainExtraParts::PreMainMessageLoopRun() {
  // Disabled on mobile platforms, see for instance issues/6176
  if (g_qorai_browser_process->p3a_service() != nullptr) {
    // TODO(iefremov): Maybe find a better place for this initialization.
    g_qorai_browser_process->p3a_service()->Init(
        g_browser_process->shared_url_loader_factory(),
        g_browser_process->component_updater());
  }

  RecordInitialP3AValues();

  // The code below is not supported on android.
#if !BUILDFLAG(IS_ANDROID)
  qorai::QoraiWindowTracker::CreateInstance(g_browser_process->local_state());
#endif  // !BUILDFLAG(IS_ANDROID)
  g_qorai_browser_process->process_misc_metrics()->uptime_monitor()->Init();
}
