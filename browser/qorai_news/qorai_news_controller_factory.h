// Copyright (c) 2021 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_NEWS_QORAI_NEWS_CONTROLLER_FACTORY_H_
#define QORAI_BROWSER_QORAI_NEWS_QORAI_NEWS_CONTROLLER_FACTORY_H_

#include <memory>

#include "qorai/components/qorai_news/common/qorai_news.mojom.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/browser_context.h"
#include "mojo/public/cpp/bindings/pending_remote.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

class Profile;
namespace content {
class BrowserContext;
}

namespace qorai_news {

class QorAINewsController;

class QorAINewsControllerFactory : public BrowserContextKeyedServiceFactory {
 public:
  static QorAINewsController* GetForBrowserContext(
      content::BrowserContext* context);
  static mojo::PendingRemote<mojom::QorAINewsController> GetRemoteForProfile(
      Profile* profile);
  static QorAINewsControllerFactory* GetInstance();

  QorAINewsControllerFactory(const QorAINewsControllerFactory&) = delete;
  QorAINewsControllerFactory& operator=(const QorAINewsControllerFactory&) =
      delete;

  bool ServiceIsCreatedWithBrowserContext() const override;

 private:
  friend base::NoDestructor<QorAINewsControllerFactory>;

  QorAINewsControllerFactory();
  ~QorAINewsControllerFactory() override;

  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;
};

}  // namespace qorai_news

#endif  // QORAI_BROWSER_QORAI_NEWS_QORAI_NEWS_CONTROLLER_FACTORY_H_
