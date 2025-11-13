// Copyright (c) 2025 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/omnibox/browser/qorai_on_device_head_provider.h"

#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"
#include "components/prefs/pref_service.h"

// static
QorAIOnDeviceHeadProvider* QorAIOnDeviceHeadProvider::Create(
    AutocompleteProviderClient* client,
    AutocompleteProviderListener* listener) {
  return new QorAIOnDeviceHeadProvider(client, listener);
}

void QorAIOnDeviceHeadProvider::Start(const AutocompleteInput& input,
                                      bool minimal_changes) {
  auto* prefs = client_->GetPrefs();
  if (!prefs || !prefs->GetBoolean(omnibox::kOnDeviceSuggestionsEnabled)) {
    matches_.clear();
    return;
  }
  OnDeviceHeadProvider::Start(input, minimal_changes);
}

QorAIOnDeviceHeadProvider::~QorAIOnDeviceHeadProvider() = default;
