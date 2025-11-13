/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.omnibox.suggestions;

import org.chromium.content_public.browser.WebContents;

/**
 * Provides additional functionality to trigger and interact with Qorai Qora autocomplete suggestion.
 */
public interface QoraiQoraAutocompleteDelegate {
    boolean isQoraEnabled();

    boolean isAutoCompleteEnabled(WebContents webContents);

    void openQoraQuery(WebContents webContents, String conversationUuid, String query);
}
