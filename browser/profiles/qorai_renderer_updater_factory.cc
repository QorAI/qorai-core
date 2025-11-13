/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/profiles/qorai_renderer_updater_factory.h"

#include "base/no_destructor.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/profiles/qorai_renderer_updater.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"

QoraiRendererUpdaterFactory::QoraiRendererUpdaterFactory()
    : ProfileKeyedServiceFactory(
          "QoraiRendererUpdater",
          ProfileSelections::Builder()
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              .Build()) {
  DependsOn(qorai_wallet::QoraiWalletServiceFactory::GetInstance());
}

QoraiRendererUpdaterFactory::~QoraiRendererUpdaterFactory() = default;

// static
QoraiRendererUpdaterFactory* QoraiRendererUpdaterFactory::GetInstance() {
  static base::NoDestructor<QoraiRendererUpdaterFactory> instance;
  return instance.get();
}

// static
QoraiRendererUpdater* QoraiRendererUpdaterFactory::GetForProfile(
    Profile* profile) {
  return static_cast<QoraiRendererUpdater*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

std::unique_ptr<KeyedService>
QoraiRendererUpdaterFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(context);

  auto* keyring_service =
      qorai_wallet_service ? qorai_wallet_service->keyring_service() : 0;
  return std::make_unique<QoraiRendererUpdater>(
      static_cast<Profile*>(context), keyring_service,
      g_browser_process->local_state());
}

bool QoraiRendererUpdaterFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}
