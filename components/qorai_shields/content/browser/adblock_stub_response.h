// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_ADBLOCK_STUB_RESPONSE_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_ADBLOCK_STUB_RESPONSE_H_

#include <optional>
#include <string>

#include "services/network/public/mojom/url_response_head.mojom-forward.h"

namespace network {
struct ResourceRequest;
}  // namespace network

namespace qorai_shields {

// Intercepts certain requests and blocks them by silently returning 200 OK
// and not allowing them to hit the network.
void MakeStubResponse(const std::optional<std::string>& data_url,
                      const network::ResourceRequest& request,
                      network::mojom::URLResponseHeadPtr* response,
                      std::string* data);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_ADBLOCK_STUB_RESPONSE_H_
