/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_region_data_manager.h"

#include <algorithm>
#include <optional>
#include <utility>

#include "base/check.h"
#include "base/check_is_test.h"
#include "base/functional/bind.h"
#include "base/functional/callback_forward.h"
#include "base/json/json_reader.h"
#include "base/logging.h"
#include "base/notreached.h"
#include "qorai/components/qorai_vpn/browser/api/qorai_vpn_api_helper.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_region_data_helper.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_constants.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace qorai_vpn {
QoraiVPNRegionDataManager::QoraiVPNRegionDataManager(
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    PrefService* local_prefs)
    : url_loader_factory_(url_loader_factory), local_prefs_(local_prefs) {
  LoadCachedRegionData();
}

QoraiVPNRegionDataManager::~QoraiVPNRegionDataManager() = default;

const std::vector<mojom::RegionPtr>& QoraiVPNRegionDataManager::GetRegions()
    const {
  return regions_;
}

bool QoraiVPNRegionDataManager::IsRegionDataReady() const {
  return !regions_.empty();
}

void QoraiVPNRegionDataManager::SetSelectedRegion(std::string_view name) {
  local_prefs_->SetString(prefs::kQoraiVPNSelectedRegionV2, name);

  if (selected_region_changed_callback_) {
    selected_region_changed_callback_.Run(GetSelectedRegion());
  }
}

std::string QoraiVPNRegionDataManager::GetSelectedRegion() const {
  if (regions_.empty()) {
    CHECK_IS_TEST();
  }

  auto region_name = local_prefs_->GetString(prefs::kQoraiVPNSelectedRegionV2);
  if (region_name.empty()) {
    // Gives device region if there is no cached selected region.
    VLOG(2) << __func__ << " : give device region instead.";
    region_name = GetDeviceRegion();
  }

  DCHECK(!region_name.empty());
  return region_name;
}

std::string QoraiVPNRegionDataManager::GetDeviceRegion() const {
  return local_prefs_->GetString(prefs::kQoraiVPNDeviceRegion);
}

void QoraiVPNRegionDataManager::SetDeviceRegion(std::string_view name) {
  local_prefs_->SetString(prefs::kQoraiVPNDeviceRegion, name);
}

std::string QoraiVPNRegionDataManager::GetRegionPrecisionForName(
    const std::string& name) const {
  for (const auto& region : regions_) {
    if (region->name == name) {
      return qorai_vpn::mojom::kRegionPrecisionCountry;
    } else {
      for (const auto& city : region->cities) {
        if (city->name == name) {
          return qorai_vpn::mojom::kRegionPrecisionCity;
        }
      }
    }
  }
  NOTREACHED();
}

void QoraiVPNRegionDataManager::SetFallbackDeviceRegion() {
  // Set first item in the region list as a |device_region_| as a fallback.
  DCHECK(!regions_.empty());
  SetDeviceRegion(regions_[0]->name);
}

void QoraiVPNRegionDataManager::SetDeviceRegionWithTimezone(
    const base::Value::List& timezones_value) {
  const std::string current_time_zone = GetCurrentTimeZone();
  if (current_time_zone.empty()) {
    return;
  }

  for (const auto& timezones : timezones_value) {
    DCHECK(timezones.is_dict());
    if (!timezones.is_dict()) {
      continue;
    }

    const auto* timezone_list_value = timezones.GetDict().FindList("timezones");
    if (!timezone_list_value) {
      continue;
    }

    for (const auto& timezone : *timezone_list_value) {
      DCHECK(timezone.is_string());
      if (!timezone.is_string()) {
        continue;
      }
      if (current_time_zone == timezone.GetString()) {
        const std::string* country_iso =
            timezones.GetDict().FindString(kRegionCountryIsoCodeKey);
        // Get region name of |country_iso| from region list.
        const std::string new_name = GetCountryRegionNameFrom(*country_iso);
        SetDeviceRegion(new_name);
        // Use device region as a default selected region.
        if (local_prefs_->GetString(prefs::kQoraiVPNSelectedRegionV2).empty()) {
          SetSelectedRegion(new_name);
        }
        return;
      }
    }
  }
}

std::string QoraiVPNRegionDataManager::GetCountryRegionNameFrom(
    const std::string& country_iso) const {
  CHECK(!regions_.empty());
  for (const auto& region : regions_) {
    if (region->country_iso_code == country_iso) {
      return region->name;
    }
  }

  // Fallback to first region item.
  return regions_[0]->name;
}

void QoraiVPNRegionDataManager::LoadCachedRegionData() {
  // Already loaded from cache.
  if (!regions_.empty()) {
    return;
  }

  // Empty device region means it's initial state.
  if (GetDeviceRegion().empty()) {
    return;
  }

  auto* preference = local_prefs_->FindPreference(prefs::kQoraiVPNRegionList);
  DCHECK(preference);
  // Early return when we don't have any cached region data.
  if (preference->IsDefaultValue()) {
    return;
  }

  // If cached one is outdated, don't use it.
  if (!ValidateCachedRegionData(preference->GetValue()->GetList())) {
    VLOG(2) << __func__ << " : Cached data is outdate. Will get fetch latest.";
    return;
  }

  if (ParseAndCacheRegionList(preference->GetValue()->GetList())) {
    VLOG(2) << __func__ << " : Loaded cached region list";
    return;
  }

  VLOG(2) << __func__ << " : Failed to load cached region list";
}

