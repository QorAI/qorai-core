/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SITE_SETTINGS_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SITE_SETTINGS_HANDLER_H_

#include <string>
#include <vector>

#include "chrome/browser/ui/webui/settings/site_settings_handler.h"

namespace settings {

class QoraiSiteSettingsHandler : public SiteSettingsHandler {
 public:
  explicit QoraiSiteSettingsHandler(Profile* profile);

  QoraiSiteSettingsHandler(const QoraiSiteSettingsHandler&) = delete;
  QoraiSiteSettingsHandler& operator=(const QoraiSiteSettingsHandler&) = delete;

  ~QoraiSiteSettingsHandler() override;

  // SettingsPageUIHandler:
  void RegisterMessages() override;

  // Returns whether the pattern is valid given the type.
  void HandleIsPatternValidForType(const base::Value::List& args);

  bool IsPatternValidForQoraiContentType(ContentSettingsType content_type,
                                         const std::string& pattern_string);

  void RemoveNonModelData(const std::vector<url::Origin>& origins) override;

 private:
  friend class TestQoraiSiteSettingsHandlerUnittest;
};

}  // namespace settings

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SITE_SETTINGS_HANDLER_H_
