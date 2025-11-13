/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_OS_CRYPT_SYNC_KEY_STORAGE_KWALLET_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_OS_CRYPT_SYNC_KEY_STORAGE_KWALLET_H_

#define InitFolder             \
  InitFolder();                \
  const char* GetFolderName(); \
  const char* GetKeyName

#include <components/os_crypt/sync/key_storage_kwallet.h>  // IWYU pragma: export
#undef InitFolder

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_OS_CRYPT_SYNC_KEY_STORAGE_KWALLET_H_
