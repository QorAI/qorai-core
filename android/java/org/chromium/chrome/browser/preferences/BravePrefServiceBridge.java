/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.preferences;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.base.ThreadUtils;
import org.chromium.chrome.browser.profiles.Profile;

/**
 * Please don't add anything in that file. We are going to refactor it soon.
 * Check this PRs on how to handle preferences correctly:
 * https://github.com/qorai/qorai-core/pull/16356
 * https://github.com/qorai/qorai-core/pull/15905
 * For the local_state based prefs please look on the PR:
 * https://github.com/qorai/qorai-core/pull/16486
 * Contact code owners if you have additional questions.
 */

@JNINamespace("chrome::android")
public class QoraiPrefServiceBridge {
    private QoraiPrefServiceBridge() {
    }

    private static QoraiPrefServiceBridge sInstance;

    public static QoraiPrefServiceBridge getInstance() {
        ThreadUtils.assertOnUiThread();
        if (sInstance == null) {
            sInstance = new QoraiPrefServiceBridge();
        }
        return sInstance;
    }

    public void setCookiesBlockType(String type) {
        QoraiPrefServiceBridgeJni.get().setCookiesBlockType(type);
    }

    public String getCookiesBlockType() {
        return QoraiPrefServiceBridgeJni.get().getCookiesBlockType();
    }

    public void setPlayYTVideoInBrowserEnabled(boolean enabled) {
        QoraiPrefServiceBridgeJni.get().setPlayYTVideoInBrowserEnabled(enabled);
    }

    public boolean getPlayYTVideoInBrowserEnabled() {
        return QoraiPrefServiceBridgeJni.get().getPlayYTVideoInBrowserEnabled();
    }

    public void setDesktopModeEnabled(boolean enabled) {
        QoraiPrefServiceBridgeJni.get().setDesktopModeEnabled(enabled);
    }

    public boolean getDesktopModeEnabled() {
        return QoraiPrefServiceBridgeJni.get().getDesktopModeEnabled();
    }

    public long getTrackersBlockedCount(Profile profile) {
        return QoraiPrefServiceBridgeJni.get().getTrackersBlockedCount(profile);
    }

    public long getAdsBlockedCount(Profile profile) {
        return QoraiPrefServiceBridgeJni.get().getAdsBlockedCount(profile);
    }

    public long getDataSaved(Profile profile) {
        return QoraiPrefServiceBridgeJni.get().getDataSaved(profile);
    }

    public void resetPromotionLastFetchStamp() {
        QoraiPrefServiceBridgeJni.get().resetPromotionLastFetchStamp();
    }

    public void setOldTrackersBlockedCount(Profile profile, long count) {
        QoraiPrefServiceBridgeJni.get().setOldTrackersBlockedCount(profile, count);
    }

    public void setOldAdsBlockedCount(Profile profile, long count) {
        QoraiPrefServiceBridgeJni.get().setOldAdsBlockedCount(profile, count);
    }

    public void setOldHttpsUpgradesCount(Profile profile, long count) {
        QoraiPrefServiceBridgeJni.get().setOldHttpsUpgradesCount(profile, count);
    }

    public boolean getBooleanForContentSetting(int contentType) {
        return QoraiPrefServiceBridgeJni.get().getBooleanForContentSetting(contentType);
    }

    public void setWebrtcPolicy(int policy) {
        QoraiPrefServiceBridgeJni.get().setWebrtcPolicy(policy);
    }

    public int getWebrtcPolicy() {
        return QoraiPrefServiceBridgeJni.get().getWebrtcPolicy();
    }

    public void setNewsOptIn(boolean value) {
        QoraiPrefServiceBridgeJni.get().setNewsOptIn(value);
    }

    public boolean getNewsOptIn() {
        return QoraiPrefServiceBridgeJni.get().getNewsOptIn();
    }

    public void setShowNews(boolean value) {
        QoraiPrefServiceBridgeJni.get().setShowNews(value);
    }

    public boolean getShowNews() {
        return QoraiPrefServiceBridgeJni.get().getShowNews();
    }

    @NativeMethods
    interface Natives {
        void setCookiesBlockType(String type);
        String getCookiesBlockType();

        void setPlayYTVideoInBrowserEnabled(boolean enabled);

        boolean getPlayYTVideoInBrowserEnabled();

        void setDesktopModeEnabled(boolean enabled);

        boolean getDesktopModeEnabled();

        long getTrackersBlockedCount(Profile profile);

        long getAdsBlockedCount(Profile profile);

        long getDataSaved(Profile profile);

        // Used to pass total stat from upgrading old tabs based browser
        // to a new core based
        void setOldTrackersBlockedCount(Profile profile, long count);

        void setOldAdsBlockedCount(Profile profile, long count);

        void setOldHttpsUpgradesCount(Profile profile, long count);

        void resetPromotionLastFetchStamp();

        boolean getBooleanForContentSetting(int contentType);

        void setWebrtcPolicy(int policy);

        int getWebrtcPolicy();

        void setNewsOptIn(boolean value);

        boolean getNewsOptIn();

        void setShowNews(boolean value);

        boolean getShowNews();
    }
}
