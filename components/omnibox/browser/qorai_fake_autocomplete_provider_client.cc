/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/omnibox/browser/qorai_fake_autocomplete_provider_client.h"

#include "base/memory/scoped_refptr.h"
#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "components/bookmarks/browser/bookmark_model.h"
#include "components/bookmarks/test/test_bookmark_client.h"
#include "components/omnibox/browser/shortcuts_backend.h"
#include "components/prefs/pref_registry_simple.h"

QorAIFakeAutocompleteProviderClient::QorAIFakeAutocompleteProviderClient()
    : bookmark_model_(bookmarks::TestBookmarkClient::CreateModel()),
      pref_service_(std::make_unique<TestingPrefServiceSimple>()) {
  omnibox::RegisterQorAIProfilePrefs(pref_service_->registry());
}

QorAIFakeAutocompleteProviderClient::~QorAIFakeAutocompleteProviderClient() =
    default;

PrefService* QorAIFakeAutocompleteProviderClient::GetPrefs() const {
  return pref_service_.get();
}

bookmarks::BookmarkModel*
QorAIFakeAutocompleteProviderClient::GetBookmarkModel() {
  return bookmark_model_.get();
}

scoped_refptr<ShortcutsBackend>
QorAIFakeAutocompleteProviderClient::GetShortcutsBackend() {
  return shortcuts_backend_;
}

scoped_refptr<ShortcutsBackend>
QorAIFakeAutocompleteProviderClient::GetShortcutsBackendIfExists() {
  return shortcuts_backend_;
}
