/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"

#include <string>
#include <utility>

#include "base/check_deref.h"
#include "base/i18n/number_formatting.h"
#include "base/metrics/histogram_macros.h"
#include "base/notreached.h"
#include "base/strings/utf_string_conversions.h"
#include "base/types/cxx23_to_underlying.h"
#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/browser/qorai_shields/qorai_shields_web_contents_observer.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_locale_utils.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/qorai_shield_constants.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/favicon/content/content_favicon_driver.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/reload_type.h"
#include "content/public/browser/web_contents.h"
#include "net/base/features.h"
#include "net/base/url_util.h"

using net::AppendQueryParameter;

namespace {

constexpr char kShieldsAllowScriptOnceHistogramName[] =
    "QorAI.Shields.AllowScriptOnce";

}  // namespace

bool IsAdBlockOnlyModeSupportedAndFeatureEnabled() {
  return base::FeatureList::IsEnabled(
             qorai_shields::features::kAdblockOnlyMode) &&
         qorai_shields::IsAdblockOnlyModeSupportedForLocale(
             g_browser_process->GetApplicationLocale());
}

namespace qorai_shields {

QorAIShieldsTabHelper::~QorAIShieldsTabHelper() = default;

QorAIShieldsTabHelper::QorAIShieldsTabHelper(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents),
      content::WebContentsUserData<QorAIShieldsTabHelper>(*web_contents),
      host_content_settings_map_(
          CHECK_DEREF(HostContentSettingsMapFactory::GetForProfile(
              web_contents->GetBrowserContext()))),
      qorai_shields_settings_(
          CHECK_DEREF(QorAIShieldsSettingsServiceFactory::GetForProfile(
              Profile::FromBrowserContext(
                  web_contents->GetBrowserContext())))) {
  favicon::ContentFaviconDriver::FromWebContents(web_contents)
      ->AddObserver(this);
  observation_.Observe(&*host_content_settings_map_);
  local_state_change_registrar_.Init(g_browser_process->local_state());
  local_state_change_registrar_.Add(
      qorai_shields::prefs::kAdBlockOnlyModeEnabled,
      base::BindRepeating(
          &QorAIShieldsTabHelper::OnShieldsAdBlockOnlyModeEnabledChanged,
          base::Unretained(this)));
}

void QorAIShieldsTabHelper::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  if (navigation_handle->IsInMainFrame() && navigation_handle->HasCommitted() &&
      !navigation_handle->IsSameDocument()) {
    if (navigation_handle->GetReloadType() != content::ReloadType::NORMAL) {
      // We are navigating to a new page or force-reloading. Therefore, clear
      // the webcompat features listed.
      webcompat_features_invoked_.clear();
    }
    ClearAllResourcesList();

    if (!navigation_triggered_by_shields_changes_) {
      MaybeNotifyRepeatedReloads(navigation_handle);
    }

    navigation_triggered_by_shields_changes_ = false;
  }
}

void QorAIShieldsTabHelper::MaybeNotifyRepeatedReloads(
    content::NavigationHandle* navigation_handle) {
  if (!IsAdBlockOnlyModeSupportedAndFeatureEnabled() ||
      g_browser_process->local_state()->GetBoolean(
          qorai_shields::prefs::kAdBlockOnlyModeEnabled)) {
    // Do not notify if ad block only mode feature is disabled or shields ad
    // block only mode is already enabled.
    return;
  }

  const PrefService* prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();
  if (prefs->GetBoolean(
          qorai_shields::prefs::kAdBlockOnlyModePromptDismissed)) {
    // Do not notify if the prompt has been dismissed.
    return;
  }

  if (navigation_handle->GetRestoreType() == content::RestoreType::kRestored) {
    // Do not notify if the navigation is a restore.
    return;
  }

  if (!PageTransitionCoreTypeIs(navigation_handle->GetPageTransition(),
                                ui::PAGE_TRANSITION_RELOAD)) {
    // Do not notify if the navigation is not a reload.
    return;
  }

  const base::Time current_time = base::Time::Now();
  if (!repeated_reloads_counter_ ||
      current_time - repeated_reloads_counter_->initial_reload_at >
          features::kAdblockOnlyModePromptAfterPageReloadsInterval.Get()) {
    repeated_reloads_counter_ = RepeatedReloadsCounter{
        .initial_reload_at = current_time,
        .reloads_count = 0,
    };
  }

  // If the page is reloaded between `kAdblockOnlyModePromptAfterPageReloadsMin`
  // and `kAdblockOnlyModePromptAfterPageReloadsMax` times in
  // `kAdblockOnlyModePromptAfterPageReloadsInterval`, notify observers.
  repeated_reloads_counter_->reloads_count++;
  if (repeated_reloads_counter_->reloads_count >=
          features::kAdblockOnlyModePromptAfterPageReloadsMin.Get() &&
      repeated_reloads_counter_->reloads_count <=
          features::kAdblockOnlyModePromptAfterPageReloadsMax.Get()) {
    for (Observer& observer : observer_list_) {
      observer.OnRepeatedReloadsDetected();
    }
  }
}

