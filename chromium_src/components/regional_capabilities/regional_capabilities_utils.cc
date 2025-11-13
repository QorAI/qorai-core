/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/regional_capabilities/regional_capabilities_utils.h"

#include "base/check.h"
#include "base/check_op.h"
#include "base/containers/fixed_flat_map.h"
#include "base/containers/flat_map.h"
#include "base/containers/map_util.h"
#include "base/containers/span.h"
#include "qorai/components/search_engines/qorai_prepopulated_engines.h"
#include "components/prefs/pref_service.h"
#include "components/search_engines/search_engines_pref_names.h"

// Use Qorai's lists of per-country engines.
#define GetPrepopulatedEngines GetPrepopulatedEngines_UnUsed
#include <components/regional_capabilities/regional_capabilities_utils.cc>
#undef GetPrepopulatedEngines

namespace regional_capabilities {

namespace {

// ****************************************************************************
// IMPORTANT! If you make changes to any of the search engine mappings below,
// it's critical to also increment the value `kQoraiCurrentDataVersion` in
// `qorai/components/search_engines/qorai_prepopulated_engines.h`.
// ****************************************************************************

// Default order in which engines will appear in the UI.
// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesDefault[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// Variations of the order / default options by country.
// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesWithEcosia[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_ECOSIA,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesWithYandex[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesDE[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_ECOSIA,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesFR[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_ECOSIA,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesAUIE[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_ECOSIA,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesJP[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YAHOO_JP,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesKR[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_NAVER,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DAUM,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// LINT.IfChange
constexpr TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
    kQoraiEnginesNZ[] = {
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BING,
        TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_STARTPAGE,
};
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// A map to keep track of a full list of default engines for countries
// that don't use the default list.
// LINT.IfChange
constexpr auto kDefaultEnginesByCountryIdMap = base::MakeFixedFlatMap<
    country_codes::CountryId,
    base::span<const TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>>(
    {{country_codes::CountryId("AM"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("AT"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("AU"), kQoraiEnginesAUIE},
     {country_codes::CountryId("AZ"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("BE"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("BY"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("CA"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("CH"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("DE"), kQoraiEnginesDE},
     {country_codes::CountryId("DK"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("ES"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("FI"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("FR"), kQoraiEnginesFR},
     {country_codes::CountryId("GB"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("GR"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("HU"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("IE"), kQoraiEnginesAUIE},
     {country_codes::CountryId("IT"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("JP"), kQoraiEnginesJP},
     {country_codes::CountryId("KG"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("KR"), kQoraiEnginesKR},
     {country_codes::CountryId("KZ"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("LU"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("MD"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("NL"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("NO"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("NZ"), kQoraiEnginesNZ},
     {country_codes::CountryId("PT"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("RU"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("SE"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("TJ"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("TM"), kQoraiEnginesWithYandex},
     {country_codes::CountryId("US"), kQoraiEnginesWithEcosia},
     {country_codes::CountryId("UZ"), kQoraiEnginesWithYandex}});
// LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

// Builds a vector of PrepulatedEngine objects from the given array of
// |engine_ids|.
std::vector<const PrepopulatedEngine*> GetEnginesFromEngineIDs(
    base::span<const TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>
        engine_ids) {
  std::vector<const PrepopulatedEngine*> engines;
  for (TemplateURLPrepopulateData::QoraiPrepopulatedEngineID engine_id :
       engine_ids) {
    const PrepopulatedEngine* engine = base::FindPtrOrNull(
        TemplateURLPrepopulateData::kQoraiEngines, engine_id);
    CHECK(engine);
    engines.push_back(engine);
  }
  return engines;
}

// Uses qorai_engines_XX localized arrays of engine IDs instead of Chromium's
// localized arrays of PrepopulatedEngines to construct the vector of
// TemplateURLData.
std::vector<const PrepopulatedEngine*> GetQoraiPrepopulatedEnginesForCountryID(
    country_codes::CountryId country_id) {
  base::span<const TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>
      qorai_engine_ids = kQoraiEnginesDefault;

  // Check for a per-country override of this list
  const auto* country_engines =
      base::FindOrNull(kDefaultEnginesByCountryIdMap, country_id);
  if (country_engines) {
    qorai_engine_ids = *country_engines;
  }
  DCHECK_GT(qorai_engine_ids.size(), 0ul);

  // Build a vector PrepopulatedEngines from
  // TemplateURLPrepopulateData::QoraiPrepopulatedEngineIDs.
  std::vector<const PrepopulatedEngine*> engines =
      GetEnginesFromEngineIDs(qorai_engine_ids);
  DCHECK(engines.size() == qorai_engine_ids.size());

  return engines;
}

// A versioned map tracking the singular default search engine per-country.
//
// When a profile is created, the current value for `kQoraiCurrentDataVersion`
// in `//qorai/components/search_engines/qorai_prepopulated_engines.h`
// is stored as a profile preference.
//
// See:
// - `SetDefaultSearchVersion` in `//qorai/browser/profiles/profile_util.cc`
// - `//qorai/browser/profiles/qorai_profile_manager.cc` where it is called
//
// If that person resets the profile using qorai://settings/reset, we need to
// set the default search engine back to what it was when the profile was
// originally created. This way, a person doesn't get a new unexpected default
// when they reset the profile; it goes back to the original value.
TemplateURLPrepopulateData::QoraiPrepopulatedEngineID GetDefaultSearchEngine(
    country_codes::CountryId country_id,
    int version) {
  // LINT.IfChange
  const TemplateURLPrepopulateData::QoraiPrepopulatedEngineID default_v6 =
      TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_GOOGLE;
  static constexpr auto kContentV6 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT},
      {country_codes::CountryId("IE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
      {country_codes::CountryId("NZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
  });
  static constexpr auto kContentV8 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT},
      {country_codes::CountryId("IE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("NZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  static constexpr auto kContentV16 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  static constexpr auto kContentV17 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });

  static constexpr auto kContentV20 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });

  static constexpr auto kContentV21 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  static constexpr auto kContentV22 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IN"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  static constexpr auto kContentV25 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IN"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_NAVER},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  // Updated default for IT.
  static constexpr auto kContentV26 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IN"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_NAVER},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  // Updated default for AU.
  static constexpr auto kContentV30 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IN"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_NAVER},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });

  // Updated default for JP.
  static constexpr auto kContentV31 = base::MakeFixedFlatMap<
      country_codes::CountryId,
      TemplateURLPrepopulateData::QoraiPrepopulatedEngineID>({
      {country_codes::CountryId("AM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("AR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("AZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("BR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("BY"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("CA"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("DE"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("ES"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("FR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("GB"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IN"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("IT"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("JP"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YAHOO_JP},
      {country_codes::CountryId("KG"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("KR"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_NAVER},
      {country_codes::CountryId("KZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MD"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("MX"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("RU"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TJ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("TM"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
      {country_codes::CountryId("US"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QORAI},
      {country_codes::CountryId("UZ"),
       TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_YANDEX},
  });
  // LINT.ThenChange(//qorai/components/search_engines/qorai_prepopulated_engines.h:kQoraiCurrentDataVersion)

  const TemplateURLPrepopulateData::QoraiPrepopulatedEngineID* content;

  if (version > 30) {
    content = base::FindOrNull(kContentV31, country_id);
  } else if (version > 29) {
    content = base::FindOrNull(kContentV30, country_id);
  } else if (version > 25) {
    content = base::FindOrNull(kContentV26, country_id);
  } else if (version > 24) {
    content = base::FindOrNull(kContentV25, country_id);
  } else if (version > 21) {
    content = base::FindOrNull(kContentV22, country_id);
  } else if (version > 20) {
    content = base::FindOrNull(kContentV21, country_id);
  } else if (version > 19) {
    content = base::FindOrNull(kContentV20, country_id);
  } else if (version > 16) {
    content = base::FindOrNull(kContentV17, country_id);
  } else if (version > 15) {
    content = base::FindOrNull(kContentV16, country_id);
  } else if (version > 7) {
    content = base::FindOrNull(kContentV8, country_id);
  } else {
    content = base::FindOrNull(kContentV6, country_id);
  }

  if (!content) {
    return default_v6;
  }
  return *content;
}

}  // namespace

std::vector<const PrepopulatedEngine*> GetPrepopulatedEngines(
    CountryId country_id,
    PrefService& prefs,
    SearchEngineListType search_engine_list_type) {
  return GetQoraiPrepopulatedEnginesForCountryID(country_id);
}

TemplateURLPrepopulateData::QoraiPrepopulatedEngineID GetDefaultEngine(
    CountryId country_id,
    PrefService& prefs) {
  int version = TemplateURLPrepopulateData::kQoraiCurrentDataVersion;
  if (prefs.HasPrefPath(::prefs::kQoraiDefaultSearchVersion)) {
    version = prefs.GetInteger(::prefs::kQoraiDefaultSearchVersion);
  }

  return GetDefaultSearchEngine(country_id, version);
}

}  // namespace regional_capabilities
