/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.base.Callback;

import java.time.LocalDateTime;
import java.time.ZoneOffset;

@JNINamespace("chrome::android")
public class QoraiSyncWorker {
    private static final String TAG = "SYNC";

    private long mNativeQoraiSyncWorker;

    private static QoraiSyncWorker sQoraiSyncWorker;
    private static boolean sInitialized;

    public static QoraiSyncWorker get() {
        if (!sInitialized) {
            sQoraiSyncWorker = new QoraiSyncWorker();
            sInitialized = true;
        }
        return sQoraiSyncWorker;
    }

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeQoraiSyncWorker == 0;
        mNativeQoraiSyncWorker = nativePtr;
    }

    private void init() {
        if (mNativeQoraiSyncWorker == 0) {
            QoraiSyncWorkerJni.get().init(QoraiSyncWorker.this);
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
        if (mNativeQoraiSyncWorker != 0) {
            QoraiSyncWorkerJni.get().destroy(mNativeQoraiSyncWorker);
            mNativeQoraiSyncWorker = 0;
        }
    }

    public QoraiSyncWorker() {
        init();
    }

    public String getPureWords() {
        return QoraiSyncWorkerJni.get().getSyncCodeWords(mNativeQoraiSyncWorker);
    }

    public String getTimeLimitedWordsFromPure(String pureWords) {
        return QoraiSyncWorkerJni.get().getTimeLimitedWordsFromPure(pureWords);
    }

    public void saveCodephrase(String codephrase) {
        QoraiSyncWorkerJni.get().saveCodeWords(mNativeQoraiSyncWorker, codephrase);
    }

    public String getSeedHexFromWords(String codephrase) {
        return QoraiSyncWorkerJni.get().getSeedHexFromWords(codephrase);
    }

    public String getWordsFromSeedHex(String seedHex) {
        return QoraiSyncWorkerJni.get().getWordsFromSeedHex(seedHex);
    }

    public String getQrDataJson(String seedHex) {
        return QoraiSyncWorkerJni.get().getQrDataJson(seedHex);
    }

    public int getQrCodeValidationResult(String jsonQr) {
        return QoraiSyncWorkerJni.get().getQrCodeValidationResult(jsonQr);
    }

    public String getSeedHexFromQrJson(String jsonQr) {
        return QoraiSyncWorkerJni.get().getSeedHexFromQrJson(jsonQr);
    }

    public int getWordsValidationResult(String timeLimitedWords) {
        return QoraiSyncWorkerJni.get().getWordsValidationResult(timeLimitedWords);
    }

    public String getPureWordsFromTimeLimited(String timeLimitedWords) {
        return QoraiSyncWorkerJni.get().getPureWordsFromTimeLimited(timeLimitedWords);
    }

    public LocalDateTime getNotAfterFromFromTimeLimitedWords(String timeLimitedWords) {
        long unixTime =
                QoraiSyncWorkerJni.get().getNotAfterFromFromTimeLimitedWords(timeLimitedWords);
        LocalDateTime notAfter = LocalDateTime.ofEpochSecond(unixTime, 0, ZoneOffset.UTC);
        return notAfter;
    }

    public String getFormattedTimeDelta(long seconds) {
        return QoraiSyncWorkerJni.get().getFormattedTimeDelta(seconds);
    }

    public void requestSync() {
        QoraiSyncWorkerJni.get().requestSync(mNativeQoraiSyncWorker);
    }

    public boolean isInitialSyncFeatureSetupComplete() {
        return QoraiSyncWorkerJni.get().isInitialSyncFeatureSetupComplete(mNativeQoraiSyncWorker);
    }

    public void finalizeSyncSetup() {
        QoraiSyncWorkerJni.get().finalizeSyncSetup(mNativeQoraiSyncWorker);
    }

    public void resetSync() {
        QoraiSyncWorkerJni.get().resetSync(mNativeQoraiSyncWorker);
    }

    @CalledByNative
    private static void onPermanentlyDeleteAccountResult(Callback<String> callback, String result) {
        callback.onResult(result);
    }

    public void permanentlyDeleteAccount(Callback<String> callback) {
        QoraiSyncWorkerJni.get().permanentlyDeleteAccount(mNativeQoraiSyncWorker, callback);
    }

    public void clearAccountDeletedNoticePending() {
        QoraiSyncWorkerJni.get().clearAccountDeletedNoticePending(mNativeQoraiSyncWorker);
    }

    public boolean isAccountDeletedNoticePending() {
        return QoraiSyncWorkerJni.get().isAccountDeletedNoticePending(mNativeQoraiSyncWorker);
    }

    @CalledByNative
    private static void onJoinSyncChainResult(Callback<Boolean> callback, Boolean result) {
        callback.onResult(result);
    }

    public void setJoinSyncChainCallback(Callback<Boolean> callback) {
        QoraiSyncWorkerJni.get().setJoinSyncChainCallback(mNativeQoraiSyncWorker, callback);
    }

    public int getWordsCount(String words) {
        return QoraiSyncWorkerJni.get().getWordsCount(words);
    }

    @NativeMethods
    interface Natives {
        void init(QoraiSyncWorker caller);

        void destroy(long nativeQoraiSyncWorker);

        String getSyncCodeWords(long nativeQoraiSyncWorker);

        void requestSync(long nativeQoraiSyncWorker);

        String getSeedHexFromWords(String passphrase);

        String getWordsFromSeedHex(String seedHex);

        String getQrDataJson(String seedHex);

        int getQrCodeValidationResult(String jsonQr);

        String getSeedHexFromQrJson(String jsonQr);

        int getWordsValidationResult(String timeLimitedWords);

        String getPureWordsFromTimeLimited(String timeLimitedWords);

        String getTimeLimitedWordsFromPure(String pureWords);

        long getNotAfterFromFromTimeLimitedWords(String pureWords);

        String getFormattedTimeDelta(long seconds);

        void saveCodeWords(long nativeQoraiSyncWorker, String passphrase);

        int getWordsCount(String words);

        void finalizeSyncSetup(long nativeQoraiSyncWorker);

        boolean isInitialSyncFeatureSetupComplete(long nativeQoraiSyncWorker);

        void resetSync(long nativeQoraiSyncWorker);

        void permanentlyDeleteAccount(long nativeQoraiSyncWorker, Callback<String> callback);
        void clearAccountDeletedNoticePending(long nativeQoraiSyncWorker);
        boolean isAccountDeletedNoticePending(long nativeQoraiSyncWorker);
        void setJoinSyncChainCallback(long nativeQoraiSyncWorker, Callback<Boolean> callback);
    }
}
