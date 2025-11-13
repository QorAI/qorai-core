/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/autocomplete/qorai_autocomplete_scheme_classifier.h"
#include "components/omnibox/browser/autocomplete_classifier.h"
#include "components/omnibox/browser/autocomplete_controller.h"

#define ChromeAutocompleteSchemeClassifier QoraiAutocompleteSchemeClassifier
#include <chrome/browser/android/omnibox/autocomplete_controller_android.cc>
#undef ChromeAutocompleteSchemeClassifier
