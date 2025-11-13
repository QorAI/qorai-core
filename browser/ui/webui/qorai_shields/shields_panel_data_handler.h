// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_SHIELDS_SHIELDS_PANEL_DATA_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_SHIELDS_SHIELDS_PANEL_DATA_HANDLER_H_

#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"
#include "qorai/components/qorai_shields/core/common/qorai_shields_panel.mojom.h"
#include "qorai/components/qorai_shields/core/common/shields_settings.mojom.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

class TabStripModel;

class TopChromeWebUIController;

class ShieldsPanelDataHandler
    : public qorai_shields::mojom::DataHandler,
      public qorai_shields::QoraiShieldsTabHelper::Observer,
      public TabStripModelObserver {
 public:
  ShieldsPanelDataHandler(
      mojo::PendingReceiver<qorai_shields::mojom::DataHandler>
          data_handler_receiver,
      TopChromeWebUIController* webui_controller,
      TabStripModel* browser);

  ShieldsPanelDataHandler(const ShieldsPanelDataHandler&) = delete;
  ShieldsPanelDataHandler& operator=(const ShieldsPanelDataHandler&) = delete;
  ~ShieldsPanelDataHandler() override;

  // mojom::DataHandler
  void RegisterUIHandler(mojo::PendingRemote<qorai_shields::mojom::UIHandler>
                             ui_handler_receiver) override;
  void GetSiteBlockInfo(GetSiteBlockInfoCallback callback) override;
  void GetSiteSettings(GetSiteSettingsCallback callback) override;
  void SetAdBlockMode(AdBlockMode callback) override;
  void SetFingerprintMode(FingerprintMode mode) override;
  void SetCookieBlockMode(CookieBlockMode mode) override;
  void SetHttpsUpgradeMode(HttpsUpgradeMode mode) override;
  void SetIsNoScriptsEnabled(bool is_enabled) override;
  void SetQoraiShieldsEnabled(bool is_enabled) override;
  void SetQoraiShieldsAdBlockOnlyModeEnabled(bool is_enabled) override;
  void SetQoraiShieldsAdBlockOnlyModePromptDismissed() override;
  void SetForgetFirstPartyStorageEnabled(bool is_enabled) override;
  void OpenWebCompatWindow() override;
  void UpdateFavicon() override;
  void AllowScriptsOnce(const std::vector<std::string>& origins) override;
  void BlockAllowedScripts(const std::vector<std::string>& origins) override;
  void SetWebcompatEnabled(ContentSettingsType webcompat_settings_type,
                           bool enabled) override;
  void ResetBlockedElements() override;
  void AreAnyBlockedElementsPresent(
      AreAnyBlockedElementsPresentCallback callback) override;

 private:
  void UpdateSiteBlockInfo();

  // QoraiShieldsTabHelper::Observer
  void OnResourcesChanged() override;
  void OnFaviconUpdated() override;
  void OnShieldsAdBlockOnlyModeEnabledChanged() override;

  // TabStripModelObserver
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;

  mojo::Receiver<qorai_shields::mojom::DataHandler> data_handler_receiver_;
  mojo::Remote<qorai_shields::mojom::UIHandler> ui_handler_remote_;
  raw_ptr<TopChromeWebUIController> const webui_controller_ = nullptr;
  raw_ptr<qorai_shields::QoraiShieldsTabHelper>
      active_shields_data_controller_ = nullptr;

  qorai_shields::mojom::SiteBlockInfo site_block_info_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_SHIELDS_SHIELDS_PANEL_DATA_HANDLER_H_
