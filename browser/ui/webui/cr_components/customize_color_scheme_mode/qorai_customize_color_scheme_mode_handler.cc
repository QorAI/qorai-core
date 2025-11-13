// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/cr_components/customize_color_scheme_mode/qorai_customize_color_scheme_mode_handler.h"

#include <utility>

#include "qorai/browser/themes/qorai_dark_mode_utils.h"
#include "qorai/components/constants/pref_names.h"
#include "chrome/browser/browser_process.h"

QoraiCustomizeColorSchemeModeHandler::QoraiCustomizeColorSchemeModeHandler(
    mojo::PendingRemote<
        customize_color_scheme_mode::mojom::CustomizeColorSchemeModeClient>
        pending_client,
    mojo::PendingReceiver<
        customize_color_scheme_mode::mojom::CustomizeColorSchemeModeHandler>
        pending_receiver,
    Profile* profile)
    : CustomizeColorSchemeModeHandler(std::move(pending_client),
                                      std::move(pending_receiver),
                                      profile) {
  local_state_change_registrar_.Init(g_browser_process->local_state());
  local_state_change_registrar_.Add(
      kQoraiDarkMode,
      base::BindRepeating(
          &QoraiCustomizeColorSchemeModeHandler::UpdateColorSchemeMode,
          base::Unretained(this)));
}

void QoraiCustomizeColorSchemeModeHandler::SetColorSchemeMode(
    customize_color_scheme_mode::mojom::ColorSchemeMode color_mode) {
  dark_mode::QoraiDarkModeType type =
      dark_mode::QoraiDarkModeType::QORAI_DARK_MODE_TYPE_DEFAULT;
  if (color_mode ==
      customize_color_scheme_mode::mojom::ColorSchemeMode::kDark) {
    type = dark_mode::QoraiDarkModeType::QORAI_DARK_MODE_TYPE_DARK;
  } else if (color_mode ==
             customize_color_scheme_mode::mojom::ColorSchemeMode::kLight) {
    type = dark_mode::QoraiDarkModeType::QORAI_DARK_MODE_TYPE_LIGHT;
  }

  dark_mode::SetQoraiDarkModeType(type);
}

void QoraiCustomizeColorSchemeModeHandler::InitializeColorSchemeMode() {
  UpdateColorSchemeMode();
}

void QoraiCustomizeColorSchemeModeHandler::OnThemeChanged() {
  UpdateColorSchemeMode();
}

void QoraiCustomizeColorSchemeModeHandler::UpdateColorSchemeMode() {
  const dark_mode::QoraiDarkModeType type = dark_mode::GetQoraiDarkModeType();
  customize_color_scheme_mode::mojom::ColorSchemeMode color_mode =
      customize_color_scheme_mode::mojom::ColorSchemeMode::kSystem;
  if (type == dark_mode::QoraiDarkModeType::QORAI_DARK_MODE_TYPE_DARK) {
    color_mode = customize_color_scheme_mode::mojom::ColorSchemeMode::kDark;
  } else if (type == dark_mode::QoraiDarkModeType::QORAI_DARK_MODE_TYPE_LIGHT) {
    color_mode = customize_color_scheme_mode::mojom::ColorSchemeMode::kLight;
  }
  CHECK(remote_client_.is_bound() && remote_client_.is_connected());
  remote_client_->SetColorSchemeMode(color_mode);
}
