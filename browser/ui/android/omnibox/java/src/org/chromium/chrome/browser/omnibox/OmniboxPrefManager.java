/**
 * Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.omnibox;

import android.content.SharedPreferences;

import org.chromium.base.ContextUtils;

import java.util.Calendar;
import java.util.Date;

public class OmniboxPrefManager {
    private static final String QORAI_SEARCH_PROMO_BANNER_EXPIRED_DATE =
            "qorai_search_promo_banner_expired_date";
    private static final String QORAI_SEARCH_PROMO_BANNER_MAYBE_LATER =
            "qorai_search_promo_banner_maybe_later";
    private static final String QORAI_SEARCH_PROMO_BANNER_DISMISSED =
            "qorai_search_promo_banner_dismissed";

    private static OmniboxPrefManager sInstance;
    private final SharedPreferences mSharedPreferences;

    private boolean isQoraiSearchPromoBannerDismissedCurrentSession;

    private OmniboxPrefManager() {
        mSharedPreferences = ContextUtils.getAppSharedPreferences();
    }

    /**
     * Returns the singleton instance of OmniboxPrefManager, creating it if needed.
     */
    public static OmniboxPrefManager getInstance() {
        if (sInstance == null) {
            sInstance = new OmniboxPrefManager();
        }
        return sInstance;
    }

    public long getQoraiSearchPromoBannerExpiredDate() {
        return mSharedPreferences.getLong(QORAI_SEARCH_PROMO_BANNER_EXPIRED_DATE, 0);
    }

    public void setQoraiSearchPromoBannerExpiredDate() {
        Calendar calender = Calendar.getInstance();
        calender.setTime(new Date());
        calender.add(Calendar.DATE, 14);

        SharedPreferences.Editor sharedPreferencesEditor = mSharedPreferences.edit();
        sharedPreferencesEditor.putLong(
                QORAI_SEARCH_PROMO_BANNER_EXPIRED_DATE, calender.getTimeInMillis());
        sharedPreferencesEditor.apply();
    }

    public boolean isQoraiSearchPromoBannerMaybeLater() {
        return mSharedPreferences.getBoolean(QORAI_SEARCH_PROMO_BANNER_MAYBE_LATER, false);
    }

    public void setQoraiSearchPromoBannerMaybeLater() {
        isQoraiSearchPromoBannerDismissedCurrentSession = true;

        SharedPreferences.Editor sharedPreferencesEditor = mSharedPreferences.edit();
        sharedPreferencesEditor.putBoolean(QORAI_SEARCH_PROMO_BANNER_MAYBE_LATER, true);
        sharedPreferencesEditor.apply();
    }

    public boolean isQoraiSearchPromoBannerDismissed() {
        return mSharedPreferences.getBoolean(QORAI_SEARCH_PROMO_BANNER_DISMISSED, false);
    }

    public void setQoraiSearchPromoBannerDismissed() {
        SharedPreferences.Editor sharedPreferencesEditor = mSharedPreferences.edit();
        sharedPreferencesEditor.putBoolean(QORAI_SEARCH_PROMO_BANNER_DISMISSED, true);
        sharedPreferencesEditor.apply();
    }

    public boolean isQoraiSearchPromoBannerDismissedCurrentSession() {
        return isQoraiSearchPromoBannerDismissedCurrentSession;
    }
}
