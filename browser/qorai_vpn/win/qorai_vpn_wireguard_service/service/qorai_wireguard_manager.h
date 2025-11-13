/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_SERVICE_QORAI_WIREGUARD_MANAGER_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_SERVICE_QORAI_WIREGUARD_MANAGER_H_

#include <wrl/implements.h>
#include <wrl/module.h>

#include "base/win/windows_types.h"
#include "qorai/components/qorai_vpn/common/wireguard/win/qorai_wireguard_manager_idl.h"

namespace qorai_vpn {

class QorAIWireguardManager
    : public Microsoft::WRL::RuntimeClass<
          Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
          IQorAIVpnWireguardManager> {
 public:
  QorAIWireguardManager() = default;

  QorAIWireguardManager(const QorAIWireguardManager&) = delete;
  QorAIWireguardManager& operator=(const QorAIWireguardManager&) = delete;

  IFACEMETHODIMP EnableVpn(BSTR public_key,
                           BSTR private_key,
                           BSTR address,
                           BSTR endpoint,
                           DWORD* last_error) override;
  IFACEMETHODIMP DisableVpn(DWORD* last_error) override;

 private:
  ~QorAIWireguardManager() override = default;
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_SERVICE_QORAI_WIREGUARD_MANAGER_H_
