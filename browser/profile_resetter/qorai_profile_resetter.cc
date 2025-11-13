/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/profile_resetter/qorai_profile_resetter.h"

#include "qorai/browser/search_engines/search_engine_provider_util.h"

QoraiProfileResetter::~QoraiProfileResetter() = default;

void QoraiProfileResetter::ResetDefaultSearchEngine() {
  ProfileResetter::ResetDefaultSearchEngine();

  if (template_url_service_->loaded()) {
    qorai::ResetDefaultPrivateSearchProvider(*profile_);
  }
}
