/**
 * Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.vpn;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import java.util.ArrayList;
import java.util.List;

@JNINamespace("chrome::android")
public class QoraiVpnNativeWorker {
    private long mNativeQoraiVpnNativeWorker;
    private static final Object sLock = new Object();
    private static QoraiVpnNativeWorker sInstance;

    private final List<QoraiVpnObserver> mObservers;

    public static QoraiVpnNativeWorker getInstance() {
        synchronized (sLock) {
            if (sInstance == null) {
                sInstance = new QoraiVpnNativeWorker();
                sInstance.init();
            }
        }
        return sInstance;
    }

    private QoraiVpnNativeWorker() {
        mObservers = new ArrayList<QoraiVpnObserver>();
    }

    private void init() {
        if (mNativeQoraiVpnNativeWorker == 0) {
            QoraiVpnNativeWorkerJni.get().init(this);
        }
    }

    /**
     * A finalizer is required to ensure that the native object associated with this descriptor gets
     * torn down, otherwise there would be a memory leak.
     */
    @SuppressWarnings("Finalize")
    @Override
    protected void finalize() {
        destroy();
    }

    private void destroy() {
        if (mNativeQoraiVpnNativeWorker != 0) {
            QoraiVpnNativeWorkerJni.get().destroy(mNativeQoraiVpnNativeWorker, this);
            mNativeQoraiVpnNativeWorker = 0;
        }
    }

    public void addObserver(QoraiVpnObserver observer) {
        synchronized (sLock) {
            mObservers.add(observer);
        }
    }

    public void removeObserver(QoraiVpnObserver observer) {
        synchronized (sLock) {
            mObservers.remove(observer);
        }
    }

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeQoraiVpnNativeWorker == 0;
        mNativeQoraiVpnNativeWorker = nativePtr;
    }

    @CalledByNative
    public void onGetTimezonesForRegions(String jsonTimezones, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onGetTimezonesForRegions(jsonTimezones, isSuccess);
        }
    }

    @CalledByNative
    public void onGetHostnamesForRegion(String jsonHostnames, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onGetHostnamesForRegion(jsonHostnames, isSuccess);
        }
    }

    @CalledByNative
    public void onGetWireguardProfileCredentials(
            String jsonWireguardProfileCredentials, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onGetWireguardProfileCredentials(jsonWireguardProfileCredentials, isSuccess);
        }
    }

    @CalledByNative
    public void onVerifyCredentials(String jsonVerifyCredentials, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onVerifyCredentials(jsonVerifyCredentials, isSuccess);
        }
    }

    @CalledByNative
    public void onInvalidateCredentials(String jsonInvalidateCredentials, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onInvalidateCredentials(jsonInvalidateCredentials, isSuccess);
        }
    }

    @CalledByNative
    public void onGetSubscriberCredential(String subscriberCredential, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onGetSubscriberCredential(subscriberCredential, isSuccess);
        }
    }

    @CalledByNative
    public void onVerifyPurchaseToken(
            String jsonResponse, String purchaseToken, String productId, boolean isSuccess) {
        for (QoraiVpnObserver observer : mObservers) {
            observer.onVerifyPurchaseToken(jsonResponse, purchaseToken, productId, isSuccess);
        }
    }

    public void getTimezonesForRegions() {
        QoraiVpnNativeWorkerJni.get().getTimezonesForRegions(mNativeQoraiVpnNativeWorker);
    }

    public void getHostnamesForRegion(String region, String regionPrecision) {
        QoraiVpnNativeWorkerJni.get()
                .getHostnamesForRegion(mNativeQoraiVpnNativeWorker, region, regionPrecision);
    }

    public void getWireguardProfileCredentials(
            String subscriberCredential, String publicKey, String hostname) {
        QoraiVpnNativeWorkerJni.get().getWireguardProfileCredentials(
                mNativeQoraiVpnNativeWorker, subscriberCredential, publicKey, hostname);
    }

    public void verifyCredentials(
            String hostname, String clientId, String subscriberCredential, String apiAuthToken) {
        QoraiVpnNativeWorkerJni.get().verifyCredentials(mNativeQoraiVpnNativeWorker, hostname,
                clientId, subscriberCredential, apiAuthToken);
    }

    public void invalidateCredentials(
            String hostname, String clientId, String subscriberCredential, String apiAuthToken) {
        QoraiVpnNativeWorkerJni.get().invalidateCredentials(mNativeQoraiVpnNativeWorker, hostname,
                clientId, subscriberCredential, apiAuthToken);
    }

    public void getSubscriberCredential(String productType, String productId,
            String validationMethod, String purchaseToken, String packageName) {
        QoraiVpnNativeWorkerJni.get().getSubscriberCredential(mNativeQoraiVpnNativeWorker,
                productType, productId, validationMethod, purchaseToken, packageName);
    }

    public void verifyPurchaseToken(
            String purchaseToken, String productId, String productType, String packageName) {
        QoraiVpnNativeWorkerJni.get().verifyPurchaseToken(
                mNativeQoraiVpnNativeWorker, purchaseToken, productId, productType, packageName);
    }

    // Desktop purchase methods
    public void reloadPurchasedState() {
        QoraiVpnNativeWorkerJni.get().reloadPurchasedState(mNativeQoraiVpnNativeWorker);
    }

    public boolean isPurchasedUser() {
        return QoraiVpnNativeWorkerJni.get().isPurchasedUser(mNativeQoraiVpnNativeWorker);
    }

    public void getSubscriberCredentialV12() {
        QoraiVpnNativeWorkerJni.get().getSubscriberCredentialV12(mNativeQoraiVpnNativeWorker);
    }

    public void reportBackgroundP3A(long sessionStartTimeMs, long sessionEndTimeMs) {
        QoraiVpnNativeWorkerJni.get().reportBackgroundP3A(
                mNativeQoraiVpnNativeWorker, sessionStartTimeMs, sessionEndTimeMs);
    }

    public void reportForegroundP3A() {
        QoraiVpnNativeWorkerJni.get().reportForegroundP3A(mNativeQoraiVpnNativeWorker);
    }

    @NativeMethods
    interface Natives {
        void init(QoraiVpnNativeWorker caller);

        void destroy(long nativeQoraiVpnNativeWorker, QoraiVpnNativeWorker caller);

        void getTimezonesForRegions(long nativeQoraiVpnNativeWorker);

        void getHostnamesForRegion(
                long nativeQoraiVpnNativeWorker, String region, String regionPrecision);

        void getWireguardProfileCredentials(
                long nativeQoraiVpnNativeWorker,
                String subscriberCredential,
                String publicKey,
                String hostname);

        void verifyCredentials(
                long nativeQoraiVpnNativeWorker,
                String hostname,
                String clientId,
                String subscriberCredential,
                String apiAuthToken);

        void invalidateCredentials(
                long nativeQoraiVpnNativeWorker,
                String hostname,
                String clientId,
                String subscriberCredential,
                String apiAuthToken);

        void getSubscriberCredential(
                long nativeQoraiVpnNativeWorker,
                String productType,
                String productId,
                String validationMethod,
                String purchaseToken,
                String packageName);

        void verifyPurchaseToken(
                long nativeQoraiVpnNativeWorker,
                String purchaseToken,
                String productId,
                String productType,
                String packageName);

        void reloadPurchasedState(long nativeQoraiVpnNativeWorker);

        boolean isPurchasedUser(long nativeQoraiVpnNativeWorker);

        void getSubscriberCredentialV12(long nativeQoraiVpnNativeWorker);

        void reportBackgroundP3A(
                long nativeQoraiVpnNativeWorker, long sessionStartTimeMs, long sessionEndTimeMs);

        void reportForegroundP3A(long nativeQoraiVpnNativeWorker);
    }
}
