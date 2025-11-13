/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.billing;

import org.chromium.chrome.browser.billing.InAppPurchaseWrapper.SubscriptionProduct;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;

import java.util.Locale;

public class LinkSubscriptionUtils {
    private static final String QORAI_ACCOUNT_URL_STAGING = "account.qoraisoftware.com";
    private static final String QORAI_ACCOUNT_URL = "account.qorai.com";

    public static final String PREF_LINK_SUBSCRIPTION_ON_STAGING = "link_subscription_on_staging";

    public static String getQoraiAccountLinkUrl(SubscriptionProduct subscriptionProduct) {
        String qoraiAccountUrl =
                isLinkSubscriptionOnStaging() ? QORAI_ACCOUNT_URL_STAGING : QORAI_ACCOUNT_URL;
        String linkType =
                (SubscriptionProduct.QORA == subscriptionProduct) ? "link-order" : "connect-receipt";
        String baseUrl = "https://%s?intent=%s&product=%s";
        return String.format(
                baseUrl,
                qoraiAccountUrl,
                linkType,
                subscriptionProduct.name().toLowerCase(Locale.ROOT));
    }

    public static String getQoraiAccountRecoverUrl(SubscriptionProduct subscriptionProduct) {
        String qoraiAccountUrl =
                isLinkSubscriptionOnStaging() ? QORAI_ACCOUNT_URL_STAGING : QORAI_ACCOUNT_URL;
        String baseUrl = "https://%s?intent=recover&product=%s&ux=mobile";
        return String.format(
                baseUrl, qoraiAccountUrl, subscriptionProduct.name().toLowerCase(Locale.ROOT));
    }

    public static boolean isLinkSubscriptionOnStaging() {
        return ChromeSharedPreferences.getInstance()
                .readBoolean(PREF_LINK_SUBSCRIPTION_ON_STAGING, false);
    }
}
