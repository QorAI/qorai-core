/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/extensions/api/qorai_theme_api.h"

#include <optional>

#include "qorai/browser/themes/qorai_dark_mode_utils.h"
#include "qorai/common/extensions/api/qorai_theme.h"

namespace extensions::api {

ExtensionFunction::ResponseAction QoraiThemeSetQoraiThemeTypeFunction::Run() {
  std::optional<qorai_theme::SetQoraiThemeType::Params> params =
      qorai_theme::SetQoraiThemeType::Params::Create(args());
  EXTENSION_FUNCTION_VALIDATE(params);

  dark_mode::SetQoraiDarkModeType(params->type);

  return RespondNow(NoArguments());
}

}  // namespace extensions::api
