// Copyright (c) 2022 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_VPN_DNS_HANDLER_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_VPN_DNS_HANDLER_H_

#include <windows.h>

#include <optional>
#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "base/task/sequenced_task_runner.h"
#include "base/timer/timer.h"
#include "base/win/object_watcher.h"

namespace qorai_vpn {

namespace ras {
enum class CheckConnectionResult;
}  // namespace ras

class QorAIVpnDnsDelegate;
class MockVpnDnsHandler;

class VpnDnsHandler : public base::win::ObjectWatcher::Delegate {
 public:
  explicit VpnDnsHandler(QorAIVpnDnsDelegate* delegate);
  ~VpnDnsHandler() override;

  void StartVPNConnectionChangeMonitoring();

 protected:
  // base::win::ObjectWatcher::Delegate overrides:
  void OnObjectSignaled(HANDLE object) override;

  ras::CheckConnectionResult GetVpnEntryStatus();
  bool CloseEngineSession();

  bool SetFilters(const std::wstring& connection_name);
  bool RemoveFilters(const std::wstring& connection_name);
  bool IsActive() const;
  bool IsExitTimerRunningForTesting();
  void SetConnectionResultForTesting(ras::CheckConnectionResult result);
  void SetCloseEngineResultForTesting(bool value);
  void SetPlatformFiltersResultForTesting(bool value);
  void SetWaitingIntervalBeforeExitForTesting(int value);
  void UpdateFiltersState();
  void ScheduleExit();

 private:
  friend class MockVpnDnsHandler;
  FRIEND_TEST_ALL_PREFIXES(VpnDnsHandlerTest,
                           ConnectingSuccessFiltersInstalled);

  bool SetupPlatformFilters(HANDLE engine_handle, const std::string& name);
  int GetWaitingIntervalBeforeExit();
  void CloseWatchers();
  void DisconnectVPN();
  void Exit();
  virtual void SubscribeForRasNotifications(HANDLE event_handle);

  std::optional<ras::CheckConnectionResult> connection_result_for_testing_;
  std::optional<bool> platform_filters_result_for_testing_;
  std::optional<bool> close_engine_result_for_testing_;
  std::optional<int> waiting_interval_before_exit_for_testing_;
  raw_ptr<QorAIVpnDnsDelegate> delegate_;
  HANDLE engine_ = nullptr;
  HANDLE event_handle_for_vpn_ = nullptr;
  base::win::ObjectWatcher connected_disconnected_event_watcher_;
  base::RepeatingTimer periodic_timer_;
  base::OneShotTimer exit_timer_;
  base::WeakPtrFactory<VpnDnsHandler> weak_factory_{this};
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_HELPER_VPN_DNS_HANDLER_H_
