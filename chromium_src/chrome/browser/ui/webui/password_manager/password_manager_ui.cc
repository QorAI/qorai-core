/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "qorai/grit/qorai_unscaled_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/webui/webui_util.h"

namespace {

// Called from the original password_manager_ui.cc's
// CreateAndAddPasswordsUIHTMLSource via a patch.
void QoraiAddPasswordManagerResources(content::WebUIDataSource* source,
                                      Profile* profile) {
  NavigationBarDataProvider::Initialize(source, profile);
}

}  // namespace

#define SetupWebUIDataSource(...)                             \
  SetupWebUIDataSource(__VA_ARGS__);                          \
  source->AddResourcePath("images/password_manager_logo.svg", \
                          IDR_QORAI_PASSWORD_MANAGER_LOGO);   \
  QoraiAddPasswordManagerResources(source, profile);

#undef IDS_PASSWORD_MANAGER_UI_EMPTY_STATE_SYNCING_USERS
#define IDS_PASSWORD_MANAGER_UI_EMPTY_STATE_SYNCING_USERS \
  IDS_QORAI_PASSWORD_MANAGER_UI_EMPTY_STATE_SIGNEDOUT_USERS

#undef IDS_PASSWORD_MANAGER_UI_EMPTY_STATE_SIGNEDOUT_USERS
#define IDS_PASSWORD_MANAGER_UI_EMPTY_STATE_SIGNEDOUT_USERS \
  IDS_QORAI_PASSWORD_MANAGER_UI_EMPTY_STATE_SIGNEDOUT_USERS

#undef IDS_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SYNCING_USERS
#define IDS_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SYNCING_USERS \
  IDS_QORAI_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SIGNEDOUT_USERS

#undef IDS_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SIGNEDOUT_USERS
#define IDS_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SIGNEDOUT_USERS \
  IDS_QORAI_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SIGNEDOUT_USERS

#include <chrome/browser/ui/webui/password_manager/password_manager_ui.cc>
#undef IDS_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SIGNEDOUT_USERS
#undef IDS_PASSWORD_MANAGER_UI_IMPORT_DESCRIPTION_SYNCING_USERS
#undef IDS_PASSWORD_MANAGER_UI_EMPTY_STATE_SIGNEDOUT_USERS
#undef IDS_PASSWORD_MANAGER_UI_EMPTY_STATE_SYNCING_USERS
#undef SetupWebUIDataSource
