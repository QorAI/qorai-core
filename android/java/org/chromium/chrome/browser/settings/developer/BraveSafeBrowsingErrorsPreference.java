/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings.developer;

import android.content.Context;
import android.util.AttributeSet;

import org.chromium.base.QoraiPreferenceKeys;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;

public class QoraiSafeBrowsingErrorsPreference extends ChromeSwitchPreference {
    public QoraiSafeBrowsingErrorsPreference(Context context) {
        super(context);
    }

    public QoraiSafeBrowsingErrorsPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void onClick() {
        super.onClick();
        ChromeSharedPreferences.getInstance()
                .writeBoolean(QoraiPreferenceKeys.QORAI_SAFE_BROWSING_ERRORS, isChecked());
    }
}
