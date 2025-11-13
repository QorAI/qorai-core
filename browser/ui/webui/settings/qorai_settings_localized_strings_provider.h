/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_LOCALIZED_STRINGS_PROVIDER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_LOCALIZED_STRINGS_PROVIDER_H_

class Profile;

namespace content {
class WebUIDataSource;
}

namespace settings {

void QoraiAddLocalizedStrings(content::WebUIDataSource*, Profile*);

}  // namespace settings

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_LOCALIZED_STRINGS_PROVIDER_H_
