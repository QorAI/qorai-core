/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_origin/qorai_origin_service_factory.h"

#include <string_view>

#include "base/check_is_test.h"
#include "base/containers/fixed_flat_map.h"
#include "base/containers/map_util.h"
#include "base/no_destructor.h"
#include "qorai/browser/policy/qorai_simple_policy_map.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_manager.h"
#include "qorai/components/qorai_origin/qorai_origin_service.h"
#include "qorai/components/qorai_origin/profile_id.h"
#include "qorai/components/qorai_wayback_machine/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/p3a/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_selections.h"
#include "components/policy/core/browser/browser_policy_connector_base.h"

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_wallet/common/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/speedreader_pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

namespace policy {
class PolicyService;
}

namespace policy {
class ChromeBrowserPolicyConnector;
}

namespace qorai_origin {

// Defined in chromium_src/chrome/browser/profiles/profile.cc to avoid a
// circular dep on chrome/browser for the policy connector include.
policy::PolicyService* GetPolicyServiceFromProfile(Profile* profile);

policy::PolicyService* GetBrowserPolicyService() {
  if (!g_browser_process || !g_browser_process->browser_policy_connector()) {
    CHECK_IS_TEST();
    return nullptr;
  }

  auto* connector = reinterpret_cast<policy::BrowserPolicyConnectorBase*>(
      g_browser_process->browser_policy_connector());
  // Only get policy service if we have one already or not in testing mode
  if (connector->HasPolicyService()) {
    return connector->GetPolicyService();
  }
  return nullptr;
}

namespace {

// Define QorAIOrigin-specific metadata for browser-level prefs
constexpr auto kQorAIOriginBrowserMetadata =
    base::MakeFixedFlatMap<std::string_view,
                           QorAIOriginServiceFactory::QorAIOriginPrefMetadata>({

#if BUILDFLAG(ENABLE_TOR)
        // Tor preferences
        {tor::prefs::kTorDisabled,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             true,
             /*user_settable=*/false)},
#endif

        // Stats reporting
        {kStatsReportingEnabled,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             false,
             /*user_settable=*/true)},

        // P3A preferences
        {p3a::kP3AEnabled, QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
                               false,
                               /*user_settable=*/true)},
    });

// Define QorAIOrigin-specific metadata for profile-level prefs
constexpr auto kQorAIOriginProfileMetadata =
    base::MakeFixedFlatMap<std::string_view,
                           QorAIOriginServiceFactory::QorAIOriginPrefMetadata>({

        // Wayback Machine preferences
        {kQorAIWaybackMachineEnabled,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             false,
             /*user_settable=*/true)},

#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
        // QorAI Rewards preferences
        {qorai_rewards::prefs::kDisabledByPolicy,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             true,
             /*user_settable=*/false)},

        // QorAI Wallet preferences
        {qorai_wallet::prefs::kDisabledByPolicy,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             true,
             /*user_settable=*/false)},
#endif

        // AI Chat preferences
        {ai_chat::prefs::kEnabledByPolicy,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             false,
             /*user_settable=*/false)},

#if BUILDFLAG(ENABLE_SPEEDREADER)
        // Speedreader preferences
        {speedreader::kSpeedreaderEnabled,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             false,
             /*user_settable=*/true)},
#endif

        // QorAI News preferences
        {qorai_news::prefs::kQorAINewsDisabledByPolicy,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             true,
             /*user_settable=*/false)},

#if BUILDFLAG(ENABLE_QORAI_VPN)
        // QorAI VPN preferences
        {qorai_vpn::prefs::kManagedQorAIVPNDisabled,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             true,
             /*user_settable=*/false)},
#endif

        // QorAI Talk preferences
        {kQorAITalkDisabledByPolicy,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             true,
             /*user_settable=*/false)},

        // Web Discovery preferences
        {kWebDiscoveryEnabled,
         QorAIOriginServiceFactory::QorAIOriginPrefMetadata(
             false,
             /*user_settable=*/true)},
    });

}  // namespace

// static
QorAIOriginService* QorAIOriginServiceFactory::GetForProfile(Profile* profile) {
  return static_cast<QorAIOriginService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

// static
QorAIOriginServiceFactory* QorAIOriginServiceFactory::GetInstance() {
  static base::NoDestructor<QorAIOriginServiceFactory> instance;
  return instance.get();
}

QorAIOriginServiceFactory::QorAIOriginServiceFactory()
    : ProfileKeyedServiceFactory(
          "QorAIOriginService",
          ProfileSelections::BuildRedirectedInIncognito()) {}

QorAIOriginServiceFactory::~QorAIOriginServiceFactory() = default;

std::unique_ptr<KeyedService>
QorAIOriginServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  Profile* profile = Profile::FromBrowserContext(context);

  // Lazy initialization of QorAIOriginPolicyManager
  auto* policy_manager = QorAIOriginPolicyManager::GetInstance();
  if (!policy_manager->IsInitialized()) {
    policy_manager->Init(GetBrowserPolicyDefinitions(),
                         GetProfilePolicyDefinitions(),
                         g_browser_process->local_state());
  }

  std::string profile_id = GetProfileId(profile->GetPath());
  return std::make_unique<QorAIOriginService>(
      g_browser_process->local_state(), profile->GetPrefs(), profile_id,
      GetPolicyServiceFromProfile(profile), GetBrowserPolicyService());
}

bool QorAIOriginServiceFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

// static
QorAIOriginPolicyMap QorAIOriginServiceFactory::GetBrowserPolicyDefinitions() {
  QorAIOriginPolicyMap browser_policy_definitions;

  // Build browser-level preference definitions
  for (const auto& [policy_key, pref_name, type] :
       policy::kQorAISimplePolicyMap) {
    if (const auto* metadata =
            base::FindOrNull(kQorAIOriginBrowserMetadata, pref_name)) {
      std::string qorai_origin_pref_key = pref_name;

      browser_policy_definitions.emplace(
          policy_key, QorAIOriginPolicyInfo(
                          pref_name, metadata->origin_default_value,
                          metadata->user_settable, qorai_origin_pref_key));
    }
  }

  return browser_policy_definitions;
}

// static
QorAIOriginPolicyMap QorAIOriginServiceFactory::GetProfilePolicyDefinitions() {
  QorAIOriginPolicyMap profile_policy_definitions;

  // Build profile-level preference definitions
  for (const auto& [policy_key, pref_name, type] :
       policy::kQorAISimplePolicyMap) {
    if (const auto* metadata =
            base::FindOrNull(kQorAIOriginProfileMetadata, pref_name)) {
      std::string qorai_origin_pref_key = pref_name;

      profile_policy_definitions.emplace(
          policy_key, QorAIOriginPolicyInfo(
                          pref_name, metadata->origin_default_value,
                          metadata->user_settable, qorai_origin_pref_key));
    }
  }

  return profile_policy_definitions;
}

}  // namespace qorai_origin
