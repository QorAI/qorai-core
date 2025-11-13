/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_adblock_handler.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "base/check_op.h"
#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/json/values_util.h"
#include "base/values.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/components/qorai_adblock/resources/grit/qorai_adblock_generated_map.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_custom_filters_provider.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_component_service_manager.h"
#include "qorai/components/qorai_shields/core/browser/ad_block_custom_resource_provider.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/singleton_tabs.h"
#include "content/public/browser/web_ui.h"
#include "ui/base/l10n/time_format.h"

QoraiAdBlockHandler::QoraiAdBlockHandler() = default;

QoraiAdBlockHandler::~QoraiAdBlockHandler() = default;

void QoraiAdBlockHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "qorai_adblock.getRegionalLists",
      base::BindRepeating(&QoraiAdBlockHandler::GetRegionalLists,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.enableFilterList",
      base::BindRepeating(&QoraiAdBlockHandler::EnableFilterList,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.updateFilterLists",
      base::BindRepeating(&QoraiAdBlockHandler::UpdateFilterLists,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.getListSubscriptions",
      base::BindRepeating(&QoraiAdBlockHandler::GetListSubscriptions,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.getCustomFilters",
      base::BindRepeating(&QoraiAdBlockHandler::GetCustomFilters,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.addSubscription",
      base::BindRepeating(&QoraiAdBlockHandler::AddSubscription,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.setSubscriptionEnabled",
      base::BindRepeating(&QoraiAdBlockHandler::SetSubscriptionEnabled,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.updateSubscription",
      base::BindRepeating(&QoraiAdBlockHandler::UpdateSubscription,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.deleteSubscription",
      base::BindRepeating(&QoraiAdBlockHandler::DeleteSubscription,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.viewSubscription",
      base::BindRepeating(&QoraiAdBlockHandler::ViewSubscriptionSource,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.updateCustomFilters",
      base::BindRepeating(&QoraiAdBlockHandler::UpdateCustomFilters,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.getCustomScriptlets",
      base::BindRepeating(&QoraiAdBlockHandler::GetCustomScriptlets,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.addCustomScriptlet",
      base::BindRepeating(&QoraiAdBlockHandler::AddCustomScriptlet,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.updateCustomScriptlet",
      base::BindRepeating(&QoraiAdBlockHandler::UpdateCustomScriptlet,
                          base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "qorai_adblock.removeCustomScriptlet",
      base::BindRepeating(&QoraiAdBlockHandler::RemoveCustomScriptlet,
                          base::Unretained(this)));
  pref_change_registrar_.Init(g_browser_process->local_state());
}

void QoraiAdBlockHandler::OnJavascriptAllowed() {
  service_observer_.Observe(g_qorai_browser_process->ad_block_service()
                                ->subscription_service_manager());
  custom_resources_observer_.Observe(
      g_qorai_browser_process->ad_block_service()->custom_resource_provider());
  pref_change_registrar_.Add(
      qorai_shields::prefs::kAdBlockCustomFilters,
      base::BindRepeating(&QoraiAdBlockHandler::RefreshCustomFilters,
                          weak_factory_.GetWeakPtr()));
}

void QoraiAdBlockHandler::OnJavascriptDisallowed() {
  service_observer_.Reset();
  custom_resources_observer_.Reset();
  pref_change_registrar_.RemoveAll();
}

void QoraiAdBlockHandler::OnServiceUpdateEvent() {
  if (!IsJavascriptAllowed()) {
    return;
  }

  RefreshSubscriptionsList();
}

void QoraiAdBlockHandler::OnCustomResourcesChanged() {
  if (!IsJavascriptAllowed()) {
    return;
  }
  FireWebUIListener("qorai_adblock.onCustomResourcesChanged");
}

void QoraiAdBlockHandler::GetRegionalLists(const base::Value::List& args) {
  AllowJavascript();
  auto regional_lists = g_qorai_browser_process->ad_block_service()
                            ->component_service_manager()
                            ->GetRegionalLists();

  ResolveJavascriptCallback(args[0], regional_lists);
}

void QoraiAdBlockHandler::EnableFilterList(const base::Value::List& args) {
  DCHECK_EQ(args.size(), 2U);

  if (!args[0].is_string() || !args[1].is_bool()) {
    return;
  }

  std::string uuid = args[0].GetString();
  bool enabled = args[1].GetBool();

  g_qorai_browser_process->ad_block_service()
      ->component_service_manager()
      ->EnableFilterList(uuid, enabled);
}

void QoraiAdBlockHandler::UpdateFilterLists(const base::Value::List& args) {
  AllowJavascript();

  DCHECK_EQ(args.size(), 1U);
  if (!args[0].is_string()) {
    return;
  }

  std::string callback_id = args[0].GetString();

  g_qorai_browser_process->ad_block_service()
      ->component_service_manager()
      ->UpdateFilterLists(
          base::BindOnce(&QoraiAdBlockHandler::OnFilterListsUpdated,
                         weak_factory_.GetWeakPtr(), std::move(callback_id)));
}

void QoraiAdBlockHandler::GetListSubscriptions(const base::Value::List& args) {
  AllowJavascript();
  ResolveJavascriptCallback(args[0], GetSubscriptions());
}

void QoraiAdBlockHandler::GetCustomFilters(const base::Value::List& args) {
  AllowJavascript();
  const std::string custom_filters = g_qorai_browser_process->ad_block_service()
                                         ->custom_filters_provider()
                                         ->GetCustomFilters();

  ResolveJavascriptCallback(args[0], base::Value(custom_filters));
}

void QoraiAdBlockHandler::AddSubscription(const base::Value::List& args) {
  DCHECK_EQ(args.size(), 1U);
  AllowJavascript();
  if (!args[0].is_string()) {
    return;
  }

  std::string subscription_url_string = args[0].GetString();
  const GURL subscription_url = GURL(subscription_url_string);

  if (!subscription_url.is_valid()) {
    return;
  }

  g_qorai_browser_process->ad_block_service()
      ->subscription_service_manager()
      ->CreateSubscription(subscription_url);

  RefreshSubscriptionsList();
}

void QoraiAdBlockHandler::SetSubscriptionEnabled(
    const base::Value::List& args) {
  DCHECK_EQ(args.size(), 2U);
  AllowJavascript();
  if (!args[0].is_string() || !args[1].is_bool()) {
    return;
  }

  std::string subscription_url_string = args[0].GetString();
  bool enabled = args[1].GetBool();
  const GURL subscription_url = GURL(subscription_url_string);
  if (!subscription_url.is_valid()) {
    return;
  }
  g_qorai_browser_process->ad_block_service()
      ->subscription_service_manager()
      ->EnableSubscription(subscription_url, enabled);

  RefreshSubscriptionsList();
}

void QoraiAdBlockHandler::UpdateSubscription(const base::Value::List& args) {
  DCHECK_EQ(args.size(), 1U);
  AllowJavascript();
  if (!args[0].is_string()) {
    return;
  }

  std::string subscription_url_string = args[0].GetString();
  const GURL subscription_url = GURL(subscription_url_string);

  if (!subscription_url.is_valid()) {
    return;
  }
  g_qorai_browser_process->ad_block_service()
      ->subscription_service_manager()
      ->RefreshSubscription(subscription_url, true);
}

void QoraiAdBlockHandler::DeleteSubscription(const base::Value::List& args) {
  DCHECK_EQ(args.size(), 1U);
  AllowJavascript();
  if (!args[0].is_string()) {
    return;
  }

  std::string subscription_url_string = args[0].GetString();
  const GURL subscription_url = GURL(subscription_url_string);
  if (!subscription_url.is_valid()) {
    return;
  }
  g_qorai_browser_process->ad_block_service()
      ->subscription_service_manager()
      ->DeleteSubscription(subscription_url);

  RefreshSubscriptionsList();
}

void QoraiAdBlockHandler::ViewSubscriptionSource(
    const base::Value::List& args) {
  DCHECK_EQ(args.size(), 1U);
  if (!args[0].is_string()) {
    return;
  }

  std::string subscription_url_string = args[0].GetString();
  const GURL subscription_url = GURL(subscription_url_string);
  if (!subscription_url.is_valid()) {
    return;
  }

  const GURL file_url = g_qorai_browser_process->ad_block_service()
                            ->subscription_service_manager()
                            ->GetListTextFileUrl(subscription_url);

  auto* browser = chrome::FindBrowserWithTab(web_ui()->GetWebContents());
  ShowSingletonTabOverwritingNTP(browser, file_url);
}

void QoraiAdBlockHandler::UpdateCustomFilters(const base::Value::List& args) {
  if (!args[0].is_string()) {
    return;
  }

  std::string custom_filters = args[0].GetString();
  g_qorai_browser_process->ad_block_service()
      ->custom_filters_provider()
      ->UpdateCustomFilters(custom_filters);
}

void QoraiAdBlockHandler::GetCustomScriptlets(const base::Value::List& args) {
  CHECK(base::FeatureList::IsEnabled(
      qorai_shields::features::kCosmeticFilteringCustomScriptlets));
  CHECK(args.size() == 1u && args[0].is_string());

  g_qorai_browser_process->ad_block_service()
      ->custom_resource_provider()
      ->GetCustomResources(
          base::BindOnce(&QoraiAdBlockHandler::OnGetCustomScriptlets,
                         weak_factory_.GetWeakPtr(), args[0].GetString()));
}

void QoraiAdBlockHandler::OnGetCustomScriptlets(const std::string& callback_id,
                                                base::Value custom_resources) {
  AllowJavascript();
  ResolveJavascriptCallback(callback_id, custom_resources);
}

void QoraiAdBlockHandler::AddCustomScriptlet(const base::Value::List& args) {
  CHECK(base::FeatureList::IsEnabled(
      qorai_shields::features::kCosmeticFilteringCustomScriptlets));
  CHECK(args.size() == 2u && args[0].is_string() && args[1].is_dict());

  g_qorai_browser_process->ad_block_service()
      ->custom_resource_provider()
      ->AddResource(
          Profile::FromWebUI(web_ui())->GetPrefs(), args[1],
          base::BindOnce(&QoraiAdBlockHandler::OnScriptletUpdateStatus,
                         weak_factory_.GetWeakPtr(), args[0].GetString()));
}

void QoraiAdBlockHandler::UpdateCustomScriptlet(const base::Value::List& args) {
  CHECK(base::FeatureList::IsEnabled(
      qorai_shields::features::kCosmeticFilteringCustomScriptlets));
  CHECK(args.size() == 3u && args[0].is_string() && args[1].is_string() &&
        args[2].is_dict());

  g_qorai_browser_process->ad_block_service()
      ->custom_resource_provider()
      ->UpdateResource(
          Profile::FromWebUI(web_ui())->GetPrefs(), args[1].GetString(),
          args[2],
          base::BindOnce(&QoraiAdBlockHandler::OnScriptletUpdateStatus,
                         weak_factory_.GetWeakPtr(), args[0].GetString()));
}

void QoraiAdBlockHandler::RemoveCustomScriptlet(const base::Value::List& args) {
  CHECK(base::FeatureList::IsEnabled(
      qorai_shields::features::kCosmeticFilteringCustomScriptlets));
  CHECK(args.size() == 2u && args[0].is_string() && args[1].is_string());

  g_qorai_browser_process->ad_block_service()
      ->custom_resource_provider()
      ->RemoveResource(
          Profile::FromWebUI(web_ui())->GetPrefs(), args[1].GetString(),
          base::BindOnce(&QoraiAdBlockHandler::OnScriptletUpdateStatus,
                         weak_factory_.GetWeakPtr(), args[0].GetString()));
}

void QoraiAdBlockHandler::OnScriptletUpdateStatus(
    const std::string& callback_id,
    qorai_shields::AdBlockCustomResourceProvider::ErrorCode error_code) {
  AllowJavascript();
  ResolveJavascriptCallback(callback_id,
                            base::Value(static_cast<int>(error_code)));
}

void QoraiAdBlockHandler::RefreshSubscriptionsList() {
  FireWebUIListener("qorai_adblock.onGetListSubscriptions", GetSubscriptions());
}

void QoraiAdBlockHandler::RefreshCustomFilters() {
  const std::string& custom_filters =
      g_qorai_browser_process->ad_block_service()
          ->custom_filters_provider()
          ->GetCustomFilters();
  FireWebUIListener("qorai_adblock.onCustomFiltersChanged",
                    base::Value(custom_filters));
}

base::Value::List QoraiAdBlockHandler::GetSubscriptions() {
  auto list_subscriptions = g_qorai_browser_process->ad_block_service()
                                ->subscription_service_manager()
                                ->GetSubscriptions();

  base::Value::List list_value;
  base::Time now = base::Time::Now();

  for (const auto& subscription : list_subscriptions) {
    base::Value::Dict dict;

    base::TimeDelta relative_time_delta =
        now - subscription.last_successful_update_attempt;

    auto time_str = ui::TimeFormat::Simple(
        ui::TimeFormat::Format::FORMAT_ELAPSED,
        ui::TimeFormat::Length::LENGTH_LONG, relative_time_delta);

    dict.Set("subscription_url", subscription.subscription_url.spec());
    dict.Set("enabled", subscription.enabled);
    dict.Set("last_update_attempt",
             subscription.last_update_attempt.InMillisecondsFSinceUnixEpoch());
    dict.Set("last_successful_update_attempt",
             subscription.last_successful_update_attempt
                 .InMillisecondsFSinceUnixEpoch());
    dict.Set("last_updated_pretty_text", time_str);
    if (subscription.homepage) {
      dict.Set("homepage", *subscription.homepage);
    }
    if (subscription.title && !subscription.title->empty()) {
      dict.Set("title", *subscription.title);
    } else {
      dict.Set("title", subscription.subscription_url.spec());
    }

    list_value.Append(std::move(dict));
  }

  return list_value;
}

void QoraiAdBlockHandler::OnFilterListsUpdated(std::string callback_id,
                                               bool success) {
  if (!IsJavascriptAllowed()) {
    return;
  }

  if (success) {
    ResolveJavascriptCallback(base::Value(callback_id), base::Value());
  } else {
    RejectJavascriptCallback(base::Value(callback_id), base::Value());
  }
}
