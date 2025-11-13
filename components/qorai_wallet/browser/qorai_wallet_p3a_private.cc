/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_p3a_private.h"

namespace qorai_wallet {

void QoraiWalletP3APrivate::ReportJSProvider(
    mojom::JSProviderType provider_type,
    mojom::CoinType coin_type,
    bool allow_provider_overwrite) {}

void QoraiWalletP3APrivate::ReportOnboardingAction(
    mojom::OnboardingAction onboarding_action) {}

void QoraiWalletP3APrivate::RecordActiveWalletCount(int count,
                                                    mojom::CoinType coin_type) {
}

void QoraiWalletP3APrivate::RecordNFTGalleryView(int nft_count) {}

}  // namespace qorai_wallet
