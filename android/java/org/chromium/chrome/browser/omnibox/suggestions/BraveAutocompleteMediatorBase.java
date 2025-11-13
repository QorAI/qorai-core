/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.omnibox.suggestions;

import android.content.Context;

import androidx.annotation.NonNull;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.omnibox.LocationBarDataProvider;
import org.chromium.components.omnibox.AutocompleteMatch;
import org.chromium.components.omnibox.OmniboxSuggestionType;
import org.chromium.misc_metrics.mojom.MiscAndroidMetrics;
import org.chromium.url.GURL;

class QoraiAutocompleteMediatorBase {
    void loadUrlForOmniboxMatch(
            int matchIndex,
            @NonNull AutocompleteMatch suggestion,
            @NonNull GURL url,
            long inputStart,
            boolean openInNewTab,
            boolean shouldUpdateSuggestionUrl) {
        Context context =
                (Context)
                        QoraiReflectionUtil.getField(AutocompleteMediator.class, "mContext", this);
        LocationBarDataProvider dataProvider =
                (LocationBarDataProvider)
                        QoraiReflectionUtil.getField(
                                AutocompleteMediator.class, "mDataProvider", this);

        if (dataProvider != null
                && !dataProvider.isIncognito()
                && context != null
                && context instanceof QoraiActivity) {
            MiscAndroidMetrics miscAndroidMetrics =
                    ((QoraiActivity) context).getMiscAndroidMetrics();
            if (miscAndroidMetrics != null) {
                boolean isNewTab = dataProvider.getNewTabPageDelegate().isCurrentlyVisible();
                boolean isSearchQuery =
                        suggestion.getType() == OmniboxSuggestionType.SEARCH_WHAT_YOU_TYPED
                                || suggestion.getType() == OmniboxSuggestionType.SEARCH_SUGGEST;
                miscAndroidMetrics.recordLocationBarChange(isNewTab, isSearchQuery);
            }
        }

        QoraiReflectionUtil.invokeMethod(
                AutocompleteMediator.class,
                this,
                "loadUrlForOmniboxMatch",
                int.class,
                matchIndex,
                AutocompleteMatch.class,
                suggestion,
                GURL.class,
                url,
                long.class,
                inputStart,
                boolean.class,
                openInNewTab,
                boolean.class,
                shouldUpdateSuggestionUrl);
    }
}
