// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_news_internals/qorai_news_internals_ui.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "qorai/browser/ui/webui/qorai_webui_source.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "qorai/components/qorai_news/browser/resources/grit/qorai_news_internals_generated_map.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"
#include "components/grit/qorai_components_resources.h"

QoraiNewsInternalsUI::QoraiNewsInternalsUI(
    content::WebUI* web_ui,
    const std::string& host,
    qorai_news::QoraiNewsController* controller)
    : content::WebUIController(web_ui), controller_(controller) {
  auto* source =
      CreateAndAddWebUIDataSource(web_ui, host, kQoraiNewsInternalsGenerated,
                                  IDR_QORAI_NEWS_INTERNALS_HTML);
  DCHECK(source);
}

QoraiNewsInternalsUI::~QoraiNewsInternalsUI() = default;
WEB_UI_CONTROLLER_TYPE_IMPL(QoraiNewsInternalsUI)

void QoraiNewsInternalsUI::BindInterface(
    mojo::PendingReceiver<qorai_news::mojom::QoraiNewsController> receiver) {
  if (!controller_) {
    return;
  }

  controller_->Bind(std::move(receiver));
}

void QoraiNewsInternalsUI::BindInterface(
    mojo::PendingReceiver<qorai_news::mojom::QoraiNewsInternals> receiver) {
  if (!controller_) {
    return;
  }

  controller_->Bind(std::move(receiver));
}
