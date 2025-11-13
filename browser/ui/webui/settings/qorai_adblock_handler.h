/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_ADBLOCK_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_ADBLOCK_HANDLER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_subscription_service_manager.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_subscription_service_manager_observer.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_custom_resource_provider.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "components/prefs/pref_change_registrar.h"

class Profile;
using qorai_shields::AdBlockSubscriptionServiceManager;
using qorai_shields::AdBlockSubscriptionServiceManagerObserver;

class QoraiAdBlockHandler
    : public settings::SettingsPageUIHandler,
      public AdBlockSubscriptionServiceManagerObserver,
      public qorai_shields::AdBlockCustomResourceProvider::Observer {
 public:
  QoraiAdBlockHandler();
  QoraiAdBlockHandler(const QoraiAdBlockHandler&) = delete;
  QoraiAdBlockHandler& operator=(const QoraiAdBlockHandler&) = delete;
  ~QoraiAdBlockHandler() override;

 private:
  // SettingsPageUIHandler overrides
  void RegisterMessages() override;

  // qorai_shields::AdblockSubscriptionServiceManagerObserver overrides:
  void OnServiceUpdateEvent() override;

  // qorai_shields::AdBlockCustomResourceProvider::Observer:
  void OnCustomResourcesChanged() override;

  void OnJavascriptAllowed() override;
  void OnJavascriptDisallowed() override;

  void GetRegionalLists(const base::Value::List& args);
  void EnableFilterList(const base::Value::List& args);
  void UpdateFilterLists(const base::Value::List& args);
  void GetListSubscriptions(const base::Value::List& args);
  void GetCustomFilters(const base::Value::List& args);
  void AddSubscription(const base::Value::List& args);
  void SetSubscriptionEnabled(const base::Value::List& args);
  void UpdateSubscription(const base::Value::List& args);
  void DeleteSubscription(const base::Value::List& args);
  void ViewSubscriptionSource(const base::Value::List& args);
  void UpdateCustomFilters(const base::Value::List& args);
  void GetCustomScriptlets(const base::Value::List& args);
  void OnGetCustomScriptlets(const std::string& callback_id,
                             base::Value custom_resources);
  void AddCustomScriptlet(const base::Value::List& args);
  void UpdateCustomScriptlet(const base::Value::List& args);
  void RemoveCustomScriptlet(const base::Value::List& args);
  void OnScriptletUpdateStatus(
      const std::string& callback_id,
      qorai_shields::AdBlockCustomResourceProvider::ErrorCode error_code);

  void RefreshSubscriptionsList();
  void RefreshCustomFilters();

  base::Value::List GetSubscriptions();

  void OnFilterListsUpdated(std::string callback_id, bool success);

  base::ScopedObservation<AdBlockSubscriptionServiceManager,
                          AdBlockSubscriptionServiceManagerObserver>
      service_observer_{this};

  base::ScopedObservation<
      qorai_shields::AdBlockCustomResourceProvider,
      qorai_shields::AdBlockCustomResourceProvider::Observer>
      custom_resources_observer_{this};

  PrefChangeRegistrar pref_change_registrar_;

  base::WeakPtrFactory<QoraiAdBlockHandler> weak_factory_{this};
};

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_ADBLOCK_HANDLER_H_
