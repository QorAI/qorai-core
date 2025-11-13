// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_news/browser/urls.h"

#include <string>

#include "qorai/qorai_domains/service_domains.h"

namespace qorai_news {

std::string GetHostname() {
  return qorai_domains::GetServicesDomain("qorai-today-cdn");
}

}  // namespace qorai_news