void QorAIShieldsTabHelper::OnShieldsAdBlockOnlyModeEnabledChanged() {
  for (Observer& observer : observer_list_) {
    observer.OnShieldsAdBlockOnlyModeEnabledChanged();
  }
}

void QorAIShieldsTabHelper::WebContentsDestroyed() {
  favicon::ContentFaviconDriver::FromWebContents(web_contents())
      ->RemoveObserver(this);
  observation_.Reset();
}

void QorAIShieldsTabHelper::OnContentSettingChanged(
    const ContentSettingsPattern& primary_pattern,
    const ContentSettingsPattern& secondary_pattern,
    ContentSettingsTypeSet content_type_set) {
  if ((content_type_set.ContainsAllTypes() ||
       content_type_set.GetType() == ContentSettingsType::QORAI_SHIELDS) &&
      primary_pattern.Matches(GetCurrentSiteURL())) {
    for (Observer& obs : observer_list_) {
      obs.OnShieldsEnabledChanged();
    }
  }
}

void QorAIShieldsTabHelper::OnFaviconUpdated(
    favicon::FaviconDriver* favicon_driver,
    NotificationIconType notification_icon_type,
    const GURL& icon_url,
    bool icon_url_changed,
    const gfx::Image& image) {
  for (Observer& obs : observer_list_) {
    obs.OnFaviconUpdated();
  }
}

void QorAIShieldsTabHelper::ReloadWebContents() {
  navigation_triggered_by_shields_changes_ = true;

  web_contents()->GetController().Reload(content::ReloadType::NORMAL, true);
}

