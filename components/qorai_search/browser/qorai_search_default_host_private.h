// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_DEFAULT_HOST_PRIVATE_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_DEFAULT_HOST_PRIVATE_H_

#include "qorai/components/qorai_search/common/qorai_search_default.mojom.h"

class TemplateURLService;
class PrefService;

namespace qorai_search {

class QoraiSearchDefaultHostPrivate final
    : public qorai_search::mojom::QoraiSearchDefault {
 public:
  QoraiSearchDefaultHostPrivate(const QoraiSearchDefaultHostPrivate&) = delete;
  QoraiSearchDefaultHostPrivate& operator=(
      const QoraiSearchDefaultHostPrivate&) = delete;

  QoraiSearchDefaultHostPrivate() = default;
  ~QoraiSearchDefaultHostPrivate() override;

  // qorai_search::mojom::QoraiSearchDefault:
  void SetCanAlwaysSetDefault() override;
  void GetCanSetDefaultSearchProvider(
      GetCanSetDefaultSearchProviderCallback callback) override;
  void SetIsDefaultSearchProvider() override;
};

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_BROWSER_QORAI_SEARCH_DEFAULT_HOST_PRIVATE_H_
