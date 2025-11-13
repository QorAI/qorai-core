/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/api/qorai_wallet/token_registry_utils.h"

#include <optional>

#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/strings/sys_string_conversions.h"
#include "base/version.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/qorai_wallet/browser/wallet_data_files_installer.h"
#include "ios/chrome/browser/shared/model/paths/paths.h"

@implementation QoraiWalletTokenRegistryUtils

+ (nullable NSURL*)tokenLogoBaseURL {
  base::FilePath path;
  std::optional<base::Version> version =
      qorai_wallet::GetLastInstalledWalletVersion();
  if (base::PathService::Get(ios::DIR_USER_DATA, &path) && version) {
    path = path.AppendASCII(qorai_wallet::kWalletBaseDirectory);
    path = path.AppendASCII(version->GetString());
    path = path.AppendASCII("images");
    return [NSURL fileURLWithPath:base::SysUTF8ToNSString(path.value())];
  }
  return nil;
}

@end
