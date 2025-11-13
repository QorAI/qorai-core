/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/psst/qorai_psst_permission_context_factory.h"

#include "qorai/components/psst/browser/core/qorai_psst_permission_context.h"
#include "qorai/components/psst/common/features.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"

namespace psst {

// static
QoraiPsstPermissionContextFactory*
QoraiPsstPermissionContextFactory::GetInstance() {
  static base::NoDestructor<QoraiPsstPermissionContextFactory> instance;
  return instance.get();
}

// static
QoraiPsstPermissionContext* QoraiPsstPermissionContextFactory::GetForProfile(
    Profile* profile) {
  CHECK(profile);
  CHECK(base::FeatureList::IsEnabled(psst::features::kEnablePsst));
  return static_cast<QoraiPsstPermissionContext*>(
      GetInstance()->GetServiceForContext(profile, true));
}

QoraiPsstPermissionContextFactory::QoraiPsstPermissionContextFactory()
    : ProfileKeyedServiceFactory("QoraiPsstPermissionService") {
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

QoraiPsstPermissionContextFactory::~QoraiPsstPermissionContextFactory() =
    default;

std::unique_ptr<KeyedService>
QoraiPsstPermissionContextFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  CHECK(context);
  auto* profile = Profile::FromBrowserContext(context);
  auto* host_content_settings_map =
      HostContentSettingsMapFactory::GetForProfile(profile);

  return std::make_unique<QoraiPsstPermissionContext>(
      host_content_settings_map);
}

}  // namespace psst
