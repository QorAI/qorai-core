// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_news/browser/network.h"

#include <string>

#include "base/time/time.h"

namespace qorai_news {

base::TimeDelta GetDefaultRequestTimeout() {
  return base::Seconds(30.0);
}
net::NetworkTrafficAnnotationTag GetNetworkTrafficAnnotationTag() {
  return net::DefineNetworkTrafficAnnotation("qorai_news_controller", R"(
      semantics {
        sender: "Qorai News Controller"
        description:
          "This controller is used to fetch qorai news feeds and publisher lists."
        trigger:
          "Triggered by uses of the Qorai News feature."
        data:
          "Article JSON"
        destination: WEBSITE
      }
      policy {
        cookies_allowed: NO
        setting:
          "You can enable or disable this feature on the New Tab Page customization."
        policy_exception_justification:
          "Not implemented."
      }
    )");
}

}  // namespace qorai_news
