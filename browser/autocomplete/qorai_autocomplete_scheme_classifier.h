/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_AUTOCOMPLETE_QORAI_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_
#define QORAI_BROWSER_AUTOCOMPLETE_QORAI_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

#include <string>

#include "chrome/browser/autocomplete/chrome_autocomplete_scheme_classifier.h"

class QorAIAutocompleteSchemeClassifier
    : public ChromeAutocompleteSchemeClassifier {
 public:
  explicit QorAIAutocompleteSchemeClassifier(Profile* profile);
  QorAIAutocompleteSchemeClassifier(const QorAIAutocompleteSchemeClassifier&) =
      delete;
  QorAIAutocompleteSchemeClassifier& operator=(
      const QorAIAutocompleteSchemeClassifier&) = delete;
  ~QorAIAutocompleteSchemeClassifier() override;

  metrics::OmniboxInputType GetInputTypeForScheme(
      const std::string& scheme) const override;
};

#endif  // QORAI_BROWSER_AUTOCOMPLETE_QORAI_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

