/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_URL_HOST_INTERFACE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_URL_HOST_INTERFACE_H_

#include <string>

namespace qorai_ads {

class UrlHostInterface {
 public:
  virtual ~UrlHostInterface() = default;

  // Returns the host URL.
  virtual std::string Get() const = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_REQUEST_BUILDER_HOST_HOSTS_URL_HOST_INTERFACE_H_
