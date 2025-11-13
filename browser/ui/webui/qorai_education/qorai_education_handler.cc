// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// based on //chrome/browser/ui/webui/whats_new/whats_new_handler.cc

#include "qorai/browser/ui/webui/qorai_education/qorai_education_handler.h"

#include <utility>

QoraiEducationHandler::QoraiEducationHandler(
    mojo::PendingReceiver<qorai_education::mojom::PageHandler> receiver,
    mojo::PendingRemote<qorai_education::mojom::Page> page,
    qorai_education::EducationPageType page_type)
    : receiver_(this, std::move(receiver)),
      page_(std::move(page)),
      page_type_(page_type) {}

QoraiEducationHandler::~QoraiEducationHandler() = default;

void QoraiEducationHandler::GetServerUrl(GetServerUrlCallback callback) {
  std::move(callback).Run(
      qorai_education::GetEducationPageServerURL(page_type_));
}
