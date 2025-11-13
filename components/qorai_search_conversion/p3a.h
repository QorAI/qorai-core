// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_P3A_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_P3A_H_

#include "qorai/components/qorai_search_conversion/types.h"

class PrefRegistrySimple;
class PrefService;

namespace qorai_search_conversion {
namespace p3a {

inline constexpr char kSearchPromoButtonHistogramName[] =
    "Qorai.Search.Promo.Button";
inline constexpr char kSearchPromoBannerBHistogramName[] =
    "Qorai.Search.Promo.BannerB";
inline constexpr char kSearchPromoBannerCHistogramName[] =
    "Qorai.Search.Promo.BannerC";
inline constexpr char kSearchPromoBannerDHistogramName[] =
    "Qorai.Search.Promo.BannerD";
inline constexpr char kSearchPromoDDGBannerCHistogramName[] =
    "Qorai.Search.Promo.DDGBannerC";
inline constexpr char kSearchPromoDDGBannerDHistogramName[] =
    "Qorai.Search.Promo.DDGBannerD";

inline constexpr char kSearchPromoNTPHistogramName[] =
    "Qorai.Search.Promo.NewTabPage";
inline constexpr char kSearchQueriesBeforeChurnHistogramName[] =
    "Qorai.Search.QueriesBeforeChurn";

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteLocalStatePrefs(PrefService* local_state);

void RecordPromoShown(PrefService* prefs, ConversionType type);
void RecordPromoTrigger(PrefService* prefs, ConversionType type);

void RecordLocationBarQuery(PrefService* prefs);
void RecordDefaultEngineConversion(PrefService* prefs);
void RecordDefaultEngineChurn(PrefService* prefs);

}  // namespace p3a
}  // namespace qorai_search_conversion

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_P3A_H_
