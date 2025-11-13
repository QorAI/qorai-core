// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_UI_WEBUI_QORAI_COLOR_CHANGE_LISTENER_QORAI_COLOR_CHANGE_HANDLER_H_
#define QORAI_UI_WEBUI_QORAI_COLOR_CHANGE_LISTENER_QORAI_COLOR_CHANGE_HANDLER_H_

#include "content/public/browser/web_contents_observer.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "ui/webui/resources/cr_components/color_change_listener/color_change_listener.mojom.h"

namespace content {
class WebContents;
}  // namespace content

namespace ui {

// Handles ColorProvider related communication between C++ and WebUI in the
// renderer.
// Note: We can't use upstream's ColorChangeHandler because we want to expose
// this to all chrome://, chrome-untrusted:// and chrome-extension:// pages and
// its not possible to use upstream's ColorChangeHandler in a
// mojo::SelfOwnedReceiver. Essentially the difference is:
// 1. We want to expose this to all WebUI pages
// 2. Upstream only exposes this to specific pages, and each one needs to have
// its own Bind/unique_ptr
class QoraiColorChangeHandler
    : public content::WebContentsObserver,
      public color_change_listener::mojom::PageHandler {
 public:
  static void BindInterface(
      content::WebContents* web_contents,
      mojo::PendingReceiver<color_change_listener::mojom::PageHandler>
          pending_receiver);

  explicit QoraiColorChangeHandler(content::WebContents* web_contents);
  QoraiColorChangeHandler(const QoraiColorChangeHandler&) = delete;
  QoraiColorChangeHandler& operator=(const QoraiColorChangeHandler&) = delete;
  ~QoraiColorChangeHandler() override;

  // content::WebContentsObserver:
  void OnColorProviderChanged() override;

  // color_change_listener::mojom::PageHandler:
  void SetPage(mojo::PendingRemote<color_change_listener::mojom::Page>
                   pending_page) override;

 private:
  mojo::Remote<color_change_listener::mojom::Page> page_;
};

}  // namespace ui

#endif  // QORAI_UI_WEBUI_QORAI_COLOR_CHANGE_LISTENER_QORAI_COLOR_CHANGE_HANDLER_H_
