/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_API_VPN_RESPONSE_PARSER_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_API_VPN_RESPONSE_PARSER_H_

#include <string>

#include "base/values.h"

namespace qorai_vpn {

std::string ParseSubscriberCredentialFromJson(const base::Value& records_v,
                                              std::string* error);

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_API_VPN_RESPONSE_PARSER_H_
