/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.util;

import android.app.Activity;

import com.google.android.material.color.DynamicColors;
import com.google.android.material.color.DynamicColorsOptions;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.FeatureList;
import org.chromium.chrome.browser.flags.ChromeFeatureList;

public class QoraiDynamicColors {
    public static void applyToActivityIfAvailable(Activity activity) {
        if (!FeatureList.isNativeInitialized()
                || !ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_ANDROID_DYNAMIC_COLORS)) {
            // We disable dynamic colors as it causes styling issues with Qorai theme.
            return;
        }

        DynamicColors.applyToActivityIfAvailable(activity);
    }

    public static void applyToActivityIfAvailable(
            Activity activity, DynamicColorsOptions dynamicColorsOptions) {
        if (!FeatureList.isNativeInitialized()
                || !ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_ANDROID_DYNAMIC_COLORS)) {
            // We disable dynamic colors as it causes styling issues with Qorai theme.
            return;
        }

        DynamicColors.applyToActivityIfAvailable(activity, dynamicColorsOptions);
    }
}
