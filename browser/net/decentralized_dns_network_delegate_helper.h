/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_DECENTRALIZED_DNS_NETWORK_DELEGATE_HELPER_H_
#define QORAI_BROWSER_NET_DECENTRALIZED_DNS_NETWORK_DELEGATE_HELPER_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "qorai/browser/net/url_context.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "net/base/completion_once_callback.h"

namespace decentralized_dns {

// Issue eth_call requests via Ethereum provider such as Infura to query
// decentralized DNS records, and redirect URL requests based on them.
int OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
    const qorai::ResponseCallback& next_callback,
    std::shared_ptr<qorai::QoraiRequestInfo> ctx);

void OnBeforeURLRequest_UnstoppableDomainsRedirectWork(
    const qorai::ResponseCallback& next_callback,
    std::shared_ptr<qorai::QoraiRequestInfo> ctx,
    const std::optional<GURL>& url,
    qorai_wallet::mojom::ProviderError error,
    const std::string& error_message);

void OnBeforeURLRequest_EnsRedirectWork(
    const qorai::ResponseCallback& next_callback,
    std::shared_ptr<qorai::QoraiRequestInfo> ctx,
    const std::vector<uint8_t>& content_hash,
    bool require_offchain_consent,
    qorai_wallet::mojom::ProviderError error,
    const std::string& error_message);

void OnBeforeURLRequest_SnsRedirectWork(
    const qorai::ResponseCallback& next_callback,
    std::shared_ptr<qorai::QoraiRequestInfo> ctx,
    const std::optional<GURL>& url,
    qorai_wallet::mojom::SolanaProviderError error,
    const std::string& error_message);

}  // namespace decentralized_dns

#endif  // QORAI_BROWSER_NET_DECENTRALIZED_DNS_NETWORK_DELEGATE_HELPER_H_
