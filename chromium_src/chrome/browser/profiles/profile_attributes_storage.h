/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_ATTRIBUTES_STORAGE_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_ATTRIBUTES_STORAGE_H_

#include "qorai/browser/profiles/qorai_profile_avatar_downloader.h"

#define ProfileAvatarDownloader QoraiProfileAvatarDownloader
#include <chrome/browser/profiles/profile_attributes_storage.h>  // IWYU pragma: export
#undef ProfileAvatarDownloader

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_PROFILES_PROFILE_ATTRIBUTES_STORAGE_H_
