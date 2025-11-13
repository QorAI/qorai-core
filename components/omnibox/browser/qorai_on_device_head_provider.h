// Copyright (c) 2025 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_ON_DEVICE_HEAD_PROVIDER_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_ON_DEVICE_HEAD_PROVIDER_H_

#include "components/omnibox/browser/on_device_head_provider.h"

class QorAIOnDeviceHeadProvider : public OnDeviceHeadProvider {
 public:
  static QorAIOnDeviceHeadProvider* Create(
      AutocompleteProviderClient* client,
      AutocompleteProviderListener* listener);

  void Start(const AutocompleteInput& input, bool minimal_changes) override;

 protected:
  using OnDeviceHeadProvider::OnDeviceHeadProvider;
  ~QorAIOnDeviceHeadProvider() override;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORAI_ON_DEVICE_HEAD_PROVIDER_H_
