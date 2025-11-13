/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.qoraiqora;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.ai_chat.mojom.ModelWithSubtitle;
import org.chromium.base.Callback;
import org.chromium.base.Log;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.billing.InAppPurchaseWrapper;
import org.chromium.chrome.browser.billing.PurchaseModel;
import org.chromium.chrome.browser.util.LiveDataUtil;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.content_public.browser.WebContents;

@JNINamespace("ai_chat")
public class QoraiQoraUtils {
    private static final String TAG = "QoraiQoraUtils";

    public static void verifySubscription(Callback callback) {
        MutableLiveData<PurchaseModel> _activePurchases = new MutableLiveData();
        LiveData<PurchaseModel> activePurchases = _activePurchases;
        InAppPurchaseWrapper.getInstance()
                .queryPurchases(_activePurchases, InAppPurchaseWrapper.SubscriptionProduct.QORA);
        LiveDataUtil.observeOnce(
                activePurchases,
                activePurchaseModel -> {
                    QoraiQoraPrefUtils.setIsSubscriptionActive(activePurchaseModel != null);
                    if (activePurchaseModel != null) {
                        QoraiQoraPrefUtils.setChatPackageName();
                        QoraiQoraPrefUtils.setChatProductId(activePurchaseModel.getProductId());
                        QoraiQoraPrefUtils.setChatPurchaseToken(
                                activePurchaseModel.getPurchaseToken());
                    } else {
                        QoraiQoraPrefUtils.setChatProductId("");
                        QoraiQoraPrefUtils.setChatPurchaseToken("");
                    }
                    if (callback != null) {
                        callback.onResult(null);
                    }
                });
    }

    public static void openQoraQuery(
            WebContents webContents,
            String conversationUuid,
            String query,
            boolean openQoraChatWindow) {
        QoraiQoraUtilsJni.get().openQoraQuery(webContents, conversationUuid, query);
    }

    public static void openQoraUrlForTab(WebContents webContents) {
        QoraiQoraUtilsJni.get().openQoraUrlForTab(webContents);
    }

    public static String getDefaultModelName(ModelWithSubtitle[] models, String defaultModelKey) {
        for (ModelWithSubtitle model : models) {
            if (model.model.key.equals(defaultModelKey)) {
                return model.model.displayName;
            }
        }

        return "";
    }

    public static void openManageSubscription() {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            Intent browserIntent =
                    new Intent(
                            Intent.ACTION_VIEW,
                            Uri.parse(InAppPurchaseWrapper.MANAGE_SUBSCRIPTION_PAGE));
            activity.startActivity(browserIntent);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "openManageSubscription get QoraiActivity exception", e);
        }
    }

    public static void goPremium(Activity activity) {
        Intent qoraiQoraPlansIntent = new Intent(activity, QoraiQoraPlansActivity.class);
        qoraiQoraPlansIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        qoraiQoraPlansIntent.setAction(Intent.ACTION_VIEW);
        activity.startActivity(qoraiQoraPlansIntent);
    }

    public static void bringMainActivityOnTop() {
        try {
            TabUtils.bringChromeTabbedActivityToTheTop(QoraiActivity.getQoraiActivity());
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "bringMainActivityOnTop error", e);
        }
    }

    @NativeMethods
    public interface Natives {
        void openQoraQuery(WebContents webContents, String conversationUuid, String query);

        void openQoraUrlForTab(WebContents webContents);
    }
}
