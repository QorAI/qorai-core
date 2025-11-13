/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORA_ACTION_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORA_ACTION_H_

#include <string>

#include "components/omnibox/browser/actions/omnibox_action.h"

class QoraAction : public OmniboxAction {
 public:
  explicit QoraAction(const std::u16string& query);

  // OmniboxAction:
  void Execute(ExecutionContext& context) const override;

 protected:
  ~QoraAction() override;

 private:
  const std::u16string query_;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORA_ACTION_H_
