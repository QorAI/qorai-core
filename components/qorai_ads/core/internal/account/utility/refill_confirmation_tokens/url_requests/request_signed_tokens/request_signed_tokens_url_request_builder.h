/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_info.h"
#include "qorai/components/qorai_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

class GURL;

namespace qorai_ads {

class RequestSignedTokensUrlRequestBuilder final
    : public UrlRequestBuilderInterface {
 public:
  RequestSignedTokensUrlRequestBuilder(WalletInfo wallet,
                                       cbr::BlindedTokenList tokens);

  RequestSignedTokensUrlRequestBuilder(
      const RequestSignedTokensUrlRequestBuilder&) = delete;
  RequestSignedTokensUrlRequestBuilder& operator=(
      const RequestSignedTokensUrlRequestBuilder&) = delete;

  ~RequestSignedTokensUrlRequestBuilder() override;

  mojom::UrlRequestInfoPtr Build() override;

 private:
  GURL BuildUrl() const;

  std::vector<std::string> BuildHeaders(const std::string& body) const;
  std::string BuildSignatureHeaderValue(const std::string& body) const;

  std::string BuildBody() const;

  const WalletInfo wallet_;
  const cbr::BlindedTokenList blinded_tokens_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_
