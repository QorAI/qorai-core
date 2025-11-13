/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.vpn.utils;

import android.app.Activity;
import android.util.Pair;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import org.chromium.qorai_vpn.mojom.QoraiVpnConstants;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.billing.InAppPurchaseWrapper;
import org.chromium.chrome.browser.billing.PurchaseModel;
import org.chromium.chrome.browser.util.LiveDataUtil;
import org.chromium.chrome.browser.vpn.QoraiVpnNativeWorker;
import org.chromium.chrome.browser.vpn.models.QoraiVpnPrefModel;
import org.chromium.chrome.browser.vpn.models.QoraiVpnServerRegion;

import java.util.TimeZone;

public class QoraiVpnApiResponseUtils {
    public static void queryPurchaseFailed(Activity activity) {
        QoraiVpnPrefUtils.setProductId("");
        QoraiVpnPrefUtils.setPurchaseExpiry(0L);
        QoraiVpnPrefUtils.setSubscriptionPurchase(false);
        QoraiVpnPrefUtils.setPaymentState(0);
        if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(activity)) {
            QoraiVpnProfileUtils.getInstance().stopVpn(activity);
        }
        QoraiVpnUtils.showToast(
                activity.getResources().getString(R.string.purchase_token_verification_failed));
        QoraiVpnUtils.dismissProgressDialog();
    }

    public static void handleOnGetSubscriberCredential(Activity activity, boolean isSuccess) {
        if (isSuccess) {
            if (!QoraiVpnNativeWorker.getInstance().isPurchasedUser()) {
                MutableLiveData<PurchaseModel> _activePurchases = new MutableLiveData();
                LiveData<PurchaseModel> activePurchases = _activePurchases;
                InAppPurchaseWrapper.getInstance()
                        .queryPurchases(
                                _activePurchases, InAppPurchaseWrapper.SubscriptionProduct.VPN);
                LiveDataUtil.observeOnce(activePurchases, activePurchaseModel -> {
                    InAppPurchaseWrapper.getInstance().processPurchases(
                            activity, activePurchaseModel.getPurchase());
                });
            }
            QoraiVpnNativeWorker.getInstance().getTimezonesForRegions();
        } else {
            QoraiVpnUtils.showToast(
                    activity.getResources().getString(R.string.vpn_profile_creation_failed));
            QoraiVpnUtils.dismissProgressDialog();
        }
    }

    public static void handleOnGetTimezonesForRegions(Activity activity,
            QoraiVpnPrefModel qoraiVpnPrefModel, String jsonTimezones, boolean isSuccess) {
        if (isSuccess) {
            QoraiVpnServerRegion qoraiVpnServerRegion =
                    QoraiVpnUtils.getServerRegionForTimeZone(
                            jsonTimezones, TimeZone.getDefault().getID());
            if (qoraiVpnServerRegion == null || qoraiVpnServerRegion.getRegionName().isEmpty()) {
                QoraiVpnUtils.showToast(
                        String.format(
                                activity.getResources()
                                        .getString(R.string.couldnt_get_matching_timezone),
                                TimeZone.getDefault().getID()));
                QoraiVpnUtils.dismissProgressDialog();
                return;
            }
            String regionFromTimeZone = qoraiVpnServerRegion.getRegionName();
            String regionForHostName = regionFromTimeZone;
            String regionPrecision = qoraiVpnServerRegion.getRegionPrecision();

            // Determine the region for host name and precision
            if (QoraiVpnUtils.selectedServerRegion != null) {
                if (!QoraiVpnUtils.selectedServerRegion
                        .getRegionName()
                        .equals(QoraiVpnPrefUtils.PREF_QORAI_VPN_AUTOMATIC)) {
                    regionForHostName = QoraiVpnUtils.selectedServerRegion.getRegionName();
                    qoraiVpnServerRegion = QoraiVpnUtils.selectedServerRegion;
                    regionPrecision = qoraiVpnServerRegion.getRegionPrecision();
                } else {
                    regionPrecision = QoraiVpnConstants.REGION_PRECISION_DEFAULT;
                }
            } else {
                String serverRegion = QoraiVpnPrefUtils.getRegionName();
                if (serverRegion.equals(QoraiVpnPrefUtils.PREF_QORAI_VPN_AUTOMATIC)) {
                    regionPrecision = QoraiVpnConstants.REGION_PRECISION_DEFAULT;
                } else {
                    regionForHostName = serverRegion;
                }
            }
            QoraiVpnNativeWorker.getInstance()
                    .getHostnamesForRegion(regionForHostName, regionPrecision);
            qoraiVpnPrefModel.setServerRegion(qoraiVpnServerRegion);
        } else {
            QoraiVpnUtils.showToast(
                    activity.getResources().getString(R.string.vpn_profile_creation_failed));
            QoraiVpnUtils.dismissProgressDialog();
        }
    }

    public static Pair<String, String> handleOnGetHostnamesForRegion(Activity activity,
            QoraiVpnPrefModel qoraiVpnPrefModel, String jsonHostNames, boolean isSuccess) {
        Pair<String, String> host = new Pair<String, String>("", "");
        if (isSuccess && qoraiVpnPrefModel != null) {
            host = QoraiVpnUtils.getHostnameForRegion(jsonHostNames);
            QoraiVpnNativeWorker.getInstance().getWireguardProfileCredentials(
                    qoraiVpnPrefModel.getSubscriberCredential(),
                    qoraiVpnPrefModel.getClientPublicKey(), host.first);
        } else {
            QoraiVpnUtils.showToast(
                    activity.getResources().getString(R.string.vpn_profile_creation_failed));
            QoraiVpnUtils.dismissProgressDialog();
        }
        return host;
    }
}
