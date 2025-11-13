/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_EPHEMERAL_STORAGE_QORAI_EPHEMERAL_STORAGE_SERVICE_DELEGATE_H_
#define QORAI_BROWSER_EPHEMERAL_STORAGE_QORAI_EPHEMERAL_STORAGE_SERVICE_DELEGATE_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "qorai/components/ephemeral_storage/ephemeral_storage_service_delegate.h"
#include "components/content_settings/core/browser/cookie_settings.h"

#if !BUILDFLAG(IS_ANDROID)
#include "chrome/browser/ui/browser_list_observer.h"
#endif

namespace content {
class BrowserContext;
}

class HostContentSettingsMap;

namespace ephemeral_storage {

class QoraiEphemeralStorageServiceDelegate :
#if !BUILDFLAG(IS_ANDROID)
    public BrowserListObserver,
#endif  // !BUILDFLAG(IS_ANDROID)
    public EphemeralStorageServiceDelegate {
 public:
  QoraiEphemeralStorageServiceDelegate(
      content::BrowserContext* context,
      HostContentSettingsMap* host_content_settings_map,
      scoped_refptr<content_settings::CookieSettings> cookie_settings);
  ~QoraiEphemeralStorageServiceDelegate() override;

#if !BUILDFLAG(IS_ANDROID)
  // BrowserListObserver:
  void OnBrowserAdded(Browser* browser) override;
#endif  // !BUILDFLAG(IS_ANDROID)

  // EphemeralStorageServiceDelegate:
  void CleanupTLDEphemeralArea(const TLDEphemeralAreaKey& key) override;
  void CleanupFirstPartyStorageArea(const TLDEphemeralAreaKey& key) override;
  void RegisterFirstWindowOpenedCallback(base::OnceClosure callback) override;

 private:
  raw_ptr<content::BrowserContext> context_ = nullptr;
  raw_ptr<HostContentSettingsMap> host_content_settings_map_ = nullptr;
  scoped_refptr<content_settings::CookieSettings> cookie_settings_;
#if !BUILDFLAG(IS_ANDROID)
  base::OnceClosure first_window_opened_callback_;
#endif  // !BUILDFLAG(IS_ANDROID)
};

}  // namespace ephemeral_storage

#endif  // QORAI_BROWSER_EPHEMERAL_STORAGE_QORAI_EPHEMERAL_STORAGE_SERVICE_DELEGATE_H_
