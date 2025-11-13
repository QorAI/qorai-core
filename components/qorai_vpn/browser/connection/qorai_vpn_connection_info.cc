/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_connection_info.h"

namespace qorai_vpn {

QoraiVPNConnectionInfo::QoraiVPNConnectionInfo() = default;
QoraiVPNConnectionInfo::~QoraiVPNConnectionInfo() = default;

QoraiVPNConnectionInfo::QoraiVPNConnectionInfo(
    const QoraiVPNConnectionInfo& info) = default;
QoraiVPNConnectionInfo& QoraiVPNConnectionInfo::operator=(
    const QoraiVPNConnectionInfo& info) = default;

void QoraiVPNConnectionInfo::Reset() {
  connection_name_.clear();
  hostname_.clear();
  username_.clear();
  password_.clear();
  smart_routing_enabled_ = false;
  proxy_.clear();
}

bool QoraiVPNConnectionInfo::IsValid() const {
  // TODO(simonhong): Improve credentials validation.
  return !hostname_.empty() && !username_.empty() && !password_.empty();
}

void QoraiVPNConnectionInfo::SetConnectionInfo(
    const std::string& connection_name,
    const std::string& hostname,
    const std::string& username,
    const std::string& password,
    const bool smart_routing_enabled,
    const std::string& proxy) {
  connection_name_ = connection_name;
  hostname_ = hostname;
  username_ = username;
  password_ = password;
  smart_routing_enabled_ = smart_routing_enabled;
  proxy_ = proxy;
}

}  // namespace qorai_vpn
