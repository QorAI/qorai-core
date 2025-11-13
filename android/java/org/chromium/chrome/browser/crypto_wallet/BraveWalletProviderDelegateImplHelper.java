/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.crypto_wallet;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.base.Callback;
import org.chromium.base.Log;
import org.chromium.qorai_wallet.mojom.CoinType;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.settings.QoraiWalletPreferences;
import org.chromium.content_public.browser.WebContents;

/** Helper class for QoraiWalletProviderDelegate implementation. */
@JNINamespace("qorai_wallet")
@SuppressWarnings("unused")
public class QoraiWalletProviderDelegateImplHelper {
    /**
     * A generic 1-argument callback.
     *
     * @param <T1> The type of the first argument.
     */
    public interface Callback1<T1> {
        /** Call the callback. */
        void call(T1 arg1);
    }

    private static final String TAG = "QoraiWalletProvider";

    @CalledByNative
    public static void showPanel() {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.showWalletPanel(false);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showPanel", e);
        }
    }

    @CalledByNative
    public static void unlockWallet() {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.openQoraiWallet(false, false, false);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "unlockWallet", e);
        }
    }

    @CalledByNative
    public static void showWalletBackup() {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.openQoraiWalletBackup();
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showWalletBackup", e);
        }
    }

    @CalledByNative
    public static void showWalletOnboarding() {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.showWalletOnboarding();
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showWalletOnboarding", e);
        }
    }

    @CalledByNative
    public static void walletInteractionDetected(WebContents webContents) {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.walletInteractionDetected(webContents);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "walletInteractionDetected " + e);
        }
    }

    @CalledByNative
    public static boolean isWeb3NotificationAllowed() {
        return QoraiWalletPreferences.getPrefWeb3NotificationsEnabled();
    }

    @CalledByNative
    public static void showAccountCreation(@CoinType.EnumType int coinType) {
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            activity.showAccountCreation(coinType);
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "showAccountCreation " + e);
        }
    }

    public static void isSolanaConnected(
            WebContents webContents, String account, Callback1<Boolean> callback) {
        Callback<Boolean> callbackWrapper =
                result -> {
                    callback.call(result);
                };
        QoraiWalletProviderDelegateImplHelperJni.get()
                .isSolanaConnected(webContents, account, callbackWrapper);
    }

    @NativeMethods
    interface Natives {
        void isSolanaConnected(WebContents webContents, String account, Callback<Boolean> callback);
    }
}
