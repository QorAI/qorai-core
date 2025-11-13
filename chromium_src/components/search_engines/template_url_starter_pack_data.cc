/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/search_engines/template_url_starter_pack_data.h"

#include <string_view>

#include "base/strings/strcat.h"
#include "base/strings/string_util.h"
#include "components/grit/qorai_components_strings.h"

#define GetStarterPackEngines GetStarterPackEngines_ChromiumImpl
#define GetDataVersion GetDataVersion_ChromiumImpl
#define GetDestinationUrlForStarterPackId \
  GetDestinationUrlForStarterPackId_ChromiumIml

#include <components/search_engines/template_url_starter_pack_data.cc>

#undef GetDestinationUrlForStarterPackId
#undef GetDataVersion
#undef GetStarterPackEngines

namespace {

constexpr char kChromeSchema[] = "chrome://";
constexpr char kQoraiSchema[] = "qorai://";

}  // namespace

namespace template_url_starter_pack_data {

// Update this whenever a change is made to any Qorai-defined starter pack data.
const int kCurrentQoraiDataVersion = 1;

const StarterPackEngine ask_qorai_search = {
    .name_message_id = IDS_SEARCH_ENGINES_STARTER_PACK_ASK_QORAI_SEARCH_NAME,
    .keyword_message_id =
        IDS_SEARCH_ENGINES_STARTER_PACK_ASK_QORAI_SEARCH_KEYWORD,
    .favicon_url = nullptr,
    .search_url = "https://search.qorai.com/ask?q={searchTerms}",
    .destination_url = "https://search.qorai.com",
    .id = StarterPackId::kAskQoraiSearch,
    .type = SEARCH_ENGINE_STARTER_PACK_ASK_QORAI_SEARCH,
};

const StarterPackEngine* qorai_engines[] = {&bookmarks, &history, &tabs,
                                            &ask_qorai_search};

int GetDataVersion() {
  return GetDataVersion_ChromiumImpl() + kCurrentQoraiDataVersion;
}

std::vector<std::unique_ptr<TemplateURLData>> GetStarterPackEngines() {
  std::vector<std::unique_ptr<TemplateURLData>> t_urls;
  for (auto* engine : qorai_engines) {
    auto t_url = TemplateURLDataFromStarterPackEngine(*engine);

    // Replace the "chrome:" scheme in any upstream starter packs.
    std::string_view url(t_url->url());
    if (base::StartsWith(url, kChromeSchema,
                         base::CompareCase::INSENSITIVE_ASCII)) {
      t_url->SetURL(base::StrCat(
          {kQoraiSchema, url.substr(std::size(kChromeSchema) - 1)}));
    }

    t_urls.push_back(std::move(t_url));
  }
  return t_urls;
}

std::u16string GetDestinationUrlForStarterPackId(int id) {
  if (id == StarterPackId::kAskQoraiSearch) {
    return base::UTF8ToUTF16(ask_qorai_search.destination_url);
  }
  return GetDestinationUrlForStarterPackId_ChromiumIml(id);
}

}  // namespace template_url_starter_pack_data
