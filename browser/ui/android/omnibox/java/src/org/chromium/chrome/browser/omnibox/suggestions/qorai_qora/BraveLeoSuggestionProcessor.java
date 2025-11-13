/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.omnibox.suggestions.qoraiqora;

import androidx.annotation.NonNull;

import org.chromium.chrome.browser.omnibox.R;
import org.chromium.chrome.browser.omnibox.UrlBarEditingTextStateProvider;
import org.chromium.chrome.browser.omnibox.styles.OmniboxDrawableState;
import org.chromium.chrome.browser.omnibox.styles.SuggestionSpannable;
import org.chromium.chrome.browser.omnibox.suggestions.AutocompleteUIContext;
import org.chromium.chrome.browser.omnibox.suggestions.QoraiQoraAutocompleteDelegate;
import org.chromium.chrome.browser.omnibox.suggestions.QoraiOmniboxSuggestionUiType;
import org.chromium.chrome.browser.omnibox.suggestions.base.BaseSuggestionViewProcessor;
import org.chromium.chrome.browser.omnibox.suggestions.base.BaseSuggestionViewProperties;
import org.chromium.chrome.browser.omnibox.suggestions.basic.SuggestionViewProperties;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.components.omnibox.AutocompleteMatch;
import org.chromium.ui.modelutil.PropertyModel;

import java.util.function.Supplier;

/** A class that handles model and view creation for the Qorai Qora suggestion. */
public class QoraiQoraSuggestionProcessor extends BaseSuggestionViewProcessor {
    private final UrlBarEditingTextStateProvider mUrlBarEditingTextProvider;
    private QoraiQoraAutocompleteDelegate mQoraiQoraAutocompleteDelegate;
    private final String mAskQora;
    private final @NonNull Supplier<Tab> mActivityTabSupplier;

    public QoraiQoraSuggestionProcessor(AutocompleteUIContext uiContext) {
        super(uiContext);
        mActivityTabSupplier = uiContext.activityTabSupplier;
        mUrlBarEditingTextProvider = uiContext.textProvider;
        mAskQora = uiContext.context.getResources().getString(R.string.ask_qora_auto_suggestion);
    }

    public void setQoraiQoraAutocompleteDelegate(QoraiQoraAutocompleteDelegate delegate) {
        mQoraiQoraAutocompleteDelegate = delegate;
    }

    public void populateModel(final PropertyModel model) {
        model.set(
                BaseSuggestionViewProperties.ICON,
                OmniboxDrawableState.forSmallIcon(
                        mContext, R.drawable.ic_qorai_ai_color, /* allowTint= */ false));
        model.set(
                SuggestionViewProperties.TEXT_LINE_1_TEXT,
                new SuggestionSpannable(mUrlBarEditingTextProvider.getTextWithoutAutocomplete()));
        model.set(SuggestionViewProperties.TEXT_LINE_2_TEXT, new SuggestionSpannable(mAskQora));
        model.set(
                BaseSuggestionViewProperties.ON_CLICK,
                () -> {
                    Tab tab = mActivityTabSupplier.get();
                    if (tab != null) {
                        mQoraiQoraAutocompleteDelegate.openQoraQuery(
                                tab.getWebContents(),
                                "",
                                mUrlBarEditingTextProvider.getTextWithoutAutocomplete());
                    }
                });
    }

    @Override
    public int getViewTypeId() {
        return QoraiOmniboxSuggestionUiType.QORAI_QORA_SUGGESTION;
    }

    @Override
    public PropertyModel createModel() {
        return new PropertyModel(SuggestionViewProperties.ALL_KEYS);
    }

    @Override
    public boolean doesProcessSuggestion(AutocompleteMatch suggestion, int position) {
        return true;
    }
}
