// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_WEB_WEBUI_QORAI_WEB_UI_IOS_DATA_SOURCE_H_
#define QORAI_IOS_WEB_WEBUI_QORAI_WEB_UI_IOS_DATA_SOURCE_H_

#include <map>
#include <set>
#include <string>

#include "base/containers/flat_map.h"
#include "ios/web/webui/web_ui_ios_data_source_impl.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"

namespace web {
class BrowserState;
}

class QoraiWebUIIOSDataSource : public web::WebUIIOSDataSourceImpl {
 public:
  static QoraiWebUIIOSDataSource* Create(const std::string& source_name);

  static QoraiWebUIIOSDataSource* CreateAndAdd(web::BrowserState* browser_state,
                                               const std::string& source_name);

  QoraiWebUIIOSDataSource(const QoraiWebUIIOSDataSource&) = delete;
  QoraiWebUIIOSDataSource& operator=(const QoraiWebUIIOSDataSource&) = delete;

  // Qorai CSP's & Security implementation:
  virtual void SetSupportedScheme(std::string_view scheme);

  virtual void OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName directive,
      const std::string& value);

  virtual void AddFrameAncestor(const GURL& frame_ancestor);
  virtual void DisableTrustedTypesCSP();

 protected:
  ~QoraiWebUIIOSDataSource() override;

  virtual std::string GetMimeType(const std::string& path) const;

 private:
  class QoraiInternalDataSource;
  friend class QoraiInternalDataSource;

  explicit QoraiWebUIIOSDataSource(const std::string& source_name);

  // Qorai CSP's & Security variables:
  base::flat_map<network::mojom::CSPDirectiveName, std::string> csp_overrides_;
  std::set<GURL> frame_ancestors_;

  // Supported scheme if not one of the default supported schemes.
  std::optional<std::string> supported_scheme_;
};

#endif  // QORAI_IOS_WEB_WEBUI_QORAI_WEB_UI_IOS_DATA_SOURCE_H_
