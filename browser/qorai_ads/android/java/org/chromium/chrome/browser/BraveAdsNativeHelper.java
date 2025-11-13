/**
 * Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.chrome.browser.profiles.Profile;

@JNINamespace("qorai_ads")
public class QoraiAdsNativeHelper {
    private QoraiAdsNativeHelper() {}

    public static boolean nativeIsOptedInToNotificationAds(Profile profile) {
        return QoraiAdsNativeHelperJni.get().isOptedInToNotificationAds(profile);
    }

    public static void nativeSetOptedInToNotificationAds(Profile profile, boolean optedIn) {
        QoraiAdsNativeHelperJni.get().setOptedInToNotificationAds(profile, optedIn);
    }

    public static boolean nativeIsSupportedRegion(Profile profile) {
        return QoraiAdsNativeHelperJni.get().isSupportedRegion(profile);
    }

    public static void nativeClearData(Profile profile) {
        QoraiAdsNativeHelperJni.get().clearData(profile);
    }

    public static void nativeOnNotificationAdShown(Profile profile, String jNotificationId) {
        QoraiAdsNativeHelperJni.get().onNotificationAdShown(profile, jNotificationId);
    }

    public static void nativeOnNotificationAdClosed(
            Profile profile, String jNotificationId, boolean jByUser) {
        QoraiAdsNativeHelperJni.get().onNotificationAdClosed(profile, jNotificationId, jByUser);
    }

    public static void nativeOnNotificationAdClicked(Profile profile, String jNotificationId) {
        QoraiAdsNativeHelperJni.get().onNotificationAdClicked(profile, jNotificationId);
    }

    @NativeMethods
    interface Natives {
        boolean isOptedInToNotificationAds(Profile profile);

        void setOptedInToNotificationAds(Profile profile, boolean optedIn);

        boolean isSupportedRegion(Profile profile);

        void clearData(Profile profile);

        void onNotificationAdShown(Profile profile, String jNotificationId);

        void onNotificationAdClosed(Profile profile, String jNotificationId, boolean jByUser);

        void onNotificationAdClicked(Profile profile, String jNotificationId);
    }
}
