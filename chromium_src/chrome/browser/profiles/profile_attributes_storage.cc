/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/profiles/profile_attributes_storage.h"

#include "qorai/browser/profiles/qorai_profile_avatar_downloader.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/grit/branded_strings.h"

// We want to use our own default profile name "Personal" instead of upstream's
// branded default profile name "Your Qorai".
#define IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME_SAVE \
  IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME
#undef IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME
#define IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME \
  IDS_PROFILE_MENU_QORAI_PLACEHOLDER_PROFILE_NAME

#define ProfileAvatarDownloader QoraiProfileAvatarDownloader
#include <chrome/browser/profiles/profile_attributes_storage.cc>
#undef ProfileAvatarDownloader
#undef IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME
#define IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME \
  IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME_SAVE
#undef IDS_PROFILE_MENU_PLACEHOLDER_PROFILE_NAME_SAVE