bool QoraiVPNRegionDataManager::NeedToUpdateRegionData() const {
  if (!IsRegionDataReady()) {
    return true;
  }

  // Skip checking region data update when we have cached one and its age is
  // younger than 5h.
  const auto last_fetched_date =
      local_prefs_->GetTime(prefs::kQoraiVPNRegionListFetchedDate);
  constexpr int kRegionDataFetchIntervalInHours = 5;

  if (last_fetched_date.is_null() ||
      (base::Time::Now() - last_fetched_date).InHours() >=
          kRegionDataFetchIntervalInHours) {
    return true;
  }

  return false;
}

void QoraiVPNRegionDataManager::NotifyRegionDataReady() const {
  if (region_data_ready_callback_) {
    region_data_ready_callback_.Run(!regions_.empty());
  }
}

void QoraiVPNRegionDataManager::FetchRegionDataIfNeeded() {
  if (api_request_) {
    VLOG(2) << __func__ << " : Region data fetching is in-progress";
    return;
  }

  if (!NeedToUpdateRegionData()) {
    VLOG(2)
        << __func__
        << " : Don't need to check as it's not passed 5h since the last check.";
    NotifyRegionDataReady();
    return;
  }
  FetchRegions();
}

void QoraiVPNRegionDataManager::FetchRegions() {
  api_request_ = std::make_unique<QoraiVpnAPIRequest>(url_loader_factory_);
  VLOG(2) << __func__ << " : Start fetching region data";
  // Unretained is safe here becasue this class owns |api_request_|.
  api_request_->GetServerRegions(
      base::BindOnce(&QoraiVPNRegionDataManager::OnFetchRegionList,
                     base::Unretained(this)),
      mojom::kRegionPrecisionCityByCountry);
}

void QoraiVPNRegionDataManager::OnFetchRegionList(
    const std::string& region_list,
    bool success) {
  if (!api_request_) {
    CHECK_IS_TEST();
  }
  api_request_.reset();
  std::optional<base::Value::List> value = base::JSONReader::ReadList(
      region_list, base::JSON_PARSE_CHROMIUM_EXTENSIONS);
  if (value && ParseAndCacheRegionList(*value, true)) {
    VLOG(2) << "Got valid region list";
    // Set default device region and it'll be updated when received valid
    // timezone info.
    SetFallbackDeviceRegion();
    // Fetch timezones list to determine default region of this device.
    api_request_ = std::make_unique<QoraiVpnAPIRequest>(url_loader_factory_);
    api_request_->GetTimezonesForRegions(base::BindOnce(
        &QoraiVPNRegionDataManager::OnFetchTimezones, base::Unretained(this)));
    return;
  }

  VLOG(2) << "Got invalid region list";
  NotifyRegionDataReady();
}

bool QoraiVPNRegionDataManager::ParseAndCacheRegionList(
    const base::Value::List& region_value,
    bool save_to_prefs) {
  auto new_regions = ParseRegionList(region_value);
  VLOG(2) << __func__ << " : has regionlist: " << !new_regions.empty();

  // To avoid deleting current valid |regions_|, only assign when
  // |new_regions| is not empty.
  if (new_regions.empty()) {
    return false;
  }

  regions_ = std::move(new_regions);

  if (save_to_prefs) {
    SetRegionListToPrefs();
  }
  return true;
}

void QoraiVPNRegionDataManager::OnFetchTimezones(
    const std::string& timezones_list,
    bool success) {
  api_request_.reset();

  if (success) {
    std::optional<base::Value::List> value = base::JSONReader::ReadList(
        timezones_list, base::JSON_PARSE_CHROMIUM_EXTENSIONS);
    success = value.has_value();
    if (success) {
      SetDeviceRegionWithTimezone(*value);
      VLOG(2) << "Got valid timezones list";
    }
  }

  if (!success) {
    VLOG(2) << "Failed to get invalid timezones list";
  }

  // Can notify as ready now regardless of timezone fetching result.
  // We use default one picked from region list as a device region on failure.
  NotifyRegionDataReady();
}

void QoraiVPNRegionDataManager::SetRegionListToPrefs() {
  DCHECK(!regions_.empty());

  base::Value::List regions_list;
  for (const auto& region : regions_) {
    regions_list.Append(GetValueFromRegion(region));
  }

  local_prefs_->Set(prefs::kQoraiVPNRegionList,
                    base::Value(std::move(regions_list)));
  local_prefs_->SetTime(prefs::kQoraiVPNRegionListFetchedDate,
                        base::Time::Now());
}

std::string QoraiVPNRegionDataManager::GetCurrentTimeZone() {
  if (!test_timezone_.empty()) {
    return test_timezone_;
  }

  return GetTimeZoneName();
}

}  // namespace qorai_vpn
