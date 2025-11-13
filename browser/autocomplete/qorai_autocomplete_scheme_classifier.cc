/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/autocomplete/qorai_autocomplete_scheme_classifier.h"

#include <string>

#include "base/strings/string_util.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/constants/url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"

QoraiAutocompleteSchemeClassifier::QoraiAutocompleteSchemeClassifier(
    Profile* profile)
    : ChromeAutocompleteSchemeClassifier(profile) {}

QoraiAutocompleteSchemeClassifier::~QoraiAutocompleteSchemeClassifier() =
    default;

// Without this override, typing in qorai:// URLs will search Google
metrics::OmniboxInputType
QoraiAutocompleteSchemeClassifier::GetInputTypeForScheme(
    const std::string& scheme) const {
  if (scheme.empty()) {
    return metrics::OmniboxInputType::EMPTY;
  }
  if (base::IsStringASCII(scheme) &&
      base::EqualsCaseInsensitiveASCII(scheme, kQoraiUIScheme)) {
    return metrics::OmniboxInputType::URL;
  }

  return ChromeAutocompleteSchemeClassifier::GetInputTypeForScheme(scheme);
}
