/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_API_QORAI_VPN_API_HELPER_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_API_QORAI_VPN_API_HELPER_H_

#include <memory>
#include <string>
#include <vector>

#include "base/values.h"

namespace base {
class Value;
}  // namespace base

namespace qorai_vpn {

struct Hostname;

std::unique_ptr<Hostname> PickBestHostname(
    const std::vector<Hostname>& hostnames);
std::vector<Hostname> ParseHostnames(const base::Value::List& hostnames);
std::string GetTimeZoneName();
base::Value::Dict GetValueWithTicketInfos(
    const std::string& email,
    const std::string& subject,
    const std::string& body,
    const std::string& subscriber_credential,
    const std::string& timezone);

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_API_QORAI_VPN_API_HELPER_H_
