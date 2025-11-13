// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_WEB_WEBUI_QORAI_URL_DATA_SOURCE_IOS_H_
#define QORAI_IOS_WEB_WEBUI_QORAI_URL_DATA_SOURCE_IOS_H_

#include <string>

#include "ios/web/public/webui/url_data_source_ios.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"

class QoraiURLDataSourceIOS : public web::URLDataSourceIOS {
 public:
  QoraiURLDataSourceIOS();
  ~QoraiURLDataSourceIOS() override;

  virtual std::string GetContentSecurityPolicy(
      network::mojom::CSPDirectiveName directive) const;

 private:
  std::string GetContentSecurityPolicyObjectSrc() const override;
  std::string GetContentSecurityPolicyFrameSrc() const override;

  // Qorai CSP's & Security variables:
  base::flat_map<network::mojom::CSPDirectiveName, std::string> csp_overrides_;
};

#endif  // QORAI_IOS_WEB_WEBUI_QORAI_URL_DATA_SOURCE_IOS_H_
