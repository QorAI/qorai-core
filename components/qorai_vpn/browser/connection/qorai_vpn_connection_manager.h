/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_QORAI_VPN_CONNECTION_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_QORAI_VPN_CONNECTION_MANAGER_H_

#include <memory>
#include <string>
#include <utility>

#include "base/functional/callback_forward.h"
#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "base/one_shot_event.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_region_data_manager.h"
#include "qorai/components/qorai_vpn/browser/connection/connection_api_impl.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#include "components/prefs/pref_member.h"

namespace network {
class SharedURLLoaderFactory;
}  // namespace network

class PrefService;

namespace qorai_vpn {

class QoraiVPNRegionDataManager;

// Interface for managing vpn connection & region data.
//   * QoraiVPNRegionDataManager: Manages region data.
//   * ConnectionAPIImpl: Manages connection state.
// All client should use this class to manage VPN connection.
// This class will have proper concrete implemention of ConnectionAPIImpl
// based on current protocol(ikev2/wireguard).
class QoraiVPNConnectionManager {
 public:
  using ConnectionAPIImplGetter =
      base::RepeatingCallback<std::unique_ptr<ConnectionAPIImpl>(
          QoraiVPNConnectionManager*,
          scoped_refptr<network::SharedURLLoaderFactory>,
          bool)>;

  explicit QoraiVPNConnectionManager(
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
      PrefService* local_prefs,
      base::RepeatingCallback<bool()> service_installer);
  virtual ~QoraiVPNConnectionManager();

  class Observer : public base::CheckedObserver {
   public:
    virtual void OnConnectionStateChanged(mojom::ConnectionState state) = 0;
    // false when fetching region data is failed.
    virtual void OnRegionDataReady(bool success) {}
    virtual void OnSelectedRegionChanged(const std::string& region_name) {}

   protected:
    ~Observer() override = default;
  };

  QoraiVPNRegionDataManager& GetRegionDataManager();

  // Shared APIs implementation between IKEv2/Wireguard connections.
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  std::string GetHostname() const;

  void ResetConnectionState();
  mojom::ConnectionState GetConnectionState() const;
  void ToggleConnection();
  void Connect();
  void Disconnect();
  void CheckConnection();

  void SetSelectedRegion(const std::string& name);

  // Returns user friendly error string if existed.
  // Otherwise returns empty.
  std::string GetLastConnectionError() const;
  void MaybeInstallSystemServices();

  void NotifyConnectionStateChanged(mojom::ConnectionState state) const;
  void NotifySelectedRegionChanged(const std::string& name) const;

  void set_connection_api_impl_getter(ConnectionAPIImplGetter getter) {
    connection_api_impl_getter_ = std::move(getter);
  }

  void UpdateConnectionAPIImpl();

  PrefService* local_prefs() const { return local_prefs_; }
  std::string target_vpn_entry_name() const { return target_vpn_entry_name_; }
  void set_target_vpn_entry_name(const std::string& name) {
    target_vpn_entry_name_ = name;
  }

 private:
  friend class QoraiVpnButtonUnitTest;
  friend class QoraiVPNServiceTest;
  friend class QoraiVPNWireguardConnectionAPIUnitTest;
  friend class SystemVPNConnectionAPIUnitTest;
  FRIEND_TEST_ALL_PREFIXES(QoraiVPNWireguardConnectionAPIUnitTest,
                           SetSelectedRegion);

  void SetConnectionAPIImplForTesting(std::unique_ptr<ConnectionAPIImpl> impl) {
    connection_api_impl_ = std::move(impl);
  }

  std::string GetCurrentEnvironment() const;

  // QoraiVPNRegionDataManager callbacks
  // Notify it's ready when |regions_| is not empty.
  void NotifyRegionDataReady(bool ready) const;

  void OnInstallSystemServicesCompleted(bool success);

  // For now, this is called when Connect() is called.
  // If system service installation is in-progress, connect request
  // is queued and return true.
  // Then, start connect after installation is done.
  bool ScheduleConnectRequestIfNeeded();

  // Installs system services (if neeeded) or is nullptr.
  // Bound in qorai_vpn::CreateQoraiVPNConnectionAPI.
  base::RepeatingCallback<bool()> install_system_service_callback_;

  ConnectionAPIImplGetter connection_api_impl_getter_;

#if BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
  BooleanPrefMember wireguard_enabled_;
#endif

  raw_ptr<PrefService> local_prefs_ = nullptr;
  std::string target_vpn_entry_name_;
  scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory_;
  std::unique_ptr<ConnectionAPIImpl> connection_api_impl_;
  QoraiVPNRegionDataManager region_data_manager_;
  base::ObserverList<Observer> observers_;

  // Used for tracking if the VPN dependencies are being installed.
  // Guard against calling install_system_service_callback_ while a call
  // is already in progress.
  bool install_in_progress_ = false;

  // Used for tracking if the VPN dependencies have been installed.
  // If the user has Qorai VPN purchased and loaded with this profile
  // AND they did a system level install, we should call
  // install_system_service_callback_ once per browser open.
  base::OneShotEvent system_service_installed_event_;

  base::WeakPtrFactory<QoraiVPNConnectionManager> weak_factory_;
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_QORAI_VPN_CONNECTION_MANAGER_H_
