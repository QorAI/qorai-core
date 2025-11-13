/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "content/public/browser/browser_context.h"

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_adaptive_captcha {

class QorAIAdaptiveCaptchaService;

class QorAIAdaptiveCaptchaServiceFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  static QorAIAdaptiveCaptchaService* GetForProfile(Profile* profile);
  static QorAIAdaptiveCaptchaServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<QorAIAdaptiveCaptchaServiceFactory>;

  QorAIAdaptiveCaptchaServiceFactory();
  ~QorAIAdaptiveCaptchaServiceFactory() override;

  QorAIAdaptiveCaptchaServiceFactory(
      const QorAIAdaptiveCaptchaServiceFactory&) = delete;
  QorAIAdaptiveCaptchaServiceFactory& operator=(
      const QorAIAdaptiveCaptchaServiceFactory&) = delete;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

}  // namespace qorai_adaptive_captcha

#endif  // QORAI_BROWSER_QORAI_ADAPTIVE_CAPTCHA_QORAI_ADAPTIVE_CAPTCHA_SERVICE_FACTORY_H_