void QorAIShieldsTabHelper::ClearAllResourcesList() {
  resource_list_blocked_ads_.clear();
  resource_list_http_redirects_.clear();
  resource_list_blocked_js_.clear();
  resource_list_blocked_fingerprints_.clear();
  resource_list_allowed_once_js_.clear();

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void QorAIShieldsTabHelper::AddObserver(Observer* obs) {
  observer_list_.AddObserver(obs);
}

void QorAIShieldsTabHelper::RemoveObserver(Observer* obs) {
  observer_list_.RemoveObserver(obs);
}

bool QorAIShieldsTabHelper::HasObserver(Observer* observer) {
  return observer_list_.HasObserver(observer);
}

int QorAIShieldsTabHelper::GetTotalBlockedCount() {
  return (resource_list_blocked_ads_.size() +
          resource_list_http_redirects_.size() +
          resource_list_blocked_js_.size() +
          resource_list_blocked_fingerprints_.size());
}

std::vector<GURL> QorAIShieldsTabHelper::GetBlockedAdsList() {
  std::vector<GURL> blocked_ads(resource_list_blocked_ads_.begin(),
                                resource_list_blocked_ads_.end());

  return blocked_ads;
}

std::vector<GURL> QorAIShieldsTabHelper::GetHttpRedirectsList() {
  std::vector<GURL> http_redirects(resource_list_http_redirects_.begin(),
                                   resource_list_http_redirects_.end());

  return http_redirects;
}

std::vector<GURL> QorAIShieldsTabHelper::GetBlockedJsList() {
  std::vector<GURL> js_list(resource_list_blocked_js_.begin(),
                            resource_list_blocked_js_.end());
  return js_list;
}

std::vector<GURL> QorAIShieldsTabHelper::GetAllowedJsList() {
  std::vector<GURL> js_list(resource_list_allowed_once_js_.begin(),
                            resource_list_allowed_once_js_.end());
  return js_list;
}

std::vector<GURL> QorAIShieldsTabHelper::GetFingerprintsList() {
  std::vector<GURL> fingerprints_list(
      resource_list_blocked_fingerprints_.begin(),
      resource_list_blocked_fingerprints_.end());

  return fingerprints_list;
}

const base::flat_set<ContentSettingsType>&
QorAIShieldsTabHelper::GetInvokedWebcompatFeatures() {
  return webcompat_features_invoked_;
}

bool QorAIShieldsTabHelper::GetQorAIShieldsEnabled() {
  return qorai_shields_settings_->GetQorAIShieldsEnabled(GetCurrentSiteURL());
}

void QorAIShieldsTabHelper::SetQorAIShieldsEnabled(bool is_enabled) {
  qorai_shields_settings_->SetQorAIShieldsEnabled(is_enabled,
                                                  GetCurrentSiteURL());

  if (IsAdBlockOnlyModeSupportedAndFeatureEnabled() && !is_enabled) {
    PrefService* prefs =
        Profile::FromBrowserContext(web_contents()->GetBrowserContext())
            ->GetPrefs();
    prefs->SetInteger(
        qorai_shields::prefs::kShieldsDisabledCount,
        prefs->GetInteger(qorai_shields::prefs::kShieldsDisabledCount) + 1);
  }

  ReloadWebContents();
}

bool QorAIShieldsTabHelper::IsQorAIShieldsAdBlockOnlyModeEnabled() {
  return IsAdBlockOnlyModeSupportedAndFeatureEnabled() &&
         g_browser_process->local_state()->GetBoolean(
             qorai_shields::prefs::kAdBlockOnlyModeEnabled);
}

void QorAIShieldsTabHelper::SetQorAIShieldsAdBlockOnlyModeEnabled(
    bool is_enabled) {
  g_browser_process->local_state()->SetBoolean(
      qorai_shields::prefs::kAdBlockOnlyModeEnabled, is_enabled);
  ReloadWebContents();
}

bool QorAIShieldsTabHelper::ShouldShowShieldsDisabledAdBlockOnlyModePrompt() {
  PrefService* prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();
  return IsAdBlockOnlyModeSupportedAndFeatureEnabled() &&
         !prefs->GetBoolean(
             qorai_shields::prefs::kAdBlockOnlyModePromptDismissed) &&
         prefs->GetInteger(qorai_shields::prefs::kShieldsDisabledCount) >=
             features::kAdblockOnlyModePromptAfterShieldsDisabledCount.Get();
}

void QorAIShieldsTabHelper::SetQorAIShieldsAdBlockOnlyModePromptDismissed() {
  PrefService* prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();
  prefs->SetBoolean(qorai_shields::prefs::kAdBlockOnlyModePromptDismissed,
                    true);
}

GURL QorAIShieldsTabHelper::GetCurrentSiteURL() const {
  return web_contents()->GetLastCommittedURL();
}

GURL QorAIShieldsTabHelper::GetFaviconURL(bool refresh) {
  auto url = GURL("chrome://favicon2/");
  url = AppendQueryParameter(url, "size", "16");
  url = AppendQueryParameter(url, "scaleFactor", "2x");
  url = AppendQueryParameter(url, "showFallbackMonogram", "");
  url = AppendQueryParameter(url, "pageUrl",
                             GetCurrentSiteURL().GetWithoutFilename().spec());

  if (refresh) {
    url = AppendQueryParameter(
        url, "v",
        base::UTF16ToUTF8(base::FormatNumber(
            base::Time::Now().InMillisecondsFSinceUnixEpoch())));
  }

  return url;
}

AdBlockMode QorAIShieldsTabHelper::GetAdBlockMode() {
  return qorai_shields_settings_->GetAdBlockMode(GetCurrentSiteURL());
}

FingerprintMode QorAIShieldsTabHelper::GetFingerprintMode() {
  return qorai_shields_settings_->GetFingerprintMode(GetCurrentSiteURL());
}

CookieBlockMode QorAIShieldsTabHelper::GetCookieBlockMode() {
  auto cookie_settings = CookieSettingsFactory::GetForProfile(
      Profile::FromBrowserContext(web_contents()->GetBrowserContext()));

  const ControlType control_type = qorai_shields::GetCookieControlType(
      &*host_content_settings_map_, cookie_settings.get(), GetCurrentSiteURL());

  switch (control_type) {
    case ControlType::ALLOW:
      return CookieBlockMode::ALLOW;
    case ControlType::BLOCK_THIRD_PARTY:
      return CookieBlockMode::CROSS_SITE_BLOCKED;
    case ControlType::BLOCK:
      return CookieBlockMode::BLOCKED;
    case ControlType::DEFAULT:
      break;
  }
  NOTREACHED() << "Unexpected value for control_type: "
               << base::to_underlying(control_type);
}

HttpsUpgradeMode QorAIShieldsTabHelper::GetHttpsUpgradeMode() {
  ControlType control_type = qorai_shields::GetHttpsUpgradeControlType(
      &*host_content_settings_map_, GetCurrentSiteURL());
  if (control_type == ControlType::ALLOW) {
    return HttpsUpgradeMode::DISABLED_MODE;
  } else if (control_type == ControlType::BLOCK) {
    return HttpsUpgradeMode::STRICT_MODE;
  } else if (control_type == ControlType::BLOCK_THIRD_PARTY) {
    return HttpsUpgradeMode::STANDARD_MODE;
  } else {
    return HttpsUpgradeMode::STANDARD_MODE;
  }
}

bool QorAIShieldsTabHelper::GetNoScriptEnabled() {
  return qorai_shields_settings_->IsNoScriptEnabled(GetCurrentSiteURL());
}

mojom::ContentSettingsOverriddenDataPtr
QorAIShieldsTabHelper::GetJsContentSettingsOverriddenData() {
  return qorai_shields_settings_->GetJsContentSettingOverriddenData(
      GetCurrentSiteURL());
}

bool QorAIShieldsTabHelper::GetForgetFirstPartyStorageEnabled() {
  return qorai_shields_settings_->GetForgetFirstPartyStorageEnabled(
      GetCurrentSiteURL());
}

void QorAIShieldsTabHelper::SetAdBlockMode(AdBlockMode mode) {
  qorai_shields_settings_->SetAdBlockMode(mode, GetCurrentSiteURL());

  ReloadWebContents();
}

void QorAIShieldsTabHelper::SetFingerprintMode(FingerprintMode mode) {
  qorai_shields_settings_->SetFingerprintMode(mode, GetCurrentSiteURL());

  ReloadWebContents();
}

void QorAIShieldsTabHelper::SetCookieBlockMode(CookieBlockMode mode) {
  auto* prefs = Profile::FromBrowserContext(web_contents()->GetBrowserContext())
                    ->GetPrefs();
  ControlType control_type = ControlType::BLOCK;

  switch (mode) {
    case CookieBlockMode::ALLOW:
      control_type = ControlType::ALLOW;
      break;
    case CookieBlockMode::CROSS_SITE_BLOCKED:
      control_type = ControlType::BLOCK_THIRD_PARTY;
      break;
    case CookieBlockMode::BLOCKED:
      control_type = ControlType::BLOCK;
      break;
  }

  qorai_shields::SetCookieControlType(&*host_content_settings_map_, prefs,
                                      control_type, GetCurrentSiteURL(),
                                      g_browser_process->local_state());

  ReloadWebContents();
}

void QorAIShieldsTabHelper::SetHttpsUpgradeMode(HttpsUpgradeMode mode) {
  ControlType control_type;
  if (mode == HttpsUpgradeMode::DISABLED_MODE) {
    control_type = ControlType::ALLOW;
  } else if (mode == HttpsUpgradeMode::STRICT_MODE) {
    control_type = ControlType::BLOCK;
  } else if (mode == HttpsUpgradeMode::STANDARD_MODE) {
    control_type = ControlType::BLOCK_THIRD_PARTY;
  } else {
    control_type = ControlType::DEFAULT;
  }
  qorai_shields::SetHttpsUpgradeControlType(&*host_content_settings_map_,
                                            control_type, GetCurrentSiteURL(),
                                            g_browser_process->local_state());

  ReloadWebContents();
}

void QorAIShieldsTabHelper::SetIsNoScriptEnabled(bool is_enabled) {
  qorai_shields_settings_->SetNoScriptEnabled(is_enabled, GetCurrentSiteURL());

  ReloadWebContents();
}

void QorAIShieldsTabHelper::SetForgetFirstPartyStorageEnabled(bool is_enabled) {
  qorai_shields_settings_->SetForgetFirstPartyStorageEnabled(
      is_enabled, GetCurrentSiteURL());
}

void QorAIShieldsTabHelper::BlockAllowedScripts(
    const std::vector<std::string>& origins) {
  QorAIShieldsWebContentsObserver* observer =
      QorAIShieldsWebContentsObserver::FromWebContents(web_contents());
  if (!observer) {
    return;
  }
  observer->BlockAllowedScripts(origins);
  ReloadWebContents();
}

void QorAIShieldsTabHelper::AllowScriptsOnce(
    const std::vector<std::string>& origins) {
  QorAIShieldsWebContentsObserver* observer =
      QorAIShieldsWebContentsObserver::FromWebContents(web_contents());
  if (!observer) {
    return;
  }
  UMA_HISTOGRAM_BOOLEAN(kShieldsAllowScriptOnceHistogramName, true);
  observer->AllowScriptsOnce(origins);
  ReloadWebContents();
}

bool QorAIShieldsTabHelper::IsQorAIShieldsManaged() {
  PrefService* profile_prefs =
      Profile::FromBrowserContext(web_contents()->GetBrowserContext())
          ->GetPrefs();

  return qorai_shields::IsQorAIShieldsManaged(
      profile_prefs, &*host_content_settings_map_, GetCurrentSiteURL());
}

void QorAIShieldsTabHelper::HandleItemBlocked(const std::string& block_type,
                                              const std::string& subresource) {
  auto subres = GURL(subresource);

  if (block_type == kAds) {
    resource_list_blocked_ads_.insert(subres);
  } else if (block_type == kHTTPUpgradableResources) {
    resource_list_http_redirects_.insert(subres);
  } else if (block_type == kJavaScript) {
    resource_list_blocked_js_.insert(subres);
  } else if (block_type == kFingerprintingV2) {
    resource_list_blocked_fingerprints_.insert(subres);
  }

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void QorAIShieldsTabHelper::HandleItemAllowedOnce(
    const std::string& allowed_once_type,
    const std::string& subresource) {
  GURL subres(subresource);
  if (allowed_once_type != kJavaScript) {
    return;
  }
  if (resource_list_allowed_once_js_.contains(subres)) {
    return;
  }
  resource_list_allowed_once_js_.insert(std::move(subres));

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void QorAIShieldsTabHelper::HandleWebcompatFeatureInvoked(
    ContentSettingsType webcompat_content_settings) {
  if (webcompat_content_settings > ContentSettingsType::QORAI_WEBCOMPAT_NONE &&
      webcompat_content_settings < ContentSettingsType::QORAI_WEBCOMPAT_ALL) {
    webcompat_features_invoked_.insert(webcompat_content_settings);
  }

  for (Observer& obs : observer_list_) {
    obs.OnResourcesChanged();
  }
}

void QorAIShieldsTabHelper::SetWebcompatEnabled(
    ContentSettingsType webcompat_settings_type,
    bool enabled) {
  qorai_shields::SetWebcompatEnabled(
      &*host_content_settings_map_, webcompat_settings_type, enabled,
      GetCurrentSiteURL(), g_browser_process->local_state());
  ReloadWebContents();
}

base::flat_map<ContentSettingsType, bool>
QorAIShieldsTabHelper::GetWebcompatSettings() {
  const GURL& current_site_url = GetCurrentSiteURL();
  base::flat_map<ContentSettingsType, bool> result;
  for (auto webcompat_settings_type = ContentSettingsType::QORAI_WEBCOMPAT_NONE;
       webcompat_settings_type != ContentSettingsType::QORAI_WEBCOMPAT_ALL;
       webcompat_settings_type = static_cast<ContentSettingsType>(
           static_cast<int32_t>(webcompat_settings_type) + 1)) {
    const bool enabled = qorai_shields::IsWebcompatEnabled(
        &*host_content_settings_map_, webcompat_settings_type,
        current_site_url);
    result[webcompat_settings_type] = enabled;
  }
  return result;
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(QorAIShieldsTabHelper);

}  // namespace qorai_shields
