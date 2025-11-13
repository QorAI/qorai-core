// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_NEWS_INTERNALS_QORAI_NEWS_INTERNALS_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_NEWS_INTERNALS_QORAI_NEWS_INTERNALS_UI_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom-forward.h"
#include "content/public/browser/web_ui_controller.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace qorai_news {
class QoraiNewsController;
}

class QoraiNewsInternalsUI : public content::WebUIController {
 public:
  explicit QoraiNewsInternalsUI(content::WebUI* web_ui,
                                const std::string& host,
                                qorai_news::QoraiNewsController* controller);
  QoraiNewsInternalsUI(const QoraiNewsInternalsUI&) = delete;
  QoraiNewsInternalsUI& operator=(const QoraiNewsInternalsUI&) = delete;
  ~QoraiNewsInternalsUI() override;

  void BindInterface(
      mojo::PendingReceiver<qorai_news::mojom::QoraiNewsController> receiver);
  void BindInterface(
      mojo::PendingReceiver<qorai_news::mojom::QoraiNewsInternals> receiver);

 private:
  raw_ptr<qorai_news::QoraiNewsController> controller_ = nullptr;
  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_NEWS_INTERNALS_QORAI_NEWS_INTERNALS_UI_H_
