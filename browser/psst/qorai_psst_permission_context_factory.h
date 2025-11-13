/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_PSST_QORAI_PSST_PERMISSION_CONTEXT_FACTORY_H_
#define QORAI_BROWSER_PSST_QORAI_PSST_PERMISSION_CONTEXT_FACTORY_H_

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"

namespace psst {

class QoraiPsstPermissionContext;

class QoraiPsstPermissionContextFactory : public ProfileKeyedServiceFactory {
 public:
  static QoraiPsstPermissionContext* GetForProfile(Profile* profile);
  static QoraiPsstPermissionContextFactory* GetInstance();

  QoraiPsstPermissionContextFactory(const QoraiPsstPermissionContextFactory&) =
      delete;
  QoraiPsstPermissionContextFactory& operator=(
      const QoraiPsstPermissionContextFactory&) = delete;

 private:
  friend base::NoDestructor<QoraiPsstPermissionContextFactory>;

  QoraiPsstPermissionContextFactory();
  ~QoraiPsstPermissionContextFactory() override;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

}  // namespace psst

#endif  // QORAI_BROWSER_PSST_QORAI_PSST_PERMISSION_CONTEXT_FACTORY_H_
