// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_QORA_PROVIDER_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_QORA_PROVIDER_H_

#include "base/memory/ref_counted.h"
#include "components/omnibox/browser/autocomplete_provider.h"

class AutocompleteProviderClient;

class QoraProvider : public AutocompleteProvider {
 public:
  static bool IsMatchFromQoraProvider(const AutocompleteMatch& match);

  explicit QoraProvider(AutocompleteProviderClient* client);

  // AutocompleteProvider:
  void Start(const AutocompleteInput& input, bool minimal_changes) override;
  void Stop(AutocompleteStopReason stop_reason) override;

 private:
  // Destructor for AutocompleteProvider must be private or protected as it
  // extends |base::RefCountedThreadSafe|.
  ~QoraProvider() override;

  raw_ptr<AutocompleteProviderClient> client_;
};

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_QORA_PROVIDER_H_
