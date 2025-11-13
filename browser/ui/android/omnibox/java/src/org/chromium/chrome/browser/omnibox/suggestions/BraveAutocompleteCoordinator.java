/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.omnibox.suggestions;

import android.view.LayoutInflater;
import android.view.View;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.base.Callback;
import org.chromium.chrome.browser.omnibox.R;
import org.chromium.chrome.browser.omnibox.suggestions.SuggestionListViewBinder.SuggestionListViewHolder;
import org.chromium.chrome.browser.omnibox.suggestions.base.BaseSuggestionView;
import org.chromium.chrome.browser.omnibox.suggestions.base.BaseSuggestionViewBinder;
import org.chromium.chrome.browser.omnibox.suggestions.qoraiqora.QoraiQoraSuggestionViewBinder;
import org.chromium.chrome.browser.omnibox.suggestions.qorai_search.QoraiSearchBannerViewBinder;
import org.chromium.ui.ViewProvider;

import java.util.ArrayList;
import java.util.List;

public class QoraiAutocompleteCoordinator {
    public ViewProvider<SuggestionListViewHolder> createViewProvider() {
        ViewProvider<SuggestionListViewHolder> provider =
                (ViewProvider<SuggestionListViewHolder>)
                        QoraiReflectionUtil.invokeMethod(
                                AutocompleteCoordinator.class, this, "createViewProvider");

        return new ViewProvider<SuggestionListViewHolder>() {
            private List<Callback<SuggestionListViewHolder>> mCallbacks = new ArrayList<>();
            private SuggestionListViewHolder mHolder;

            @Override
            public void inflate() {
                provider.whenLoaded(
                        (holder) -> {
                            OmniboxSuggestionsDropdown dropdown = holder.dropdown;
                            if (dropdown != null && dropdown.getAdapter() != null) {
                                addTypes(dropdown.getAdapter());
                                mHolder = holder;
                                for (int i = 0; i < mCallbacks.size(); i++) {
                                    mCallbacks.get(i).onResult(holder);
                                }
                                mCallbacks = null;
                            }
                        });
                provider.inflate();
            }

            private void addTypes(OmniboxSuggestionsDropdownAdapter adapter) {
                adapter.registerType(
                        QoraiOmniboxSuggestionUiType.QORAI_SEARCH_PROMO_BANNER,
                        parent ->
                                LayoutInflater.from(parent.getContext())
                                        .inflate(R.layout.omnibox_qorai_search_banner, null),
                        QoraiSearchBannerViewBinder::bind);

                adapter.registerType(
                        QoraiOmniboxSuggestionUiType.QORAI_QORA_SUGGESTION,
                        parent ->
                                new BaseSuggestionView<View>(
                                        parent.getContext(), R.layout.omnibox_basic_suggestion),
                        new BaseSuggestionViewBinder<View>(QoraiQoraSuggestionViewBinder::bind));
            }

            @Override
            public void whenLoaded(Callback<SuggestionListViewHolder> callback) {
                if (mHolder != null) {
                    callback.onResult(mHolder);
                    return;
                }
                mCallbacks.add(callback);
            }
        };
    }
}
