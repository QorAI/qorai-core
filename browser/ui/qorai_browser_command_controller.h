/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_BROWSER_COMMAND_CONTROLLER_H_
#define QORAI_BROWSER_UI_QORAI_BROWSER_COMMAND_CONTROLLER_H_

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/raw_ref.h"
#include "base/scoped_observation.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "components/prefs/pref_change_registrar.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"
#endif

class QoraiAppMenuBrowserTest;
class QoraiAppMenuModelBrowserTest;
class QoraiBrowserCommandControllerTest;
enum class TabChangeType;

namespace content {
class WebContents;
}

// This namespace is needed for a chromium_src override
namespace chrome {

class QoraiBrowserCommandController : public chrome::BrowserCommandController
#if BUILDFLAG(ENABLE_QORAI_VPN)
    ,
                                      public qorai_vpn::QoraiVPNServiceObserver
#endif
{
 public:
  explicit QoraiBrowserCommandController(BrowserWindowInterface* bwi);
  QoraiBrowserCommandController(const QoraiBrowserCommandController&) = delete;
  QoraiBrowserCommandController& operator=(
      const QoraiBrowserCommandController&) = delete;
  ~QoraiBrowserCommandController() override;

#if BUILDFLAG(ENABLE_TOR)
  void UpdateCommandForTor();
#endif

 protected:
  void TabChangedAt(content::WebContents* contents,
                    int index,
                    TabChangeType change) override;
  void TabPinnedStateChanged(TabStripModel* tab_strip_model,
                             content::WebContents* contents,
                             int index) override;
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;
  void OnTabGroupChanged(const TabGroupChange& change) override;
  void OnSplitTabChanged(const SplitTabChange& change) override;

 private:
  friend class ::QoraiAppMenuBrowserTest;
  friend class ::QoraiAppMenuModelBrowserTest;
  friend class ::QoraiBrowserCommandControllerTest;

  // Overriden from CommandUpdater:
  bool SupportsCommand(int id) const override;
  bool IsCommandEnabled(int id) const override;
  bool ExecuteCommandWithDisposition(
      int id,
      WindowOpenDisposition disposition,
      base::TimeTicks time_stamp = base::TimeTicks::Now()) override;
  void AddCommandObserver(int id, CommandObserver* observer) override;
  void RemoveCommandObserver(int id, CommandObserver* observer) override;
  void RemoveCommandObserver(CommandObserver* observer) override;
  bool UpdateCommandEnabled(int id, bool state) override;

#if BUILDFLAG(ENABLE_QORAI_VPN)
  // qorai_vpn::QoraiVPNServiceObserver overrides:
  void OnPurchasedStateChanged(
      qorai_vpn::mojom::PurchasedState state,
      const std::optional<std::string>& description) override;
#endif

  void InitQoraiCommandState();
  void UpdateCommandForQoraiRewards();
  void UpdateCommandForWebcompatReporter();
  void UpdateCommandForQoraiSync();
  void UpdateCommandForQoraiWallet();
  void UpdateCommandForSidebar();
  void UpdateCommandForAIChat();
  void UpdateCommandForQoraiVPN();
  void UpdateCommandForPlaylist();
  void UpdateCommandForWaybackMachine();
  void UpdateCommandsForTabs();
  void UpdateCommandsForSend();
  void UpdateCommandsForPin();
  void UpdateCommandForSplitView();

  bool ExecuteQoraiCommandWithDisposition(int id,
                                          WindowOpenDisposition disposition,
                                          base::TimeTicks time_stamp);

  PrefChangeRegistrar pref_change_registrar_;
  const raw_ref<Browser> browser_;

  CommandUpdaterImpl qorai_command_updater_;
};

}  // namespace chrome

#endif  // QORAI_BROWSER_UI_QORAI_BROWSER_COMMAND_CONTROLLER_H_
