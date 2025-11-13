/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_privacy_handler.h"

#include "base/check.h"
#include "base/check_op.h"
#include "base/functional/bind.h"
#include "base/values.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/de_amp/common/features.h"
#include "qorai/components/debounce/core/common/features.h"
#include "qorai/components/google_sign_in_permission/google_sign_in_permission_util.h"
#include "qorai/components/p3a/pref_names.h"
#include "qorai/components/request_otr/common/buildflags/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "third_party/blink/public/common/peerconnection/webrtc_ip_handling_policy.h"

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "qorai/components/request_otr/common/features.h"
#endif

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
#include "qorai/browser/gcm_driver/qorai_gcm_channel_status.h"
#endif

#if BUILDFLAG(IS_WIN)
#include "qorai/components/windows_recall/windows_recall.h"
#endif

QoraiPrivacyHandler::QoraiPrivacyHandler() {
  local_state_change_registrar_.Init(g_browser_process->local_state());
  local_state_change_registrar_.Add(
      kStatsReportingEnabled,
      base::BindRepeating(&QoraiPrivacyHandler::OnStatsUsagePingEnabledChanged,
                          base::Unretained(this)));
  local_state_change_registrar_.Add(
      p3a::kP3AEnabled,
      base::BindRepeating(&QoraiPrivacyHandler::OnP3AEnabledChanged,
                          base::Unretained(this)));
#if BUILDFLAG(IS_WIN)
  if (windows_recall::IsWindowsRecallAvailable()) {
    local_state_change_registrar_.Add(
        windows_recall::prefs::kWindowsRecallDisabled,
        base::BindRepeating(
            &QoraiPrivacyHandler::OnWindowsRecallDisabledChanged,
            base::Unretained(this)));
  }
#endif
}

QoraiPrivacyHandler::~QoraiPrivacyHandler() {
  local_state_change_registrar_.RemoveAll();
}

void QoraiPrivacyHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());

  web_ui()->RegisterMessageCallback(
      "setP3AEnabled", base::BindRepeating(&QoraiPrivacyHandler::SetP3AEnabled,
                                           base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getP3AEnabled", base::BindRepeating(&QoraiPrivacyHandler::GetP3AEnabled,
                                           base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setStatsUsagePingEnabled",
      base::BindRepeating(&QoraiPrivacyHandler::SetStatsUsagePingEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getStatsUsagePingEnabled",
      base::BindRepeating(&QoraiPrivacyHandler::GetStatsUsagePingEnabled,
                          base::Unretained(this)));
#if BUILDFLAG(IS_WIN)
  if (windows_recall::IsWindowsRecallAvailable()) {
    web_ui()->RegisterMessageCallback(
        "isWindowsRecallDisabled",
        base::BindRepeating(&QoraiPrivacyHandler::GetLocalStateBooleanEnabled,
                            base::Unretained(this),
                            windows_recall::prefs::kWindowsRecallDisabled));
    web_ui()->RegisterMessageCallback(
        "setWindowsRecallDisabled",
        base::BindRepeating(&QoraiPrivacyHandler::SetLocalStateBooleanEnabled,
                            base::Unretained(this),
                            windows_recall::prefs::kWindowsRecallDisabled));
  }
#endif
}

// static
void QoraiPrivacyHandler::AddLoadTimeData(content::WebUIDataSource* data_source,
                                          Profile* profile) {
#if BUILDFLAG(USE_GCM_FROM_PLATFORM)
  data_source->AddBoolean("pushMessagingEnabledAtStartup", true);
#else
  gcm::QoraiGCMChannelStatus* gcm_channel_status =
      gcm::QoraiGCMChannelStatus::GetForProfile(profile);

  DCHECK(gcm_channel_status);
  data_source->AddBoolean("pushMessagingEnabledAtStartup",
                          gcm_channel_status->IsGCMEnabled());
#endif
  data_source->AddBoolean(
      "isDeAmpFeatureEnabled",
      base::FeatureList::IsEnabled(de_amp::features::kQoraiDeAMP));
  data_source->AddBoolean(
      "isDebounceFeatureEnabled",
      base::FeatureList::IsEnabled(debounce::features::kQoraiDebounce));
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  data_source->AddBoolean(
      "isRequestOTRFeatureEnabled",
      base::FeatureList::IsEnabled(request_otr::features::kQoraiRequestOTRTab));
#endif
  data_source->AddBoolean(
      "isGoogleSignInFeatureEnabled",
      google_sign_in_permission::IsGoogleSignInFeatureEnabled());
  data_source->AddBoolean(
      "isLocalhostAccessFeatureEnabled",
      base::FeatureList::IsEnabled(
          qorai_shields::features::kQoraiLocalhostAccessPermission));
  data_source->AddBoolean(
      "isOpenAIChatFromQoraiSearchEnabled",
      ai_chat::IsAIChatEnabled(profile->GetPrefs()) &&
          ai_chat::features::IsOpenAIChatFromQoraiSearchEnabled());
  auto* local_state = g_browser_process->local_state();
  data_source->AddBoolean(
      "isStatsReportingEnabledManaged",
      local_state->IsManagedPreference(kStatsReportingEnabled));
  data_source->AddBoolean("isP3AEnabledManaged",
                          local_state->IsManagedPreference(p3a::kP3AEnabled));

#if BUILDFLAG(IS_WIN)
  {
    data_source->AddBoolean("isWindowsRecallAvailable",
                            windows_recall::IsWindowsRecallAvailable());
    data_source->AddBoolean("windowsRecallDisabledAtStartup",
                            windows_recall::IsWindowsRecallDisabled(
                                g_browser_process->local_state()));
  }
#else
  data_source->AddBoolean("isWindowsRecallAvailable", false);
#endif
}

void QoraiPrivacyHandler::SetLocalStateBooleanEnabled(
    const std::string& path,
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  if (!args[0].is_bool()) {
    return;
  }

  bool enabled = args[0].GetBool();
  PrefService* local_state = g_browser_process->local_state();
  local_state->SetBoolean(path, enabled);
}

void QoraiPrivacyHandler::GetLocalStateBooleanEnabled(
    const std::string& path,
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);

  PrefService* local_state = g_browser_process->local_state();
  bool enabled = local_state->GetBoolean(path);

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(enabled));
}

