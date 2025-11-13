/**
 * Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser;

import android.os.Handler;

import androidx.annotation.Nullable;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;
import org.json.JSONException;

import org.chromium.qorai_rewards.mojom.PublisherStatus;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.components.embedder_support.util.UrlConstants;

import java.util.ArrayList;
import java.util.List;

@JNINamespace("chrome::android")
public class QoraiRewardsNativeWorker {
    /** Allows to monitor a front tab publisher changes. */
    public interface PublisherObserver {
        void onFrontTabPublisherChanged(boolean verified, String publisherId);
    }

    // Rewards notifications
    // Taken from components/qorai_rewards/content/rewards_notification_service.h
    public static final int REWARDS_NOTIFICATION_INVALID = 0;
    public static final int REWARDS_NOTIFICATION_AUTO_CONTRIBUTE = 1;
    public static final int REWARDS_NOTIFICATION_FAILED_CONTRIBUTION = 4;
    public static final int REWARDS_NOTIFICATION_IMPENDING_CONTRIBUTION = 5;
    public static final int REWARDS_NOTIFICATION_TIPS_PROCESSED = 8;
    public static final int REWARDS_NOTIFICATION_ADS_ONBOARDING = 9;
    public static final int REWARDS_NOTIFICATION_VERIFIED_PUBLISHER = 10;
    public static final int REWARDS_NOTIFICATION_PENDING_NOT_ENOUGH_FUNDS = 11;
    public static final int REWARDS_NOTIFICATION_GENERAL = 12;

    public static final int OK = 0;
    public static final int FAILED = 1;
    public static final int QOR_NOT_ALLOWED = 25;
    public static final int SAFETYNET_ATTESTATION_FAILED = 27;

    private String mFrontTabUrl;
    private static final Handler sHandler = new Handler();

    private final List<QoraiRewardsObserver> mObservers;
    private final List<PublisherObserver> mFrontTabPublisherObservers;
    private long mNativeQoraiRewardsNativeWorker;

    private static QoraiRewardsNativeWorker sInstance;
    private static final Object sLock = new Object();

    public static QoraiRewardsNativeWorker getInstance() {
        synchronized (sLock) {
            if (sInstance == null) {
                sInstance = new QoraiRewardsNativeWorker();
                sInstance.init();
          }
        }
        return sInstance;
    }

    private QoraiRewardsNativeWorker() {
        mObservers = new ArrayList<QoraiRewardsObserver>();
        mFrontTabPublisherObservers = new ArrayList<PublisherObserver>();
    }

    private void init() {
      if (mNativeQoraiRewardsNativeWorker == 0) {
          QoraiRewardsNativeWorkerJni.get().init(QoraiRewardsNativeWorker.this);
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
        if (mNativeQoraiRewardsNativeWorker != 0) {
            QoraiRewardsNativeWorkerJni.get().destroy(mNativeQoraiRewardsNativeWorker);
            mNativeQoraiRewardsNativeWorker = 0;
        }
    }

    public void addObserver(QoraiRewardsObserver observer) {
        synchronized (sLock) {
            mObservers.add(observer);
        }
    }

    public void removeObserver(QoraiRewardsObserver observer) {
        synchronized (sLock) {
            mObservers.remove(observer);
        }
    }

    public void addPublisherObserver(PublisherObserver observer) {
        synchronized (sLock) {
            mFrontTabPublisherObservers.add(observer);
        }
    }

    public void removePublisherObserver(PublisherObserver observer) {
        synchronized (sLock) {
            mFrontTabPublisherObservers.remove(observer);
        }
    }

    public void onNotifyFrontTabUrlChanged(int tabId, String url) {
        boolean chromeUrl = url.startsWith(UrlConstants.CHROME_SCHEME);
        boolean newUrl = (mFrontTabUrl == null || !mFrontTabUrl.equals(url));
        if (chromeUrl) {
            // Don't query 'GetPublisherInfo' and post response now.
            sHandler.post(
                    new Runnable() {
                        @Override
                        public void run() {
                            notifyPublisherObservers(false, "");
                        }
                    });
        } else if (newUrl) {
            getPublisherInfo(tabId, url);
        }

        mFrontTabUrl = url;
    }

    private void notifyPublisherObservers(boolean verified, String publisherId) {
        for (PublisherObserver observer : mFrontTabPublisherObservers) {
            observer.onFrontTabPublisherChanged(verified, publisherId);
        }
    }

    public void triggerOnNotifyFrontTabUrlChanged() {
        // Clear mFrontTabUrl so that all observers are updated.
        mFrontTabUrl = "";
        sHandler.post(
                new Runnable() {
                    @Override
                    public void run() {
                        Tab tab = QoraiRewardsHelper.currentActiveChromeTabbedActivityTab();
                        if (tab != null && !tab.isIncognito()) {
                            onNotifyFrontTabUrlChanged(tab.getId(), tab.getUrl().getSpec());
                        }
                    }
                });
    }

    public boolean isSupported() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().isSupported(mNativeQoraiRewardsNativeWorker);
        }
    }

    public boolean isSupportedSkipRegionCheck() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().isSupportedSkipRegionCheck(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public boolean isRewardsEnabled() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().isRewardsEnabled(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public boolean shouldShowSelfCustodyInvite() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get()
                    .shouldShowSelfCustodyInvite(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void createRewardsWallet(String countryCode) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().createRewardsWallet(
                    mNativeQoraiRewardsNativeWorker, countryCode);
        }
    }

    public void getRewardsParameters() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getRewardsParameters(mNativeQoraiRewardsNativeWorker);
        }
    }

    public double getVbatDeadline() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getVbatDeadline(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public void getUserType() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getUserType(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void fetchBalance() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().fetchBalance(mNativeQoraiRewardsNativeWorker);
        }
    }

    @Nullable
    public QoraiRewardsBalance getWalletBalance() {
        synchronized (sLock) {
            String json = QoraiRewardsNativeWorkerJni.get().getWalletBalance(
                    mNativeQoraiRewardsNativeWorker);
            QoraiRewardsBalance balance = null;
            try{
                balance = new QoraiRewardsBalance(json);
            }
            catch (JSONException e) {
                balance = null;
            }
            return balance;
        }
    }

    public String getExternalWalletType() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getExternalWalletType(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public boolean canConnectAccount() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().canConnectAccount(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public double[] getTipChoices() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getTipChoices(mNativeQoraiRewardsNativeWorker);
        }
    }

    public double getWalletRate() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getWalletRate(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void getPublisherInfo(int tabId, String host) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getPublisherInfo(
                    mNativeQoraiRewardsNativeWorker, tabId, host);
        }
    }

    public String getPublisherURL(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherURL(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public String getCaptchaSolutionURL(String paymentId, String captchaId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getCaptchaSolutionURL(
                    mNativeQoraiRewardsNativeWorker, paymentId, captchaId);
        }
    }

    public String getAttestationURL() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getAttestationURL(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public String getAttestationURLWithPaymentId(String paymentId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getAttestationURLWithPaymentId(
                    mNativeQoraiRewardsNativeWorker, paymentId);
        }
    }

    public String getPublisherFavIconURL(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherFavIconURL(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public String getPublisherName(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherName(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public String getPublisherId(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherId(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public int getPublisherPercent(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherPercent(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public boolean getPublisherExcluded(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherExcluded(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public int getPublisherStatus(int tabId) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherStatus(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public void removePublisherFromMap(int tabId) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().removePublisherFromMap(
                    mNativeQoraiRewardsNativeWorker, tabId);
        }
    }

    public void getCurrentBalanceReport() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getCurrentBalanceReport(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public void donate(String publisherKey, double amount, boolean recurring) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get()
                    .donate(mNativeQoraiRewardsNativeWorker, publisherKey, amount, recurring);
        }
    }

    public void getAllNotifications() {
        sHandler.post(
                new Runnable() {
                    @Override
                    public void run() {
                        synchronized (sLock) {
                            QoraiRewardsNativeWorkerJni.get()
                                    .getAllNotifications(mNativeQoraiRewardsNativeWorker);
                        }
                    }
                });
    }

    public void deleteNotification(String notificationId) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get()
                    .deleteNotification(mNativeQoraiRewardsNativeWorker, notificationId);
        }
    }

    public void getRecurringDonations() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getRecurringDonations(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public boolean isCurrentPublisherInRecurrentDonations(String publisher) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().isCurrentPublisherInRecurrentDonations(
                    mNativeQoraiRewardsNativeWorker, publisher);
        }
    }

    public double getPublisherRecurrentDonationAmount(String publisher) {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPublisherRecurrentDonationAmount(
                    mNativeQoraiRewardsNativeWorker, publisher);
        }
    }

    public void getReconcileStamp() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getReconcileStamp(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void removeRecurring(String publisher) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().removeRecurring(
                    mNativeQoraiRewardsNativeWorker, publisher);
        }
    }

    public void resetTheWholeState() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().resetTheWholeState(mNativeQoraiRewardsNativeWorker);
        }
    }

    public int getAdsPerHour() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getAdsPerHour(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void setAdsPerHour(int value) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().setAdsPerHour(mNativeQoraiRewardsNativeWorker, value);
        }
    }

    public void getExternalWallet() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getExternalWallet(mNativeQoraiRewardsNativeWorker);
        }
    }

    public boolean isTermsOfServiceUpdateRequired() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get()
                    .isTermsOfServiceUpdateRequired(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void acceptTermsOfServiceUpdate() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get()
                    .acceptTermsOfServiceUpdate(mNativeQoraiRewardsNativeWorker);
        }
    }

    public String getCountryCode() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getCountryCode(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public void getAvailableCountries() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getAvailableCountries(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    public void getPublisherBanner(String publisherKey) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get()
                    .getPublisherBanner(mNativeQoraiRewardsNativeWorker, publisherKey);
        }
    }

    public void getPublishersVisitedCount() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getPublishersVisitedCount(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    @CalledByNative
    public void onGetPublishersVisitedCount(int count) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetPublishersVisitedCount(count);
        }
    }

    public void disconnectWallet() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().disconnectWallet(mNativeQoraiRewardsNativeWorker);
        }
    }

    public void getAdsAccountStatement() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().getAdsAccountStatement(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    @CalledByNative
    public void onCreateRewardsWallet(String result) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onCreateRewardsWallet(result);
        }
    }

    public void refreshPublisher(String publisherKey) {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().refreshPublisher(
                    mNativeQoraiRewardsNativeWorker, publisherKey);
        }
    }

    public void recordPanelTrigger() {
        synchronized (sLock) {
            QoraiRewardsNativeWorkerJni.get().recordPanelTrigger(mNativeQoraiRewardsNativeWorker);
        }
    }

    public String getPayoutStatus() {
        synchronized (sLock) {
            return QoraiRewardsNativeWorkerJni.get().getPayoutStatus(
                    mNativeQoraiRewardsNativeWorker);
        }
    }

    @CalledByNative
    public void onRefreshPublisher(int status, String publisherKey) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onRefreshPublisher(status, publisherKey);
        }
    }

    @CalledByNative
    public void onRewardsParameters() {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onRewardsParameters();
        }
    }

    @CalledByNative
    public void onTermsOfServiceUpdateAccepted() {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onTermsOfServiceUpdateAccepted();
        }
    }

    @CalledByNative
    public void onBalance(boolean success) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onBalance(success);
        }
    }

    @CalledByNative
    public void onGetCurrentBalanceReport(double[] report) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetCurrentBalanceReport(report);
        }
    }

    @CalledByNative
    private void setNativePtr(long nativePtr) {
        assert mNativeQoraiRewardsNativeWorker == 0;
        mNativeQoraiRewardsNativeWorker = nativePtr;
    }

    @CalledByNative
    public void onPublisherInfo(int tabId, String publisherId) {
        int pubStatus = getPublisherStatus(tabId);
        boolean verified = pubStatus != PublisherStatus.NOT_VERIFIED;
        notifyPublisherObservers(verified, publisherId);

        // Notify QoraiRewardsObserver (panel).
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onPublisherInfo(tabId);
        }
    }

    @CalledByNative
    public void onNotificationAdded(String id, int type, long timestamp, String[] args) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onNotificationAdded(id, type, timestamp, args);
        }
    }

    @CalledByNative
    public void onNotificationsCount(int count) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onNotificationsCount(count);
        }
    }

    @CalledByNative
    public void onGetLatestNotification(String id, int type, long timestamp, String[] args) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetLatestNotification(id, type, timestamp, args);
        }
    }

    @CalledByNative
    public void onNotificationDeleted(String id) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onNotificationDeleted(id);
        }
    }

    @CalledByNative
    public void onGetReconcileStamp(long timestamp) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetReconcileStamp(timestamp);
        }
    }

    @CalledByNative
    public void onRecurringDonationUpdated() {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onRecurringDonationUpdated();
        }
    }

    @CalledByNative
    public void onCompleteReset(boolean success) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onCompleteReset(success);
        }
    }

    @CalledByNative
    public void onResetTheWholeState(boolean success) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onResetTheWholeState(success);
        }
    }

    @CalledByNative
    public void onGetExternalWallet(String externalWallet) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetExternalWallet(externalWallet);
        }
    }

    @CalledByNative
    public void onGetAvailableCountries(String[] countries) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetAvailableCountries(countries);
        }
    }

    @CalledByNative
    public void onGetAdsAccountStatement(
            boolean success,
            double nextPaymentDate,
            int adsReceivedThisMonth,
            double minEarningsThisMonth,
            double maxEarningsThisMonth,
            double minEarningsLastMonth,
            double maxEarningsLastMonth) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetAdsAccountStatement(
                    success,
                    nextPaymentDate,
                    adsReceivedThisMonth,
                    minEarningsThisMonth,
                    maxEarningsThisMonth,
                    minEarningsLastMonth,
                    maxEarningsLastMonth);
        }
    }

    @CalledByNative
    public void onExternalWalletConnected() {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onExternalWalletConnected();
        }
    }

    @CalledByNative
    public void onExternalWalletLoggedOut() {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onExternalWalletLoggedOut();
        }
    }

    @CalledByNative
    public void onExternalWalletReconnected() {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onExternalWalletReconnected();
        }
    }

    @CalledByNative
    public void onSendContribution(boolean result) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onSendContribution(result);
        }
    }

    @CalledByNative
    public void onReconcileComplete(int resultCode, int rewardsType, double amount) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onReconcileComplete(resultCode, rewardsType, amount);
        }
    }

    @CalledByNative
    public void onPublisherBanner(String jsonBannerInfo) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onPublisherBanner(jsonBannerInfo);
        }
    }

    @CalledByNative
    public void onGetUserType(int userType) {
        for (QoraiRewardsObserver observer : mObservers) {
            observer.onGetUserType(userType);
        }
    }

    @NativeMethods
    interface Natives {
        void init(QoraiRewardsNativeWorker caller);
        void destroy(long nativeQoraiRewardsNativeWorker);
        boolean isSupported(long nativeQoraiRewardsNativeWorker);
        boolean isSupportedSkipRegionCheck(long nativeQoraiRewardsNativeWorker);
        boolean isRewardsEnabled(long nativeQoraiRewardsNativeWorker);

        boolean shouldShowSelfCustodyInvite(long nativeQoraiRewardsNativeWorker);

        String getWalletBalance(long nativeQoraiRewardsNativeWorker);
        String getExternalWalletType(long nativeQoraiRewardsNativeWorker);

        void getPublisherBanner(long nativeQoraiRewardsNativeWorker, String publisherKey);

        void getPublishersVisitedCount(long nativeQoraiRewardsNativeWorker);
        boolean canConnectAccount(long nativeQoraiRewardsNativeWorker);

        double[] getTipChoices(long nativeQoraiRewardsNativeWorker);

        double getWalletRate(long nativeQoraiRewardsNativeWorker);

        void getPublisherInfo(long nativeQoraiRewardsNativeWorker, int tabId, String host);

        String getPublisherURL(long nativeQoraiRewardsNativeWorker, int tabId);

        String getCaptchaSolutionURL(
                long nativeQoraiRewardsNativeWorker, String paymentId, String captchaId);

        String getAttestationURL(long nativeQoraiRewardsNativeWorker);

        String getAttestationURLWithPaymentId(
                long nativeQoraiRewardsNativeWorker, String paymentId);

        String getPublisherFavIconURL(long nativeQoraiRewardsNativeWorker, int tabId);

        String getPublisherName(long nativeQoraiRewardsNativeWorker, int tabId);

        String getPublisherId(long nativeQoraiRewardsNativeWorker, int tabId);

        int getPublisherPercent(long nativeQoraiRewardsNativeWorker, int tabId);

        boolean getPublisherExcluded(long nativeQoraiRewardsNativeWorker, int tabId);

        int getPublisherStatus(long nativeQoraiRewardsNativeWorker, int tabId);

        void removePublisherFromMap(long nativeQoraiRewardsNativeWorker, int tabId);

        void getCurrentBalanceReport(long nativeQoraiRewardsNativeWorker);

        void donate(
                long nativeQoraiRewardsNativeWorker,
                String publisherKey,
                double amount,
                boolean recurring);

        void getAllNotifications(long nativeQoraiRewardsNativeWorker);

        void deleteNotification(long nativeQoraiRewardsNativeWorker, String notificationId);

        void getRecurringDonations(long nativeQoraiRewardsNativeWorker);

        boolean isCurrentPublisherInRecurrentDonations(
                long nativeQoraiRewardsNativeWorker, String publisher);

        void getReconcileStamp(long nativeQoraiRewardsNativeWorker);

        double getPublisherRecurrentDonationAmount(
                long nativeQoraiRewardsNativeWorker, String publisher);

        void removeRecurring(long nativeQoraiRewardsNativeWorker, String publisher);

        void resetTheWholeState(long nativeQoraiRewardsNativeWorker);

        int getAdsPerHour(long nativeQoraiRewardsNativeWorker);

        void setAdsPerHour(long nativeQoraiRewardsNativeWorker, int value);

        void getExternalWallet(long nativeQoraiRewardsNativeWorker);

        boolean isTermsOfServiceUpdateRequired(long nativeQoraiRewardsNativeWorker);

        void acceptTermsOfServiceUpdate(long nativeQoraiRewardsNativeWorker);

        String getCountryCode(long nativeQoraiRewardsNativeWorker);
        void getAvailableCountries(long nativeQoraiRewardsNativeWorker);
        void disconnectWallet(long nativeQoraiRewardsNativeWorker);
        void refreshPublisher(long nativeQoraiRewardsNativeWorker, String publisherKey);

        void recordPanelTrigger(long nativeQoraiRewardsNativeWorker);

        void createRewardsWallet(long nativeQoraiRewardsNativeWorker, String countryCode);

        void getRewardsParameters(long nativeQoraiRewardsNativeWorker);

        double getVbatDeadline(long nativeQoraiRewardsNativeWorker);

        void getUserType(long nativeQoraiRewardsNativeWorker);

        void fetchBalance(long nativeQoraiRewardsNativeWorker);

        void getAdsAccountStatement(long nativeQoraiRewardsNativeWorker);

        String getPayoutStatus(long nativeQoraiRewardsNativeWorker);
    }
}
