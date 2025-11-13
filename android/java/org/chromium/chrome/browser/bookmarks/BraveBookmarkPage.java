/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.bookmarks;

import android.content.ComponentName;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.back_press.BackPressManager;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.ui.messages.snackbar.SnackbarManager;
import org.chromium.chrome.browser.ui.native_page.NativePageHost;

public class QoraiBookmarkPage extends BookmarkPage {
    // Overridden Chromium's BookmarkPage.mManager
    private BookmarkManagerCoordinator mBookmarkManagerCoordinator;

    public QoraiBookmarkPage(
            @NonNull SnackbarManager snackbarManager,
            @NonNull Profile profile,
            @NonNull NativePageHost host,
            @Nullable ComponentName componentName,
            BackPressManager backPressManager) {
        super(snackbarManager, profile, host, componentName, backPressManager);

        if (mBookmarkManagerCoordinator instanceof QoraiBookmarkManagerCoordinator
                && QoraiActivity.getChromeTabbedActivity() != null) {
            ((QoraiBookmarkManagerCoordinator) mBookmarkManagerCoordinator)
                    .setWindow(QoraiActivity.getChromeTabbedActivity().getWindowAndroid());
        }
    }
}
