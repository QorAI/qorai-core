/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"

#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"

namespace qorai_wallet {

bool IsAllowedForContext(content::BrowserContext* context) {
  if (!context || context->IsTor()) {
    return false;
  }

  auto* prefs = user_prefs::UserPrefs::Get(context);
  if (!IsAllowed(prefs)) {
    return false;
  }

  if (Profile::FromBrowserContext(context)->IsRegularProfile()) {
    return true;
  }

  if (Profile::FromBrowserContext(context)->IsIncognitoProfile()) {
    return prefs->GetBoolean(kQorAIWalletPrivateWindowsEnabled);
  }

  return false;
}

}  // namespace qorai_wallet
