/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NTP_BACKGROUND_QORAI_NTP_CUSTOM_BACKGROUND_SERVICE_FACTORY_H_
#define QORAI_BROWSER_NTP_BACKGROUND_QORAI_NTP_CUSTOM_BACKGROUND_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace ntp_background_images {
class QoraiNTPCustomBackgroundService;
}  // namespace ntp_background_images

class QoraiNTPCustomBackgroundServiceFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  static ntp_background_images::QoraiNTPCustomBackgroundService* GetForContext(
      content::BrowserContext* context);
  static QoraiNTPCustomBackgroundServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<QoraiNTPCustomBackgroundServiceFactory>;

  QoraiNTPCustomBackgroundServiceFactory();
  ~QoraiNTPCustomBackgroundServiceFactory() override;

  QoraiNTPCustomBackgroundServiceFactory(
      const QoraiNTPCustomBackgroundServiceFactory&) = delete;
  QoraiNTPCustomBackgroundServiceFactory& operator=(
      const QoraiNTPCustomBackgroundServiceFactory&) = delete;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

#endif  // QORAI_BROWSER_NTP_BACKGROUND_QORAI_NTP_CUSTOM_BACKGROUND_SERVICE_FACTORY_H_
