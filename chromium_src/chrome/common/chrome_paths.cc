/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#define RegisterPathProvider RegisterPathProvider_ChromiumImpl
#include <chrome/common/chrome_paths.cc>
#undef RegisterPathProvider

#include "qorai/components/constants/qorai_paths.h"

namespace qorai {

bool QoraiPathProvider(int key, base::FilePath* result) {
  base::FilePath cur;

  switch (key) {
    case DIR_TEST_DATA:
      if (!base::PathService::Get(base::DIR_SRC_TEST_DATA_ROOT, &cur)) {
        return false;
      }
      cur = cur.Append(FILE_PATH_LITERAL("qorai"));
      cur = cur.Append(FILE_PATH_LITERAL("test"));
      cur = cur.Append(FILE_PATH_LITERAL("data"));
      if (!base::PathExists(cur)) {  // We don't want to create this.
        return false;
      }
      break;

    default:
      return false;
  }

  *result = cur;
  return true;
}

void RegisterQoraiPathProvider() {
  base::PathService::RegisterProvider(QoraiPathProvider, PATH_START, PATH_END);
}

}  // namespace qorai

namespace chrome {

void RegisterPathProvider() {
  RegisterPathProvider_ChromiumImpl();
  qorai::RegisterQoraiPathProvider();
}

}  // namespace chrome
