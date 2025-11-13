/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_clear_browsing_data_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_import_data_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_search_engines_handler.h"
#include "qorai/browser/ui/webui/settings/qorai_site_settings_handler.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "chrome/browser/regional_capabilities/regional_capabilities_service_factory.h"
#include "chrome/browser/ui/webui/settings/hats_handler.h"
#include "chrome/browser/ui/webui/settings/settings_secure_dns_handler.h"
#include "chrome/browser/ui/webui/settings/site_settings_handler.h"

#if BUILDFLAG(IS_WIN) && BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/ui/webui/settings/qorai_settings_secure_dns_handler.h"

#define SecureDnsHandler QoraiSecureDnsHandler
#endif  // BUILDFLAG(IS_WIN) && BUILDFLAG(ENABLE_QORAI_VPN)

#define SiteSettingsHandler QoraiSiteSettingsHandler
#define ImportDataHandler QoraiImportDataHandler
#define SearchEnginesHandler QoraiSearchEnginesHandler>(profile, regional_capabilities::RegionalCapabilitiesServiceFactory::GetForProfile(profile))); \
  if (false) AddSettingsPageUIHandler(std::make_unique<SearchEnginesHandler

#define ClearBrowsingDataHandler QoraiClearBrowsingDataHandler
#include <chrome/browser/ui/webui/settings/settings_ui.cc>
#undef ClearBrowsingDataHandler
#undef SearchEnginesHandler
#undef ImportDataHandler
#undef SiteSettingsHandler
#if BUILDFLAG(IS_WIN) && BUILDFLAG(ENABLE_QORAI_VPN)
#undef SecureDnsHandler
#endif  // BUILDFLAG(IS_WIN) && BUILDFLAG(ENABLE_QORAI_VPN)
