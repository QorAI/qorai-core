/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.omnibox.suggestions.editurl;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.chrome.browser.omnibox.suggestions.AutocompleteUIContext;
import org.chromium.chrome.browser.omnibox.suggestions.base.BaseSuggestionViewProcessor;
import org.chromium.components.omnibox.AutocompleteMatch;

public abstract class QoraiEditUrlSuggestionProcessorBase extends BaseSuggestionViewProcessor {
    public QoraiEditUrlSuggestionProcessorBase(AutocompleteUIContext uiContext) {
        super(uiContext);
    }

    /*
     * Calls to the upstream's `EditUrlSuggestionProcessor.onCopyLink` will be redirected here via bytecode.
     * Here we call the upstream's `EditUrlSuggestionProcessor.onCopyLink` with possibly changed suggestion.
     * See comment to `QoraiEditUrlSuggestionProcessor.maybeUpdateSuggestionForCopyLink` for more details on why it may be changed.
     */
    public void onCopyLink(AutocompleteMatch suggestion) {
        QoraiReflectionUtil.invokeMethod(
                EditUrlSuggestionProcessor.class,
                this,
                "onCopyLink",
                AutocompleteMatch.class,
                maybeUpdateSuggestionForCopyLink(suggestion));
    }

    public AutocompleteMatch maybeUpdateSuggestionForCopyLink(AutocompleteMatch suggestion) {
        assert false : "This method should be overridden by QoraiEditUrlSuggestionProcessor";
        return suggestion;
    }
}
