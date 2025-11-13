// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Foundation/Foundation.h>

#ifndef QORAI_IOS_BROWSER_API_OMNIBOX_AUTOCOMPLETE_CLASSIFIER_H_
#define QORAI_IOS_BROWSER_API_OMNIBOX_AUTOCOMPLETE_CLASSIFIER_H_

NS_ASSUME_NONNULL_BEGIN

// From:
// https://source.chromium.org/chromium/chromium/src/+/main:components/omnibox/browser/autocomplete_match_type.h
NS_SWIFT_NAME(AutocompleteMatch.Type)
typedef NS_ENUM(NSUInteger, QoraiIOSAutocompleteMatchType) {
  QoraiIOSAutocompleteMatchTypeUrlWhatYouTyped = 0,  // The input as a URL.
  QoraiIOSAutocompleteMatchTypeHistoryUrl =
      1,  // A past page whose URL contains the input.
  QoraiIOSAutocompleteMatchTypeNavSuggest = 5,  // A suggested URL.
  QoraiIOSAutocompleteMatchTypeSearchWhatYouTyped =
      6,  // The input as a search query (with the default engine).
  QoraiIOSAutocompleteMatchTypeSearchHistory =
      7,  // A past search (with the default engine) containing the input.
  QoraiIOSAutocompleteMatchTypeSearchOtherEngine =
      13,  // A search with a non-default engine.
  QoraiIOSAutocompleteMatchTypeBookmarkTitle =
      16,  // A bookmark whose title contains the input.
  QoraiIOSAutocompleteMatchTypeClipboardUrl =
      19,  // A URL based on the clipboard.
  QoraiIOSAutocompleteMatchTypeClipboardText =
      26,  // Text based on the clipboard.
  QoraiIOSAutocompleteMatchTypeOpenTab =
      30,  // A URL match amongst the currently open tabs.
};

OBJC_EXPORT
NS_SWIFT_NAME(AutocompleteMatch)
@interface QoraiIOSAutocompleteMatch : NSObject
@property(nonatomic, readonly)
    NSString* text;  // The text passed into the classifier
@property(nonatomic, readonly)
    QoraiIOSAutocompleteMatchType type;  // The type of match
@property(nonatomic, readonly)
    NSURL* destinationURL;  // The suggested search URL
@end

OBJC_EXPORT
NS_SWIFT_NAME(AutocompleteClassifier)
@interface QoraiIOSAutocompleteClassifier : NSObject
+ (nullable QoraiIOSAutocompleteMatch*)classify:(NSString*)text;
+ (bool)isSearchType:(QoraiIOSAutocompleteMatchType)type;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_OMNIBOX_AUTOCOMPLETE_CLASSIFIER_H_
