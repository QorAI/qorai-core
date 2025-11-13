// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMMON_EXTENSIONS_QORAI_EXTENSIONS_CLIENT_H_
#define QORAI_COMMON_EXTENSIONS_QORAI_EXTENSIONS_CLIENT_H_

#include <string>

#include "chrome/common/extensions/chrome_extensions_client.h"

namespace extensions {

class QoraiExtensionsClient : public ChromeExtensionsClient {
 public:
  QoraiExtensionsClient();
  QoraiExtensionsClient(const QoraiExtensionsClient&) = delete;
  QoraiExtensionsClient& operator=(const QoraiExtensionsClient&) = delete;

  void InitializeWebStoreUrls(base::CommandLine* command_line) override;
  bool IsScriptableURL(const GURL& url, std::string* error) const override;
  const GURL& GetWebstoreUpdateURL() const override;

 private:
  GURL webstore_update_url_;
};

}  // namespace extensions

#endif  // QORAI_COMMON_EXTENSIONS_QORAI_EXTENSIONS_CLIENT_H_
