/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.tasks;

import android.content.Intent;
import android.os.Bundle;

import org.chromium.chrome.browser.ChromeInactivityTracker;
import org.chromium.chrome.browser.ntp.QoraiFreshNtpHelper;

public final class QoraiReturnToChromeUtil {
    /** Returns whether should show a NTP as the home surface at startup. */
    public static boolean shouldShowNtpAsHomeSurfaceAtStartup(
            Intent intent, Bundle bundle, ChromeInactivityTracker inactivityTracker) {
        // When feature is disabled, use Qorai's default behavior
        if (!QoraiFreshNtpHelper.isEnabled()) {
            return false;
        }

        // Uncomment this when the experiment is ready
        // When feature is enabled, check the variant
        // String variant = QoraiFreshNtpHelper.getVariant();
        // switch (variant) {
        //     case "A":
        //         // Variant A: Qorai's default behavior (no NTP at startup)
        //         return false;
        //     default:
        //         // All other variants: fallback to upstream behavior
        //         //return ReturnToChromeUtil.shouldShowNtpAsHomeSurfaceAtStartup(
        //         //        intent, bundle, inactivityTracker);
        // }
        return false;
    }
}
