// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/ios/browser/qorai_shields_settings_bridge_impl.h"

#include <Foundation/Foundation.h>

#include <memory>

#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/prefs/pref_service.h"
#include "net/base/apple/url_conversions.h"
#include "url/gurl.h"

@implementation QoraiShieldsSettingsBridgeImpl {
  raw_ptr<qorai_shields::QoraiShieldsSettingsService> _qoraiShieldsSettings;
}

- (instancetype)initWithQoraiShieldsSettings:
    (raw_ptr<qorai_shields::QoraiShieldsSettingsService>)qoraiShieldsSettings {
  if ((self = [super init])) {
    _qoraiShieldsSettings = qoraiShieldsSettings;
  }
  return self;
}

- (bool)qoraiShieldsEnabledFor:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return _qoraiShieldsSettings->GetQoraiShieldsEnabled(gurl);
}

- (void)setQoraiShieldsEnabled:(bool)isEnabled forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _qoraiShieldsSettings->SetQoraiShieldsEnabled(isEnabled, gurl);
}

- (QoraiShieldsAdBlockMode)defaultAdBlockMode {
  return static_cast<QoraiShieldsAdBlockMode>(
      _qoraiShieldsSettings->GetDefaultAdBlockMode());
}

- (QoraiShieldsAdBlockMode)adBlockModeForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return static_cast<QoraiShieldsAdBlockMode>(
      _qoraiShieldsSettings->GetAdBlockMode(gurl));
}

- (void)setDefaultAdBlockMode:(QoraiShieldsAdBlockMode)adBlockMode {
  _qoraiShieldsSettings->SetDefaultAdBlockMode(
      static_cast<qorai_shields::mojom::AdBlockMode>(adBlockMode));
}

- (void)setAdBlockMode:(QoraiShieldsAdBlockMode)adBlockMode forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _qoraiShieldsSettings->SetAdBlockMode(
      static_cast<qorai_shields::mojom::AdBlockMode>(adBlockMode), gurl);
}

- (bool)isBlockScriptsEnabledByDefault {
  return _qoraiShieldsSettings->IsNoScriptEnabledByDefault();
}

- (bool)blockScriptsEnabledForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return _qoraiShieldsSettings->IsNoScriptEnabled(gurl);
}

- (void)setBlockScriptsEnabledByDefault:(bool)isEnabled {
  _qoraiShieldsSettings->SetNoScriptEnabledByDefault(isEnabled);
}

- (void)setBlockScriptsEnabled:(bool)isEnabled forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _qoraiShieldsSettings->SetNoScriptEnabled(isEnabled, gurl);
}

- (QoraiShieldsFingerprintMode)defaultFingerprintMode {
  return static_cast<QoraiShieldsFingerprintMode>(
      _qoraiShieldsSettings->GetDefaultFingerprintMode());
}

- (QoraiShieldsFingerprintMode)fingerprintModeForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return static_cast<QoraiShieldsFingerprintMode>(
      _qoraiShieldsSettings->GetFingerprintMode(gurl));
}

- (void)setDefaultFingerprintMode:(QoraiShieldsFingerprintMode)fingerprintMode {
  _qoraiShieldsSettings->SetDefaultFingerprintMode(
      static_cast<qorai_shields::mojom::FingerprintMode>(fingerprintMode));
}

- (void)setFingerprintMode:(QoraiShieldsFingerprintMode)fingerprintMode
                    forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _qoraiShieldsSettings->SetFingerprintMode(
      static_cast<qorai_shields::mojom::FingerprintMode>(fingerprintMode),
      gurl);
}

- (QoraiShieldsAutoShredMode)defaultAutoShredMode {
  return static_cast<QoraiShieldsAutoShredMode>(
      _qoraiShieldsSettings->GetDefaultAutoShredMode());
}

- (QoraiShieldsAutoShredMode)autoShredModeForURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  return static_cast<QoraiShieldsAutoShredMode>(
      _qoraiShieldsSettings->GetAutoShredMode(gurl));
}

- (void)setDefaultAutoShredMode:(QoraiShieldsAutoShredMode)autoShredMode {
  _qoraiShieldsSettings->SetDefaultAutoShredMode(
      static_cast<qorai_shields::mojom::AutoShredMode>(autoShredMode));
}

- (void)setAutoShredMode:(QoraiShieldsAutoShredMode)autoShredMode
                  forURL:(NSURL*)url {
  GURL gurl = net::GURLWithNSURL(url);
  _qoraiShieldsSettings->SetAutoShredMode(
      static_cast<qorai_shields::mojom::AutoShredMode>(autoShredMode), gurl);
}

@end
