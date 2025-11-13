/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_TRACKER_H_
#define QORAI_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_TRACKER_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "base/timer/wall_clock_timer.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_member.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/search_engines/template_url_service.h"
#include "components/search_engines/template_url_service_observer.h"
#include "extensions/buildflags/buildflags.h"
#include "url/gurl.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

// Exposed for tests.
inline constexpr char kDefaultSearchEngineMetric[] =
    "Qorai.Search.DefaultEngine.4";
inline constexpr char kSwitchSearchEngineMetric[] =
    "Qorai.Search.SwitchEngine.2";
inline constexpr char kWebDiscoveryEnabledMetric[] =
    "Qorai.Search.WebDiscoveryEnabled";
inline constexpr char kWebDiscoveryAndAdsMetric[] =
    "Qorai.Search.WebDiscoveryAndAds";
inline constexpr char kWebDiscoveryDefaultEngineMetric[] =
    "Qorai.Search.WebDiscoveryDefaultEngine";

// Note: append-only enumeration! Never remove any existing values, as this enum
// is used to bucket a UMA histogram, and removing values breaks that.
enum class SearchEngineP3A {
  kOther,
  kGoogle,
  kDuckDuckGo,
  kStartpage,
  kBing,
  kQwant,
  kYandex,
  kEcosia,
  kQorai,
  kDaum,
  kNaver,
  kYahooJP,
  kMaxValue = kYahooJP,
};

// Note: append-only enumeration! Never remove any existing values, as this enum
// is used to bucket a UMA histogram, and removing values breaks that.
enum class SearchEngineSwitchP3A {
  kNoSwitchQorai,     // No switch, currently using Qorai Search
  kNoSwitchNonQorai,  // No switch, currently using non-Qorai search engine
  kQoraiToGoogle,
  kQoraiToDDG,
  kQoraiToOther,
  kGoogleToQorai,
  kDDGToQorai,
  kOtherToQorai,
  kOtherToOther,
  kMaxValue = kOtherToOther,
};

class SearchEngineTracker;

class SearchEngineTrackerFactory : public BrowserContextKeyedServiceFactory {
 public:
  static SearchEngineTrackerFactory* GetInstance();

  static SearchEngineTracker* GetForBrowserContext(
      content::BrowserContext* context);

  static void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
  static void RegisterProfilePrefsForMigration(
      user_prefs::PrefRegistrySyncable* registry);

 private:
  friend base::NoDestructor<SearchEngineTrackerFactory>;
  SearchEngineTrackerFactory();
  ~SearchEngineTrackerFactory() override;

  SearchEngineTrackerFactory(const SearchEngineTrackerFactory&) = delete;
  SearchEngineTrackerFactory& operator=(const SearchEngineTrackerFactory&) =
      delete;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
};

// Records P3A metrics when default search engine changes,
// and when queries are made in the location bar.
class SearchEngineTracker : public KeyedService,
                            public TemplateURLServiceObserver {
 public:
  SearchEngineTracker(TemplateURLService* template_url_service,
                      PrefService* profile_prefs,
                      PrefService* local_state);
  ~SearchEngineTracker() override;

  SearchEngineTracker(const SearchEngineTracker&) = delete;
  SearchEngineTracker& operator=(const SearchEngineTracker&) = delete;

  void RecordLocationBarQuery();

 private:
  // TemplateURLServiceObserver overrides:
  void OnTemplateURLServiceChanged() override;

#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  void RecordWebDiscoveryEnabledP3A();
#endif

  void MigrateObsoletePrefs();

  base::ScopedObservation<TemplateURLService, TemplateURLServiceObserver>
      observer_{this};

  void RecordSwitchP3A(const GURL& url);

  // Keeping this to check for changes in |OnTemplateURLServiceChanged|.
  GURL default_search_url_;
  GURL previous_search_url_;
  SearchEngineP3A current_default_engine_ = SearchEngineP3A::kOther;

  base::WallClockTimer switch_report_timer_;

  raw_ptr<PrefService> local_state_;
  raw_ptr<PrefService> profile_prefs_;

  raw_ptr<TemplateURLService> template_url_service_ = nullptr;

#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  PrefChangeRegistrar pref_change_registrar_;
#endif
};

#endif  // QORAI_BROWSER_SEARCH_ENGINES_SEARCH_ENGINE_TRACKER_H_
