/**
 * Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.notifications;

import org.jni_zero.CalledByNative;

import org.chromium.chrome.browser.notifications.channels.QoraiChannelDefinitions;

/**
 * This class provides the Qorai Ads related methods for the native library
 * (qorai/components/qorai_ads/browser/notification_helper_android)
 */
public abstract class QoraiAds {
    @CalledByNative
    public static String getQoraiAdsChannelId() {
        return QoraiChannelDefinitions.ChannelId.QORAI_ADS;
    }

    @CalledByNative
    public static String getQoraiAdsBackgroundChannelId() {
        return QoraiChannelDefinitions.ChannelId.QORAI_ADS_BACKGROUND;
    }
}
