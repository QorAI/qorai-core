/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/permissions/permission_manager_factory.h"

#include "qorai/browser/geolocation/qorai_geolocation_permission_context_delegate.h"
#include "qorai/browser/permissions/permission_lifetime_manager_factory.h"
#include "qorai/components/permissions/qorai_permission_manager.h"
#include "qorai/components/permissions/contexts/qorai_google_sign_in_permission_context.h"
#include "qorai/components/permissions/contexts/qorai_localhost_permission_context.h"
#include "qorai/components/permissions/contexts/qorai_open_ai_chat_permission_context.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "qorai/components/permissions/permission_lifetime_manager.h"
#include "components/permissions/features.h"

#define GeolocationPermissionContextDelegate \
  QoraiGeolocationPermissionContextDelegate

#define BuildServiceInstanceForBrowserContext \
  BuildServiceInstanceForBrowserContext_ChromiumImpl

#include <chrome/browser/permissions/permission_manager_factory.cc>

#undef GeolocationPermissionContextDelegate
#undef BuildServiceInstanceForBrowserContext

std::unique_ptr<KeyedService>
PermissionManagerFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  Profile* profile = Profile::FromBrowserContext(context);
  auto permission_contexts = CreatePermissionContexts(profile);

  permission_contexts[ContentSettingsType::QORAI_ETHEREUM] =
      std::make_unique<permissions::QoraiWalletPermissionContext>(
          profile, ContentSettingsType::QORAI_ETHEREUM);
  permission_contexts[ContentSettingsType::QORAI_SOLANA] =
      std::make_unique<permissions::QoraiWalletPermissionContext>(
          profile, ContentSettingsType::QORAI_SOLANA);
  permission_contexts[ContentSettingsType::QORAI_CARDANO] =
      std::make_unique<permissions::QoraiWalletPermissionContext>(
          profile, ContentSettingsType::QORAI_CARDANO);
  permission_contexts[ContentSettingsType::QORAI_GOOGLE_SIGN_IN] =
      std::make_unique<permissions::QoraiGoogleSignInPermissionContext>(
          profile);
  permission_contexts[ContentSettingsType::QORAI_LOCALHOST_ACCESS] =
      std::make_unique<permissions::QoraiLocalhostPermissionContext>(profile);
  permission_contexts[ContentSettingsType::QORAI_OPEN_AI_CHAT] =
      std::make_unique<permissions::QoraiOpenAIChatPermissionContext>(profile);

  if (base::FeatureList::IsEnabled(
          permissions::features::kPermissionLifetime)) {
    auto factory =
        base::BindRepeating(&PermissionLifetimeManagerFactory::GetForProfile);
    for (auto& permission_context : permission_contexts) {
      permission_context.second->SetPermissionLifetimeManagerFactory(factory);
    }
  }

  return std::make_unique<permissions::QoraiPermissionManager>(
      profile, std::move(permission_contexts));
}
