/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/omnibox/browser/qora_action.h"

QoraAction::QoraAction(const std::u16string& query)
    : OmniboxAction({}, {}), query_(query) {}

void QoraAction::Execute(ExecutionContext& context) const {
  context.client_->OpenQora(query_);
}

QoraAction::~QoraAction() = default;
