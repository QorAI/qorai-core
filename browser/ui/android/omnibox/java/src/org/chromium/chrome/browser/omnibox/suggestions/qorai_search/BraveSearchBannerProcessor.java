/**
 * Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.omnibox.suggestions.qorai_search;

import android.content.Context;

import org.chromium.chrome.browser.omnibox.R;
import org.chromium.chrome.browser.omnibox.UrlBarEditingTextStateProvider;
import org.chromium.chrome.browser.omnibox.suggestions.AutocompleteDelegate;
import org.chromium.chrome.browser.omnibox.suggestions.QoraiOmniboxSuggestionUiType;
import org.chromium.chrome.browser.omnibox.suggestions.QoraiSuggestionHost;
import org.chromium.chrome.browser.omnibox.suggestions.DropdownItemProcessor;
import org.chromium.chrome.browser.omnibox.suggestions.OmniboxLoadUrlParams;
import org.chromium.ui.base.PageTransition;
import org.chromium.ui.modelutil.PropertyModel;

/** A class that handles model and view creation for the suggestion qorai search banner. */
public class QoraiSearchBannerProcessor implements DropdownItemProcessor {
    private final QoraiSuggestionHost mSuggestionHost;
    private final int mMinimumHeight;
    private final UrlBarEditingTextStateProvider mUrlBarEditingTextProvider;
    private final AutocompleteDelegate mUrlBarDelegate;

    /**
     * @param context An Android context.
     * @param suggestionHost A handle to the object using the suggestions.
     */
    public QoraiSearchBannerProcessor(Context context, QoraiSuggestionHost suggestionHost,
            UrlBarEditingTextStateProvider editingTextProvider, AutocompleteDelegate urlDelegate) {
        mSuggestionHost = suggestionHost;
        mUrlBarEditingTextProvider = editingTextProvider;
        mUrlBarDelegate = urlDelegate;
        mMinimumHeight = context.getResources().getDimensionPixelSize(
                R.dimen.omnibox_qorai_search_banner_height);
    }

    public void populateModel(final PropertyModel model) {
        model.set(
                QoraiSearchBannerProperties.DELEGATE,
                new QoraiSearchBannerProperties.Delegate() {
                    @Override
                    public void onPositiveClicked() {
                        mUrlBarDelegate.loadUrl(
                                new OmniboxLoadUrlParams.Builder(
                                                "https://search.qorai.com/search?q="
                                                        + mUrlBarEditingTextProvider
                                                                .getTextWithoutAutocomplete()
                                                        + "&action=makeDefault",
                                                PageTransition.LINK)
                                        .setInputStartTimestamp(System.currentTimeMillis())
                                        .setOpenInNewTab(false)
                                        .build());
                    }

                    @Override
                    public void onNegativeClicked() {
                        mSuggestionHost.removeQoraiSearchSuggestion();
                    }
                });
    }

    @Override
    public int getViewTypeId() {
        return QoraiOmniboxSuggestionUiType.QORAI_SEARCH_PROMO_BANNER;
    }

    @Override
    public int getMinimumViewHeight() {
        return mMinimumHeight;
    }

    @Override
    public PropertyModel createModel() {
        return new PropertyModel(QoraiSearchBannerProperties.ALL_KEYS);
    }

    @Override
    public void onOmniboxSessionStateChange(boolean activated) {}

    @Override
    public void onNativeInitialized() {}
}
