/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.tasks.tab_management;

import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;

@NullMarked
public class QoraiTabUiFeatureUtilities {
    public static boolean isQoraiTabGroupsEnabled() {
        return ChromeSharedPreferences.getInstance()
                .readBoolean(
                        QoraiPreferenceKeys.QORAI_TAB_GROUPS_ENABLED,
                        ChromeSharedPreferences.getInstance()
                                .readBoolean(
                                        QoraiPreferenceKeys.QORAI_TAB_GROUPS_ENABLED_DEFAULT_VALUE,
                                        true));
    }
}
