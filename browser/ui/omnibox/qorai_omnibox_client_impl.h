/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_OMNIBOX_QORAI_OMNIBOX_CLIENT_IMPL_H_
#define QORAI_BROWSER_UI_OMNIBOX_QORAI_OMNIBOX_CLIENT_IMPL_H_

#include "base/memory/raw_ptr.h"
#include "qorai/browser/autocomplete/qorai_autocomplete_scheme_classifier.h"
#include "qorai/components/time_period_storage/weekly_storage.h"
#include "chrome/browser/ui/omnibox/chrome_omnibox_client.h"
#include "components/prefs/pref_change_registrar.h"

class PrefRegistrySimple;
class Profile;
class SearchEngineTracker;

namespace ai_chat {
class AIChatMetrics;
}  // namespace ai_chat

class QoraiOmniboxClientImpl : public ChromeOmniboxClient {
 public:
  QoraiOmniboxClientImpl(LocationBar* location_bar,
                         Browser* browser,
                         Profile* profile);
  QoraiOmniboxClientImpl(const QoraiOmniboxClientImpl&) = delete;
  QoraiOmniboxClientImpl& operator=(const QoraiOmniboxClientImpl&) = delete;
  ~QoraiOmniboxClientImpl() override;

  static void RegisterProfilePrefs(PrefRegistrySimple* prefs);

  const AutocompleteSchemeClassifier& GetSchemeClassifier() const override;

  void OnURLOpenedFromOmnibox(OmniboxLog* log) override;

  void OnAutocompleteAccept(
      const GURL& destination_url,
      TemplateURLRef::PostContent* post_content,
      WindowOpenDisposition disposition,
      ui::PageTransition transition,
      AutocompleteMatchType::Type match_type,
      base::TimeTicks match_selection_timestamp,
      bool destination_url_entered_without_scheme,
      bool destination_url_entered_with_http_scheme,
      const std::u16string& text,
      const AutocompleteMatch& match,
      const AutocompleteMatch& alternative_nav_match) override;

 private:
  void RecordSearchEventP3A();

  raw_ptr<Profile> profile_ = nullptr;
  raw_ptr<SearchEngineTracker> search_engine_tracker_ = nullptr;
  raw_ptr<ai_chat::AIChatMetrics> ai_chat_metrics_ = nullptr;
  QoraiAutocompleteSchemeClassifier scheme_classifier_;
  WeeklyStorage search_storage_;
  PrefChangeRegistrar pref_change_registrar_;
};

#endif  // QORAI_BROWSER_UI_OMNIBOX_QORAI_OMNIBOX_CLIENT_IMPL_H_
