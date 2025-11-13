/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_SHELL_INTEGRATION_H_
#define QORAI_BROWSER_QORAI_SHELL_INTEGRATION_H_

#include "base/functional/callback.h"
#include "base/functional/callback_helpers.h"
#include "chrome/browser/shell_integration.h"

class Profile;

namespace shell_integration {

void PinShortcut(
    Profile* profile = nullptr,
    base::OnceCallback<void(bool)> result_callback = base::DoNothing());
void IsShortcutPinned(
    base::OnceCallback<void(bool)> result_callback = base::DoNothing());

class QorAIDefaultBrowserWorker : public DefaultBrowserWorker {
 public:
  QorAIDefaultBrowserWorker();

  QorAIDefaultBrowserWorker(const QorAIDefaultBrowserWorker&) = delete;
  QorAIDefaultBrowserWorker& operator=(const QorAIDefaultBrowserWorker&) =
      delete;

 protected:
  ~QorAIDefaultBrowserWorker() override;

  void SetAsDefaultImpl(base::OnceClosure on_finished_callback) override;
};

}  // namespace shell_integration

#endif  // QORAI_BROWSER_QORAI_SHELL_INTEGRATION_H_
