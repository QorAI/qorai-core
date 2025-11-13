/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/permissions/chrome_permissions_client.h"

#define MaybeCreateMessageUI MaybeCreateMessageUI_ChromiumImpl
#include <chrome/browser/permissions/chrome_permissions_client.cc>
#undef MaybeCreateMessageUI

#include <vector>

#include "build/build_config.h"
#include "components/permissions/permission_request.h"
#include "components/permissions/request_type.h"
#include "url/origin.h"

#if BUILDFLAG(IS_ANDROID)
#include "qorai/browser/permissions/qorai_wallet_permission_prompt_android.h"
#include "components/permissions/android/permission_prompt/permission_prompt_android.h"
#endif

bool ChromePermissionsClient::QoraiCanBypassEmbeddingOriginCheck(
    const GURL& requesting_origin,
    const GURL& embedding_origin,
    ContentSettingsType type) {
  // Note that requesting_origin has an address in it at this point.
  // But even if we get the original origin without the address, we can't
  // check it against the embedding origin for QORAI_ETHEREUM and QORAI_SOLANA
  // here because it can be allowed across origins via the iframe `allow`
  // attribute with the `ethereum` and `solana` feature policy.
  // Without this check we'd fail Chromium's origin check.
  // We instead handle this in qorai_wallet_render_frame_observer.cc by not
  // exposing the API which can request permission when the origin is 3p and
  // the feature policy is not allowed explicitly. We ensure that the correct
  // handling is covered via the browser tests:
  // SolanaProviderRendererTest.Iframe3P and
  // JSEthereumProviderBrowserTest.Iframe3P
  if (type == ContentSettingsType::QORAI_ETHEREUM ||
      type == ContentSettingsType::QORAI_SOLANA ||
      type == ContentSettingsType::QORAI_CARDANO) {
    return true;
  }

  return CanBypassEmbeddingOriginCheck(requesting_origin, embedding_origin);
}

#if BUILDFLAG(IS_ANDROID)
std::unique_ptr<ChromePermissionsClient::PermissionMessageDelegate>
ChromePermissionsClient::MaybeCreateMessageUI(
    content::WebContents* web_contents,
    ContentSettingsType type,
    base::WeakPtr<permissions::PermissionPromptAndroid> prompt) {
  const auto& requests = prompt->delegate_public()->Requests();
  if (requests.size() > 0) {
    qorai_wallet::mojom::CoinType coin_type =
        qorai_wallet::mojom::CoinType::ETH;
    permissions::RequestType request_type = requests[0]->request_type();
    if (request_type == permissions::RequestType::kQoraiEthereum ||
        request_type == permissions::RequestType::kQoraiSolana ||
        request_type == permissions::RequestType::kQoraiCardano) {
      if (request_type == permissions::RequestType::kQoraiSolana) {
        coin_type = qorai_wallet::mojom::CoinType::SOL;
      }
      if (request_type == permissions::RequestType::kQoraiCardano) {
        coin_type = qorai_wallet::mojom::CoinType::ADA;
      }
      auto delegate = std::make_unique<QoraiWalletPermissionPrompt::Delegate>(
          std::move(prompt));
      return std::make_unique<QoraiWalletPermissionPrompt>(
          web_contents, std::move(delegate), coin_type);
    }
  }

  return MaybeCreateMessageUI_ChromiumImpl(web_contents, type,
                                           std::move(prompt));
}
#endif
