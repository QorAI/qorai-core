// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ui/webui/qorai_color_change_listener/qorai_color_change_handler.h"

#include <memory>
#include <utility>

#include "mojo/public/cpp/bindings/self_owned_receiver.h"

namespace ui {

void QoraiColorChangeHandler::BindInterface(
    content::WebContents* web_contents,
    mojo::PendingReceiver<color_change_listener::mojom::PageHandler>
        pending_receiver) {
  mojo::MakeSelfOwnedReceiver(
      std::make_unique<QoraiColorChangeHandler>(web_contents),
      std::move(pending_receiver));
}

QoraiColorChangeHandler::QoraiColorChangeHandler(
    content::WebContents* web_contents)
    : WebContentsObserver(web_contents) {}

QoraiColorChangeHandler::~QoraiColorChangeHandler() = default;

void QoraiColorChangeHandler::SetPage(
    mojo::PendingRemote<color_change_listener::mojom::Page> pending_page) {
  page_.Bind(std::move(pending_page));
}

void QoraiColorChangeHandler::OnColorProviderChanged() {
  if (page_) {
    page_->OnColorProviderChanged();
  }
}

}  // namespace ui
