/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_PROFILES_QORAI_RENDERER_UPDATER_FACTORY_H_
#define QORAI_BROWSER_PROFILES_QORAI_RENDERER_UPDATER_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"

class Profile;
class QoraiRendererUpdater;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

// Singleton that creates/deletes QoraiRendererUpdater as new Profiles are
// created/shutdown.
class QoraiRendererUpdaterFactory : public ProfileKeyedServiceFactory {
 public:
  // Returns an instance of the QoraiRendererUpdaterFactory singleton.
  static QoraiRendererUpdaterFactory* GetInstance();

  // Returns the instance of RendererUpdater for the passed |profile|.
  static QoraiRendererUpdater* GetForProfile(Profile* profile);

  QoraiRendererUpdaterFactory(const QoraiRendererUpdaterFactory&) = delete;
  QoraiRendererUpdaterFactory& operator=(const QoraiRendererUpdaterFactory&) =
      delete;

 protected:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* profile) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;

 private:
  friend base::NoDestructor<QoraiRendererUpdaterFactory>;

  QoraiRendererUpdaterFactory();
  ~QoraiRendererUpdaterFactory() override;
};

#endif  // QORAI_BROWSER_PROFILES_QORAI_RENDERER_UPDATER_FACTORY_H_
