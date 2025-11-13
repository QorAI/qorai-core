// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "chrome/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/customize_toolbar_handler.h"

#include "base/containers/map_util.h"
#include "base/memory/raw_ref.h"
#include "base/notreached.h"
#include "qorai/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/qorai_action.h"
#include "qorai/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/list_action_modifiers.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/grit/generated_resources.h"
#include "components/grit/qorai_components_strings.h"

#define ListCategories ListCategories_ChromiumImpl
#define ListActions ListActions_ChromiumImpl
#define PinAction PinAction_ChromiumImpl

// pref_change_registrar_.Init() in constructor
#define Init(...)    \
  Init(__VA_ARGS__); \
  ObserveQoraiActions()

// Replace the resource ID for the "Your Chrome" category with "Qorai Menu"
// resource ID.
#undef IDS_NTP_CUSTOMIZE_TOOLBAR_CATEGORY_YOUR_CHROME
#define IDS_NTP_CUSTOMIZE_TOOLBAR_CATEGORY_YOUR_CHROME \
  IDS_CUSTOMIZE_TOOLBAR_CATEGORY_TOOLBAR

#include <chrome/browser/ui/webui/side_panel/customize_chrome/customize_toolbar/customize_toolbar_handler.cc>

#undef IDS_NTP_CUSTOMIZE_TOOLBAR_CATEGORY_YOUR_CHROME

#undef Init
#undef PinAction
#undef ListActions
#undef ListCategories

void CustomizeToolbarHandler::ListCategories(ListCategoriesCallback callback) {
  ListCategories_ChromiumImpl(
      base::BindOnce(
          &customize_chrome::AppendQoraiSpecificCategories,
          base::Unretained(base::raw_ref<content::WebContents>(*web_contents_)))
          .Then(std::move(callback)));
}

void CustomizeToolbarHandler::ListActions(ListActionsCallback callback) {
  ListActions_ChromiumImpl(
      base::BindOnce(&customize_chrome::FilterUnsupportedChromiumActions)
          .Then(base::BindOnce(
              &customize_chrome::ApplyQoraiSpecificModifications,
              base::Unretained(
                  base::raw_ref<content::WebContents>(*web_contents_))))
          .Then(std::move(callback)));
}

void CustomizeToolbarHandler::PinAction(
    side_panel::customize_chrome::mojom::ActionId action_id,
    bool pin) {
  if (const auto* qorai_action =
          base::FindPtrOrNull(customize_chrome::kQoraiActions, action_id)) {
    // Qorai specific actions are handled here.
    prefs()->SetBoolean(qorai_action->pref_name,
                        !prefs()->GetBoolean(qorai_action->pref_name));
    return;
  }

  PinAction_ChromiumImpl(action_id, pin);
}

void CustomizeToolbarHandler::ObserveQoraiActions() {
  for (const auto& [id, qorai_action] : customize_chrome::kQoraiActions) {
    pref_change_registrar_.Add(
        qorai_action->pref_name,
        base::BindRepeating(
            &CustomizeToolbarHandler::OnQoraiActionPinnedChanged,
            base::Unretained(this), id));
  }
}

void CustomizeToolbarHandler::OnQoraiActionPinnedChanged(
    side_panel::customize_chrome::mojom::ActionId action_id) {
  const auto* qorai_action =
      base::FindPtrOrNull(customize_chrome::kQoraiActions, action_id);
  CHECK(qorai_action);
  client_->SetActionPinned(action_id,
                           prefs()->GetBoolean(qorai_action->pref_name));
}
