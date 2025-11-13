/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#import "qorai/ios/browser/api/ads/ads_client_ios.h"

#include <optional>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#import "qorai/ios/browser/api/ads/ads_client_bridge.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

// Constructor & Destructor
AdsClientIOS::AdsClientIOS(id<AdsClientBridge> bridge) : bridge_(bridge) {}

AdsClientIOS::~AdsClientIOS() {
  bridge_ = nil;
}

void AdsClientIOS::AddObserver(qorai_ads::AdsClientNotifierObserver* observer) {
  [bridge_ addObserver:observer];
}

void AdsClientIOS::RemoveObserver(
    qorai_ads::AdsClientNotifierObserver* observer) {
  [bridge_ removeObserver:observer];
}

void AdsClientIOS::NotifyPendingObservers() {
  [bridge_ notifyPendingObservers];
}

bool AdsClientIOS::IsNetworkConnectionAvailable() const {
  return [bridge_ isNetworkConnectionAvailable];
}

bool AdsClientIOS::IsBrowserActive() const {
  return [bridge_ isBrowserActive];
}

bool AdsClientIOS::IsBrowserInFullScreenMode() const {
  return [bridge_ isBrowserInFullScreenMode];
}

bool AdsClientIOS::CanShowNotificationAdsWhileBrowserIsBackgrounded() const {
  return [bridge_ canShowNotificationAdsWhileBrowserIsBackgrounded];
}

void AdsClientIOS::ShowNotificationAd(const qorai_ads::NotificationAdInfo& ad) {
  [bridge_ showNotificationAd:ad];
}

bool AdsClientIOS::CanShowNotificationAds() const {
  return [bridge_ canShowNotificationAds];
}

void AdsClientIOS::CloseNotificationAd(const std::string& placement_id) {
  [bridge_ closeNotificationAd:placement_id];
}

void AdsClientIOS::UrlRequest(
    qorai_ads::mojom::UrlRequestInfoPtr mojom_url_request,
    qorai_ads::UrlRequestCallback callback) {
  [bridge_ UrlRequest:std::move(mojom_url_request)
             callback:std::move(callback)];
}

void AdsClientIOS::Save(const std::string& name,
                        const std::string& value,
                        qorai_ads::SaveCallback callback) {
  [bridge_ save:name value:value callback:std::move(callback)];
}

void AdsClientIOS::LoadResourceComponent(const std::string& id,
                                         int version,
                                         qorai_ads::LoadFileCallback callback) {
  [bridge_ loadResourceComponent:id
                         version:version
                        callback:std::move(callback)];
}

void AdsClientIOS::GetSiteHistory(int max_count,
                                  int days_ago,
                                  qorai_ads::GetSiteHistoryCallback callback) {
  [bridge_ getSiteHistory:max_count
                  forDays:days_ago
                 callback:std::move(callback)];
}

void AdsClientIOS::Load(const std::string& name,
                        qorai_ads::LoadCallback callback) {
  [bridge_ load:name callback:std::move(callback)];
}

void AdsClientIOS::ShowScheduledCaptcha(const std::string& payment_id,
                                        const std::string& captcha_id) {
  [bridge_ showScheduledCaptcha:payment_id captchaId:captcha_id];
}

void AdsClientIOS::Log(const char* file,
                       int line,
                       int verbose_level,
                       const std::string& message) {
  [bridge_ log:file line:line verboseLevel:verbose_level message:message];
}

void AdsClientIOS::SetProfilePref(const std::string& path, base::Value value) {
  [bridge_ setProfilePref:path value:std::move(value)];
}

std::optional<base::Value> AdsClientIOS::GetProfilePref(
    const std::string& path) {
  return [bridge_ getProfilePref:path];
}

bool AdsClientIOS::FindProfilePref(const std::string& path) const {
  return [bridge_ findProfilePref:path];
}

void AdsClientIOS::ClearProfilePref(const std::string& path) {
  [bridge_ clearProfilePref:path];
}

bool AdsClientIOS::HasProfilePrefPath(const std::string& path) const {
  return [bridge_ hasProfilePrefPath:path];
}

void AdsClientIOS::SetLocalStatePref(const std::string& path,
                                     base::Value value) {
  [bridge_ setLocalStatePref:path value:std::move(value)];
}

std::optional<base::Value> AdsClientIOS::GetLocalStatePref(
    const std::string& path) {
  return [bridge_ getLocalStatePref:path];
}

bool AdsClientIOS::FindLocalStatePref(const std::string& path) const {
  return [bridge_ findLocalStatePref:path];
}

void AdsClientIOS::ClearLocalStatePref(const std::string& path) {
  [bridge_ clearLocalStatePref:path];
}

bool AdsClientIOS::HasLocalStatePrefPath(const std::string& path) const {
  return [bridge_ hasLocalStatePrefPath:path];
}

base::Value::Dict AdsClientIOS::GetVirtualPrefs() const {
  return [bridge_ getVirtualPrefs];
}
