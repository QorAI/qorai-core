/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_ADS_ADS_CLIENT_BRIDGE_H_
#define QORAI_IOS_BROWSER_API_ADS_ADS_CLIENT_BRIDGE_H_

#import <Foundation/Foundation.h>

#include <optional>
#include <string>
#include <vector>

#include "base/values.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-shared.h"
#import "qorai/components/qorai_ads/core/public/ads_client/ads_client.h"

@protocol AdsClientBridge
@required

- (bool)isBrowserActive;
- (bool)isBrowserInFullScreenMode;
- (bool)canShowNotificationAdsWhileBrowserIsBackgrounded;
- (void)addObserver:(qorai_ads::AdsClientNotifierObserver*)observer;
- (void)removeObserver:(qorai_ads::AdsClientNotifierObserver*)observer;
- (void)notifyPendingObservers;
- (bool)isNetworkConnectionAvailable;
- (bool)canShowNotificationAds;
- (void)loadResourceComponent:(const std::string&)id
                      version:(int)version
                     callback:(qorai_ads::LoadFileCallback)callback;
- (void)showScheduledCaptcha:(const std::string&)payment_id
                   captchaId:(const std::string&)captcha_id;
- (void)getSiteHistory:(int)max_count
               forDays:(int)days_ago
              callback:(qorai_ads::GetSiteHistoryCallback)callback;
- (void)load:(const std::string&)name
    callback:(qorai_ads::LoadCallback)callback;
- (void)log:(const char*)file
            line:(int)line
    verboseLevel:(int)verbose_level
         message:(const std::string&)message;
- (void)save:(const std::string&)name
       value:(const std::string&)value
    callback:(qorai_ads::SaveCallback)callback;
- (void)showNotificationAd:(const qorai_ads::NotificationAdInfo&)info;
- (void)closeNotificationAd:(const std::string&)placement_id;
- (void)UrlRequest:(qorai_ads::mojom::UrlRequestInfoPtr)url_request
          callback:(qorai_ads::UrlRequestCallback)callback;
- (void)setProfilePref:(const std::string&)path value:(base::Value)value;
- (bool)findProfilePref:(const std::string&)path;
- (std::optional<base::Value>)getProfilePref:(const std::string&)path;
- (void)clearProfilePref:(const std::string&)path;
- (bool)hasProfilePrefPath:(const std::string&)path;
- (void)setLocalStatePref:(const std::string&)path value:(base::Value)value;
- (bool)findLocalStatePref:(const std::string&)path;
- (std::optional<base::Value>)getLocalStatePref:(const std::string&)path;
- (void)clearLocalStatePref:(const std::string&)path;
- (bool)hasLocalStatePrefPath:(const std::string&)path;
- (base::Value::Dict)getVirtualPrefs;

@end

#endif  // QORAI_IOS_BROWSER_API_ADS_ADS_CLIENT_BRIDGE_H_
