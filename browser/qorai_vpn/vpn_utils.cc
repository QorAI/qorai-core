/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/vpn_utils.h"

#include "base/functional/bind.h"
#include "base/notreached.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_connection_manager.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "build/build_config.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/channel_info.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

#if BUILDFLAG(IS_WIN)
#include "qorai/browser/qorai_vpn/win/vpn_utils_win.h"
#include "qorai/browser/qorai_vpn/win/wireguard_connection_api_impl_win.h"
#include "qorai/components/qorai_vpn/browser/connection/ikev2/win/ras_connection_api_impl_win.h"
#endif

#if BUILDFLAG(IS_MAC)
#include "qorai/browser/qorai_vpn/mac/vpn_utils_mac.h"
#endif

namespace qorai_vpn {

namespace {

#if !BUILDFLAG(IS_ANDROID)
std::unique_ptr<ConnectionAPIImpl> CreateConnectionAPIImpl(
    QorAIVPNConnectionManager* manager,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    bool wireguard_enabled) {
#if BUILDFLAG(IS_MAC)
  return CreateConnectionAPIImplMac(manager, url_loader_factory);
#endif

#if BUILDFLAG(IS_WIN)
  if (wireguard_enabled) {
    return std::make_unique<WireguardConnectionAPIImplWin>(manager,
                                                           url_loader_factory);
  }
  return std::make_unique<RasConnectionAPIImplWin>(manager, url_loader_factory);
#endif

  // VPN is not supported on other platforms.
  NOTREACHED();
}
#endif

}  // namespace

std::unique_ptr<QorAIVPNConnectionManager> CreateQorAIVPNConnectionManager(
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    PrefService* local_prefs) {
#if BUILDFLAG(IS_ANDROID)
  // Android doesn't use connection api.
  return nullptr;
#else
  // Currently, service installer only used on Windows.
  // Installs registers IKEv2 service (for DNS) and our WireGuard impl.
  // NOTE: Install only happens if person has purchased the product.
  auto service_installer =
#if BUILDFLAG(IS_WIN)
      base::BindRepeating(&qorai_vpn::InstallVpnSystemServices);
#else
      base::NullCallback();
#endif

  auto manager = std::make_unique<QorAIVPNConnectionManager>(
      url_loader_factory, local_prefs, service_installer);
  manager->set_target_vpn_entry_name(
      qorai_vpn::GetQorAIVPNEntryName(chrome::GetChannel()));
  manager->set_connection_api_impl_getter(
      base::BindRepeating(&CreateConnectionAPIImpl));
  manager->UpdateConnectionAPIImpl();
  return manager;
#endif
}

bool IsAllowedForContext(content::BrowserContext* context) {
  return Profile::FromBrowserContext(context)->IsRegularProfile() &&
         qorai_vpn::IsQorAIVPNFeatureEnabled();
}

bool IsQorAIVPNEnabled(content::BrowserContext* context) {
  // TODO(simonhong): Can we use this check for android?
  // For now, vpn is disabled by default on desktop but not sure on
  // android.
#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
  return qorai_vpn::IsQorAIVPNEnabled(user_prefs::UserPrefs::Get(context)) &&
         IsAllowedForContext(context);
#else
  return Profile::FromBrowserContext(context)->IsRegularProfile();
#endif
}

}  // namespace qorai_vpn
