/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_utils.h"
#include "qorai/components/qorai_shields/core/common/shields_settings.mojom-shared.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "components/user_prefs/user_prefs.h"

#include <chrome/browser/content_settings/content_settings_manager_delegate.cc>

namespace {

bool IsJsBlockingEnforced(content::BrowserContext* browser_context,
                          const GURL& url) {
  Profile* profile = Profile::FromBrowserContext(browser_context);
  auto* settings_service =
      QoraiShieldsSettingsServiceFactory::GetForProfile(profile);
  if (!settings_service) {
    return false;
  }

  return settings_service->IsJsBlockingEnforced(url);
}

qorai_shields::mojom::ShieldsSettingsPtr GetQoraiShieldsSettingsOnUI(
    const content::GlobalRenderFrameHostToken& frame_token) {
  content::RenderFrameHost* rfh =
      content::RenderFrameHost::FromFrameToken(frame_token);
  if (!rfh) {
    return qorai_shields::mojom::ShieldsSettings::New();
  }
  content::RenderFrameHost* top_frame_rfh = rfh->GetOutermostMainFrame();
  if (!top_frame_rfh) {
    return qorai_shields::mojom::ShieldsSettings::New();
  }

  const GURL& top_frame_url = top_frame_rfh->GetLastCommittedURL();

  content::BrowserContext* browser_context = rfh->GetBrowserContext();
  const qorai_shields::mojom::FarblingLevel farbling_level =
      qorai_shields::GetFarblingLevel(
          HostContentSettingsMapFactory::GetForProfile(browser_context),
          top_frame_url);
  const base::Token farbling_token =
      farbling_level != qorai_shields::mojom::FarblingLevel::OFF
          ? qorai_shields::GetFarblingToken(
                HostContentSettingsMapFactory::GetForProfile(browser_context),
                top_frame_url)
          : base::Token();
  PrefService* pref_service = user_prefs::UserPrefs::Get(browser_context);

  return qorai_shields::mojom::ShieldsSettings::New(
      farbling_level, farbling_token, std::vector<std::string>(),
      qorai_shields::IsReduceLanguageEnabledForProfile(pref_service),
      IsJsBlockingEnforced(browser_context, top_frame_url));
}

}  // namespace

void ContentSettingsManagerDelegate::GetQoraiShieldsSettings(
    const content::GlobalRenderFrameHostToken& frame_token,
    content_settings::mojom::ContentSettingsManager::
        GetQoraiShieldsSettingsCallback callback) {
  content::GetUIThreadTaskRunner({})->PostTaskAndReplyWithResult(
      FROM_HERE, base::BindOnce(&GetQoraiShieldsSettingsOnUI, frame_token),
      std::move(callback));
}
