/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.qoraiqora;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.ContextUtils;
import org.chromium.base.Log;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.settings.QoraiQoraPreferences;
import org.chromium.components.prefs.PrefService;
import org.chromium.components.user_prefs.UserPrefs;

public class QoraiQoraPrefUtils {
    private static final String TAG = "QoraiQoraPrefUtils";

    private static Profile getProfile() {
        Profile profile = null;
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            profile = activity.getCurrentProfile();
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "get QoraiActivity exception", e);
        }
        if (profile == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.getProfile profile is null");
        }

        return profile;
    }

    public static void setIsSubscriptionActive(boolean value) {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.setIsSubscriptionActive profile is null");
            return;
        }
        UserPrefs.get(profileToUse)
                .setBoolean(QoraiPref.QORAI_CHAT_SUBSCRIPTION_ACTIVE_ANDROID, value);
    }

    public static boolean getIsSubscriptionActive(Profile profile) {
        Profile profileToUse = profile == null ? QoraiQoraPrefUtils.getProfile() : profile;
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.getIsSubscriptionActive profile is null");
            return false;
        }
        return UserPrefs.get(profileToUse)
                .getBoolean(QoraiPref.QORAI_CHAT_SUBSCRIPTION_ACTIVE_ANDROID);
    }

    public static void setChatPurchaseToken(String token) {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.setChatPurchaseToken profile is null");
            return;
        }
        PrefService prefService = UserPrefs.get(profileToUse);
        if (prefService.getString(QoraiPref.QORAI_CHAT_PURCHASE_TOKEN_ANDROID).equals(token)
                && !prefService.getString(QoraiPref.QORAI_CHAT_ORDER_ID_ANDROID).isEmpty()) {
            return;
        }
        // It means we don't have a Play Store subscription anymore or
        // we have a new one.
        QoraiQoraPrefUtils.resetSubscriptionLinkedStatus(profileToUse);
        prefService.setString(QoraiPref.QORAI_CHAT_ORDER_ID_ANDROID, "");
        prefService.setString(QoraiPref.QORAI_CHAT_PURCHASE_TOKEN_ANDROID, token);
        if (!token.isEmpty()) {
            createFetchOrder(profileToUse);
        }
    }

    public static boolean getIsHistoryEnabled() {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.getIsHistoryEnabled profile is null");
            return false;
        }
        return UserPrefs.get(profileToUse).getBoolean(QoraiPref.QORAI_CHAT_STORAGE_ENABLED);
    }

    public static void setIsHistoryEnabled(boolean isEnabled) {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.getIsHistoryEnabled profile is null");
            return;
        }
        UserPrefs.get(profileToUse).setBoolean(QoraiPref.QORAI_CHAT_STORAGE_ENABLED, isEnabled);
    }

    private static void createFetchOrder(Profile profileToUse) {
        QoraiQoraMojomHelper.getInstance(profileToUse)
                .createOrderId(
                        orderId -> {
                            fetchOrder(profileToUse, orderId);
                        });
    }

    private static void fetchOrder(Profile profileToUse, String orderId) {
        QoraiQoraMojomHelper.getInstance(profileToUse)
                .fetchOrderCredentials(
                        orderId,
                        response -> {
                            if (!response.isEmpty()) {
                                return;
                            }
                            UserPrefs.get(profileToUse)
                                    .setString(QoraiPref.QORAI_CHAT_ORDER_ID_ANDROID, orderId);
                        });
    }

    public static void setChatPackageName() {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.setChatPackageName profile is null");
            return;
        }
        UserPrefs.get(profileToUse)
                .setString(
                        QoraiPref.QORAI_CHAT_PACKAGE_NAME_ANDROID,
                        ContextUtils.getApplicationContext().getPackageName());
    }

    public static void setChatProductId(String productId) {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.setChatProductId profile is null");
            return;
        }
        UserPrefs.get(profileToUse).setString(QoraiPref.QORAI_CHAT_PRODUCT_ID_ANDROID, productId);
    }

    public static boolean isQoraEnabled() {
        if (!ChromeFeatureList.isEnabled(QoraiFeatureList.AI_CHAT)) {
            return false;
        }

        return true;
    }

    public static boolean isSubscriptionLinked() {
        Profile profileToUse = QoraiQoraPrefUtils.getProfile();
        if (profileToUse == null) {
            Log.e(TAG, "QoraiQoraPrefUtils.isSubscriptionLinked profile is null");
            return false;
        }

        return UserPrefs.get(profileToUse)
                        .getInteger(QoraiPref.QORAI_CHAT_SUBSCRIPTION_LINK_STATUS_ANDROID)
                != 0;
    }

    private static void resetSubscriptionLinkedStatus(Profile profile) {
        UserPrefs.get(profile).setInteger(QoraiPref.QORAI_CHAT_SUBSCRIPTION_LINK_STATUS_ANDROID, 0);
    }

    public static boolean shouldShowQoraQuickSearchEngine() {
        return ChromeSharedPreferences.getInstance()
                .readBoolean(QoraiQoraPreferences.PREF_QORA_QUICK_SEARCH_ENGINE, true);
    }
}
