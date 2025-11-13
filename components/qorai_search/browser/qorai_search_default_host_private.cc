// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_search/browser/qorai_search_default_host_private.h"

#include <utility>

namespace qorai_search {

QoraiSearchDefaultHostPrivate::~QoraiSearchDefaultHostPrivate() = default;

void QoraiSearchDefaultHostPrivate::SetCanAlwaysSetDefault() {}

void QoraiSearchDefaultHostPrivate::GetCanSetDefaultSearchProvider(
    GetCanSetDefaultSearchProviderCallback callback) {
  std::move(callback).Run(false);
}

void QoraiSearchDefaultHostPrivate::SetIsDefaultSearchProvider() {}

}  // namespace qorai_search
