/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_ads/core/internal/common/subdivision/subdivision_observer.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace qorai_ads {

class SubdivisionTargeting final : public AdsClientNotifierObserver,
                                   public SubdivisionObserver {
 public:
  SubdivisionTargeting();

  SubdivisionTargeting(const SubdivisionTargeting&) = delete;
  SubdivisionTargeting& operator=(const SubdivisionTargeting&) = delete;

  ~SubdivisionTargeting() override;

  bool IsDisabled() const;

  bool ShouldAutoDetect() const;

  static bool ShouldAllow();

  const std::string& GetSubdivision() const;

 private:
  void MaybeInitialize();

  void MaybeRequireSubdivision();

  void DisableSubdivision();

  void AutoDetectSubdivision();

  void MaybeAllowForCountry(const std::string& country_code);

  bool ShouldFetchSubdivision();
  void MaybeFetchSubdivision();

  void MaybeAllowAndFetchSubdivisionForLocale(const std::string& locale);

  void SetAutoDetectedSubdivision(const std::string& subdivision);
  void UpdateAutoDetectedSubdivision();
  const std::string& GetLazyAutoDetectedSubdivision() const;

  void SetUserSelectedSubdivision(const std::string& subdivision);
  void UpdateUserSelectedSubdivision();
  const std::string& GetLazyUserSelectedSubdivision() const;

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyPrefDidChange(const std::string& path) override;

  // SubdivisionObserver:
  void OnDidUpdateSubdivision(const std::string& subdivision) override;

  mutable std::optional<std::string> auto_detected_subdivision_;
  mutable std::optional<std::string> user_selected_subdivision_;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_H_
