/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_QORAI_VPN_CONNECTION_INFO_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_QORAI_VPN_CONNECTION_INFO_H_

#include <string>

namespace qorai_vpn {

class QoraiVPNConnectionInfo {
 public:
  QoraiVPNConnectionInfo();
  ~QoraiVPNConnectionInfo();
  QoraiVPNConnectionInfo(const QoraiVPNConnectionInfo& info);
  QoraiVPNConnectionInfo& operator=(const QoraiVPNConnectionInfo& info);

  void Reset();
  bool IsValid() const;
  void SetConnectionInfo(const std::string& connection_name,
                         const std::string& hostname,
                         const std::string& username,
                         const std::string& password,
                         bool smart_routing_enabled,
                         const std::string& proxy);

  std::string connection_name() const { return connection_name_; }
  std::string hostname() const { return hostname_; }
  std::string username() const { return username_; }
  std::string password() const { return password_; }
  bool smart_routing_enabled() const { return smart_routing_enabled_; }
  std::string proxy() const { return proxy_; }
  void set_smart_routing_enabled(bool enabled) {
    smart_routing_enabled_ = enabled;
  }

 private:
  std::string connection_name_;
  std::string hostname_;
  std::string username_;
  std::string password_;
  bool smart_routing_enabled_;
  std::string proxy_;
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_QORAI_VPN_CONNECTION_INFO_H_
