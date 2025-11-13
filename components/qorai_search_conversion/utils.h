/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_UTILS_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_UTILS_H_

#include <string>

class GURL;
class PrefRegistrySimple;
class PrefService;
class TemplateURLService;

namespace qorai_search_conversion {

enum class ConversionType;

bool IsNTPPromotionEnabled(PrefService* prefs, TemplateURLService* service);

// Promotion type from omnibox.
ConversionType GetConversionType(PrefService* prefs,
                                 TemplateURLService* service);
void RegisterPrefs(PrefRegistrySimple* registry);
void SetDismissed(PrefService* prefs);
void SetMaybeLater(PrefService* prefs);
GURL GetPromoURL(const std::u16string& search_term);
GURL GetPromoURL(const std::string& search_term);

// True when omnibox conversion features are enabled.
bool IsQoraiSearchConversionFeatureEnabled();

}  // namespace qorai_search_conversion

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_UTILS_H_
