// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// based on //chrome/browser/ui/webui/whats_new/whats_new_handler.h

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_HANDLER_H_

#include "qorai/browser/ui/webui/qorai_education/qorai_education.mojom.h"
#include "qorai/components/qorai_education/education_urls.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "ui/webui/mojo_web_ui_controller.h"

// Page handler for qorai://getting-started
class QoraiEducationHandler : public qorai_education::mojom::PageHandler {
 public:
  QoraiEducationHandler(
      mojo::PendingReceiver<qorai_education::mojom::PageHandler> receiver,
      mojo::PendingRemote<qorai_education::mojom::Page> page,
      qorai_education::EducationPageType page_type);
  ~QoraiEducationHandler() override;
  QoraiEducationHandler(const QoraiEducationHandler&) = delete;
  QoraiEducationHandler& operator=(const QoraiEducationHandler&) = delete;

 private:
  // qorai_education::mojom::PageHandler
  void GetServerUrl(GetServerUrlCallback callback) override;

  // These are located at the end of the list of member variables to ensure the
  // WebUI page is disconnected before other members are destroyed.
  mojo::Receiver<qorai_education::mojom::PageHandler> receiver_;
  mojo::Remote<qorai_education::mojom::Page> page_;
  qorai_education::EducationPageType page_type_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_EDUCATION_QORAI_EDUCATION_HANDLER_H_
