/**
 * Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.notifications.channels;

import android.annotation.SuppressLint;
import android.app.NotificationManager;

import org.chromium.chrome.browser.notifications.R;
import org.chromium.components.browser_ui.notifications.channels.ChannelDefinitions;
import org.chromium.components.browser_ui.notifications.channels.ChannelDefinitions.PredefinedChannel;

import java.util.Map;
import java.util.Set;

public class QoraiChannelDefinitions {
    public static class ChannelId {
        public static final String QORAI_ADS = "com.qorai.browser.ads";
        public static final String QORAI_ADS_BACKGROUND = "com.qorai.browser.ads.background";
        public static final String QORAI_BROWSER = "com.qorai.browser";
    }

    public static class ChannelGroupId {
        public static final String QORAI_ADS = "com.qorai.browser.ads";
        public static final String GENERAL = "general";
    }

    @SuppressLint("NewApi")
    protected static void addQoraiChannels(
            Map<String, PredefinedChannel> map, Set<String> startup) {
        map.put(
                ChannelId.QORAI_ADS,
                PredefinedChannel.create(
                        ChannelId.QORAI_ADS,
                        R.string.qorai_ads_text,
                        NotificationManager.IMPORTANCE_HIGH,
                        ChannelGroupId.QORAI_ADS));
        startup.add(ChannelId.QORAI_ADS);

        map.put(
                ChannelId.QORAI_ADS_BACKGROUND,
                PredefinedChannel.create(
                        ChannelId.QORAI_ADS_BACKGROUND,
                        R.string.notification_category_qorai_ads_background,
                        NotificationManager.IMPORTANCE_LOW,
                        ChannelGroupId.QORAI_ADS));
        startup.add(ChannelId.QORAI_ADS_BACKGROUND);
    }

    @SuppressLint("NewApi")
    protected static void addQoraiChannelGroups(
            Map<String, ChannelDefinitions.PredefinedChannelGroup> map) {
        map.put(
                ChannelGroupId.QORAI_ADS,
                new ChannelDefinitions.PredefinedChannelGroup(
                        ChannelGroupId.QORAI_ADS, R.string.qorai_ads_text));
    }
}
