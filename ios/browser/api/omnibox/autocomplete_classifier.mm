// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/api/omnibox/autocomplete_classifier.h"

#include "base/notreached.h"
#include "base/strings/sys_string_conversions.h"
#include "components/omnibox/browser/autocomplete_classifier.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/prefs/pref_service.h"
#include "ios/chrome/browser/autocomplete/model/autocomplete_classifier_factory.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/prefs/pref_names.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/chrome/browser/shared/model/profile/profile_manager_ios.h"
#include "net/base/apple/url_conversions.h"

namespace qorai {
AutocompleteMatch::Type MatchTypeFromQoraiType(
    QoraiIOSAutocompleteMatchType type) {
  switch (type) {
    case QoraiIOSAutocompleteMatchTypeUrlWhatYouTyped:
      return AutocompleteMatch::Type::URL_WHAT_YOU_TYPED;
    case QoraiIOSAutocompleteMatchTypeHistoryUrl:
      return AutocompleteMatch::Type::HISTORY_URL;
    case QoraiIOSAutocompleteMatchTypeNavSuggest:
      return AutocompleteMatch::Type::NAVSUGGEST;
    case QoraiIOSAutocompleteMatchTypeSearchWhatYouTyped:
      return AutocompleteMatch::Type::SEARCH_WHAT_YOU_TYPED;
    case QoraiIOSAutocompleteMatchTypeSearchHistory:
      return AutocompleteMatch::Type::SEARCH_HISTORY;
    case QoraiIOSAutocompleteMatchTypeSearchOtherEngine:
      return AutocompleteMatch::Type::SEARCH_OTHER_ENGINE;
    case QoraiIOSAutocompleteMatchTypeBookmarkTitle:
      return AutocompleteMatch::Type::BOOKMARK_TITLE;
    case QoraiIOSAutocompleteMatchTypeClipboardUrl:
      return AutocompleteMatch::Type::CLIPBOARD_URL;
    case QoraiIOSAutocompleteMatchTypeClipboardText:
      return AutocompleteMatch::Type::CLIPBOARD_TEXT;
    case QoraiIOSAutocompleteMatchTypeOpenTab:
      return AutocompleteMatch::Type::OPEN_TAB;
  }
  NOTREACHED() << "Unknown QoraiIOSAutocompleteMatchType: " << type;
}

QoraiIOSAutocompleteMatchType QoraiTypeFromMatchType(
    AutocompleteMatch::Type type) {
  switch (type) {
    case AutocompleteMatch::Type::URL_WHAT_YOU_TYPED:
      return QoraiIOSAutocompleteMatchTypeUrlWhatYouTyped;
    case AutocompleteMatch::Type::HISTORY_URL:
      return QoraiIOSAutocompleteMatchTypeHistoryUrl;
    case AutocompleteMatch::Type::NAVSUGGEST:
      return QoraiIOSAutocompleteMatchTypeNavSuggest;
    case AutocompleteMatch::Type::SEARCH_WHAT_YOU_TYPED:
      return QoraiIOSAutocompleteMatchTypeSearchWhatYouTyped;
    case AutocompleteMatch::Type::SEARCH_HISTORY:
      return QoraiIOSAutocompleteMatchTypeSearchHistory;
    case AutocompleteMatch::Type::SEARCH_OTHER_ENGINE:
      return QoraiIOSAutocompleteMatchTypeSearchOtherEngine;
    case AutocompleteMatch::Type::BOOKMARK_TITLE:
      return QoraiIOSAutocompleteMatchTypeBookmarkTitle;
    case AutocompleteMatch::Type::CLIPBOARD_URL:
      return QoraiIOSAutocompleteMatchTypeClipboardUrl;
    case AutocompleteMatch::Type::CLIPBOARD_TEXT:
      return QoraiIOSAutocompleteMatchTypeClipboardText;
    case AutocompleteMatch::Type::OPEN_TAB:
      return QoraiIOSAutocompleteMatchTypeOpenTab;
    default:
      NOTREACHED() << "Unknown AutocompleteMatch::Type: " << type;
  }
}
}  // namespace qorai

@implementation QoraiIOSAutocompleteMatch
- (instancetype)initWithText:(NSString*)text
                        type:(QoraiIOSAutocompleteMatchType)type
              destinationURL:(NSURL*)destinationURL {
  if ((self = [super init])) {
    _text = text;
    _type = type;
    _destinationURL = destinationURL;
  }
  return self;
}
@end

@implementation QoraiIOSAutocompleteClassifier

+ (QoraiIOSAutocompleteMatch*)classify:(NSString*)text {
  std::vector<ProfileIOS*> profiles =
      GetApplicationContext()->GetProfileManager()->GetLoadedProfiles();
  ProfileIOS* last_used_profile = profiles.at(0);

  AutocompleteClassifier* classifier =
      ios::AutocompleteClassifierFactory::GetForProfile(last_used_profile);
  if (classifier) {
    AutocompleteMatch match;
    classifier->Classify(base::SysNSStringToUTF16(text), false, false,
                         metrics::OmniboxEventProto::INVALID_SPEC, &match,
                         nullptr);

    if (!match.destination_url.is_valid()) {
      return nil;
    }

    return [[QoraiIOSAutocompleteMatch alloc]
          initWithText:text
                  type:qorai::QoraiTypeFromMatchType(match.type)
        destinationURL:net::NSURLWithGURL(match.destination_url)];
  }
  return nil;
}

+ (bool)isSearchType:(QoraiIOSAutocompleteMatchType)type {
  return AutocompleteMatch::IsSearchType(qorai::MatchTypeFromQoraiType(type));
}

@end