void QoraiPrivacyHandler::SetStatsUsagePingEnabled(
    const base::Value::List& args) {
  SetLocalStateBooleanEnabled(kStatsReportingEnabled, args);
}

void QoraiPrivacyHandler::GetStatsUsagePingEnabled(
    const base::Value::List& args) {
  GetLocalStateBooleanEnabled(kStatsReportingEnabled, args);
}

void QoraiPrivacyHandler::OnStatsUsagePingEnabledChanged() {
  if (IsJavascriptAllowed()) {
    PrefService* local_state = g_browser_process->local_state();
    bool user_enabled = local_state->GetBoolean(kStatsReportingEnabled);
    bool is_managed = local_state->IsManagedPreference(kStatsReportingEnabled);

    FireWebUIListener("stats-usage-ping-enabled-changed", user_enabled,
                      is_managed);
  }
}

void QoraiPrivacyHandler::SetP3AEnabled(const base::Value::List& args) {
  SetLocalStateBooleanEnabled(p3a::kP3AEnabled, args);
}

void QoraiPrivacyHandler::GetP3AEnabled(const base::Value::List& args) {
  GetLocalStateBooleanEnabled(p3a::kP3AEnabled, args);
}

void QoraiPrivacyHandler::OnP3AEnabledChanged() {
  if (IsJavascriptAllowed()) {
    PrefService* local_state = g_browser_process->local_state();
    bool user_enabled = local_state->GetBoolean(p3a::kP3AEnabled);
    bool is_managed = local_state->IsManagedPreference(p3a::kP3AEnabled);

    FireWebUIListener("p3a-enabled-changed", user_enabled, is_managed);
  }
}

#if BUILDFLAG(IS_WIN)
void QoraiPrivacyHandler::OnWindowsRecallDisabledChanged() {
  CHECK(windows_recall::IsWindowsRecallAvailable());
  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("windows-recall-disabled-changed",
                    base::Value(g_browser_process->local_state()->GetBoolean(
                        windows_recall::prefs::kWindowsRecallDisabled)));
}
#endif
