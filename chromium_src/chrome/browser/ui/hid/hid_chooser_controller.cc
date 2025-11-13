/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "chrome/browser/chooser_controller/title_util.h"
#include "chrome/grit/generated_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

std::u16string QoraiCreateTitleLabel() {
  auto wallet_title = l10n_util::GetStringUTF16(IDS_QORAI_WALLET);
  return l10n_util::GetStringFUTF16(IDS_HID_CHOOSER_PROMPT, wallet_title);
}

}  // namespace

#define CreateChooserTitle                                                  \
  qorai_wallet::IsQoraiWalletOrigin(                                        \
      render_frame_host->GetOutermostMainFrame()->GetLastCommittedOrigin()) \
      ? QoraiCreateTitleLabel()                                             \
      : CreateChooserTitle
#include <chrome/browser/ui/hid/hid_chooser_controller.cc>
#undef CreateChooserTitle
