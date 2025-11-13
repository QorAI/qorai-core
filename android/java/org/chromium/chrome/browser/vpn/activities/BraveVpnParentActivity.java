/**
 * Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.vpn.activities;

import android.content.Intent;
import android.os.Handler;
import android.util.Pair;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.wireguard.android.backend.GoBackend;
import com.wireguard.crypto.KeyPair;

import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.billing.InAppPurchaseWrapper;
import org.chromium.chrome.browser.billing.PurchaseModel;
import org.chromium.chrome.browser.init.ActivityProfileProvider;
import org.chromium.chrome.browser.init.AsyncInitializationActivity;
import org.chromium.chrome.browser.profiles.ProfileProvider;
import org.chromium.chrome.browser.util.LiveDataUtil;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.chrome.browser.vpn.QoraiVpnNativeWorker;
import org.chromium.chrome.browser.vpn.QoraiVpnObserver;
import org.chromium.chrome.browser.vpn.models.QoraiVpnPrefModel;
import org.chromium.chrome.browser.vpn.models.QoraiVpnWireguardProfileCredentials;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnApiResponseUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnPrefUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnProfileUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnUtils;
import org.chromium.chrome.browser.vpn.wireguard.WireguardConfigUtils;

import java.util.concurrent.CompletableFuture;

public abstract class QoraiVpnParentActivity extends AsyncInitializationActivity
        implements QoraiVpnObserver {
    private static final String TAG = "QoraiVPN";
    public boolean mIsVerification;
    protected QoraiVpnPrefModel mQoraiVpnPrefModel;
    protected boolean mIsServerLocationChanged;

    private static final int INVALIDATE_CREDENTIAL_TIMER_COUNT = 5000;

    abstract void showRestoreMenu(boolean shouldShowRestore);
    abstract void updateProfileView();

    // Pass @{code ActivityResultRegistry} reference explicitly to avoid crash
    // https://github.com/qorai/qorai-browser/issues/31882
    ActivityResultLauncher<Intent> mIntentActivityResultLauncher =
            registerForActivityResult(
                    new ActivityResultContracts.StartActivityForResult(),
                    getActivityResultRegistry(),
                    result -> {
                        QoraiVpnUtils.dismissProgressDialog();
                        if (result.getResultCode() == RESULT_OK) {
                            QoraiVpnProfileUtils.getInstance()
                                    .startVpn(QoraiVpnParentActivity.this);
                            QoraiVpnUtils.showVpnConfirmDialog(this);
                        } else if (result.getResultCode() == RESULT_CANCELED) {
                            if (QoraiVpnProfileUtils.getInstance().isVPNRunning(this)) {
                                QoraiVpnUtils.showVpnAlwaysOnErrorDialog(this);
                            } else {
                                updateProfileView();
                            }
                            QoraiVpnUtils.showToast(
                                    getResources().getString(R.string.permission_was_cancelled));
                        }
                    });

    @Override
    public void onResumeWithNative() {
        super.onResumeWithNative();
        QoraiVpnNativeWorker.getInstance().addObserver(this);
    }

    @Override
    public void onPauseWithNative() {
        QoraiVpnNativeWorker.getInstance().removeObserver(this);
        super.onPauseWithNative();
    }

    @Override
    public void finishNativeInitialization() {
        super.finishNativeInitialization();
    }

    @Override
    protected void onDestroy() {
        QoraiVpnUtils.dismissProgressDialog();
        super.onDestroy();
    }

    protected void verifySubscription() {
        mQoraiVpnPrefModel = new QoraiVpnPrefModel();
        MutableLiveData<PurchaseModel> _activePurchases = new MutableLiveData();
        LiveData<PurchaseModel> activePurchases = _activePurchases;
        InAppPurchaseWrapper.getInstance()
                .queryPurchases(_activePurchases, InAppPurchaseWrapper.SubscriptionProduct.VPN);
        LiveDataUtil.observeOnce(
                activePurchases,
                activePurchaseModel -> {
                    if (activePurchaseModel != null) {
                        mQoraiVpnPrefModel.setPurchaseToken(activePurchaseModel.getPurchaseToken());
                        mQoraiVpnPrefModel.setProductId(activePurchaseModel.getProductId());
                        QoraiVpnNativeWorker.getInstance()
                                .verifyPurchaseToken(
                                        mQoraiVpnPrefModel.getPurchaseToken(),
                                        mQoraiVpnPrefModel.getProductId(),
                                        QoraiVpnUtils.SUBSCRIPTION_PARAM_TEXT,
                                        getPackageName());
                    } else {
                        if (!mIsVerification) {
                            QoraiVpnApiResponseUtils.queryPurchaseFailed(
                                    QoraiVpnParentActivity.this);
                            mIsServerLocationChanged = false;
                        } else {
                            showRestoreMenu(false);
                        }
                        QoraiVpnUtils.dismissProgressDialog();
                    }
                });
    }

    @Override
    public void onVerifyPurchaseToken(
            String jsonResponse, String purchaseToken, String productId, boolean isSuccess) {
        if (isSuccess && mQoraiVpnPrefModel != null) {
            Long purchaseExpiry = QoraiVpnUtils.getPurchaseExpiryDate(jsonResponse);
            int paymentState = QoraiVpnUtils.getPaymentState(jsonResponse);
            if (purchaseExpiry > 0 && purchaseExpiry >= System.currentTimeMillis()) {
                QoraiVpnPrefUtils.setPurchaseToken(purchaseToken);
                QoraiVpnPrefUtils.setProductId(productId);
                QoraiVpnPrefUtils.setPurchaseExpiry(purchaseExpiry);
                QoraiVpnPrefUtils.setSubscriptionPurchase(true);
                QoraiVpnPrefUtils.setPaymentState(paymentState);
                if (!mIsVerification || QoraiVpnPrefUtils.isResetConfiguration()) {
                    QoraiVpnNativeWorker.getInstance()
                            .getSubscriberCredential(
                                    QoraiVpnUtils.SUBSCRIPTION_PARAM_TEXT,
                                    mQoraiVpnPrefModel.getProductId(),
                                    QoraiVpnUtils.IAP_ANDROID_PARAM_TEXT,
                                    mQoraiVpnPrefModel.getPurchaseToken(),
                                    getPackageName());
                } else {
                    mIsVerification = false;
                    showRestoreMenu(true);
                    QoraiVpnUtils.showToast(getResources().getString(R.string.already_subscribed));
                    QoraiVpnUtils.dismissProgressDialog();
                }
            } else {
                QoraiVpnApiResponseUtils.queryPurchaseFailed(QoraiVpnParentActivity.this);
                mIsServerLocationChanged = false;
                if (mIsVerification) {
                    mIsVerification = false;
                    showRestoreMenu(false);
                    QoraiVpnUtils.dismissProgressDialog();
                } else {
                    QoraiVpnUtils.openQoraiVpnPlansActivity(QoraiVpnParentActivity.this);
                }
            }
        } else {
            QoraiVpnUtils.dismissProgressDialog();
        }
    };

    @Override
    public void onGetSubscriberCredential(String subscriberCredential, boolean isSuccess) {
        mQoraiVpnPrefModel.setSubscriberCredential(subscriberCredential);
        QoraiVpnApiResponseUtils.handleOnGetSubscriberCredential(
                QoraiVpnParentActivity.this, isSuccess);
    };

    @Override
    public void onGetTimezonesForRegions(String jsonTimezones, boolean isSuccess) {
        QoraiVpnApiResponseUtils.handleOnGetTimezonesForRegions(
                QoraiVpnParentActivity.this, mQoraiVpnPrefModel, jsonTimezones, isSuccess);
    }

    @Override
    public void onGetHostnamesForRegion(String jsonHostNames, boolean isSuccess) {
        KeyPair keyPair = new KeyPair();
        mQoraiVpnPrefModel.setClientPrivateKey(keyPair.getPrivateKey().toBase64());
        mQoraiVpnPrefModel.setClientPublicKey(keyPair.getPublicKey().toBase64());
        Pair<String, String> host = QoraiVpnApiResponseUtils.handleOnGetHostnamesForRegion(
                QoraiVpnParentActivity.this, mQoraiVpnPrefModel, jsonHostNames, isSuccess);
        mQoraiVpnPrefModel.setHostname(host.first);
        mQoraiVpnPrefModel.setHostnameDisplay(host.second);
    }

    @Override
    public void onGetWireguardProfileCredentials(
            String jsonWireguardProfileCredentials, boolean isSuccess) {
        if (isSuccess && mQoraiVpnPrefModel != null) {
            QoraiVpnWireguardProfileCredentials qoraiVpnWireguardProfileCredentials =
                    QoraiVpnUtils.getWireguardProfileCredentials(jsonWireguardProfileCredentials);

            int timerCount = 0;
            if (mIsServerLocationChanged) {
                timerCount = INVALIDATE_CREDENTIAL_TIMER_COUNT;
                mIsServerLocationChanged = false;
                try {
                    QoraiVpnNativeWorker.getInstance()
                            .invalidateCredentials(
                                    QoraiVpnPrefUtils.getHostname(),
                                    QoraiVpnPrefUtils.getClientId(),
                                    QoraiVpnPrefUtils.getSubscriberCredential(),
                                    QoraiVpnPrefUtils.getApiAuthToken());
                } catch (Exception ex) {
                    Log.e(TAG, ex.getMessage());
                }
            }

            new Handler()
                    .postDelayed(
                            () -> {
                                checkForVpn(qoraiVpnWireguardProfileCredentials);
                            },
                            timerCount);
        } else {
            QoraiVpnUtils.showToast(getResources().getString(R.string.vpn_profile_creation_failed));
            QoraiVpnUtils.dismissProgressDialog();
        }
    }

    public void changeServerRegion() {
        mIsServerLocationChanged = true;
        QoraiVpnUtils.showProgressDialog(
                QoraiVpnParentActivity.this, getResources().getString(R.string.vpn_connect_text));
        if (QoraiVpnNativeWorker.getInstance().isPurchasedUser()) {
            mQoraiVpnPrefModel = new QoraiVpnPrefModel();
            QoraiVpnNativeWorker.getInstance().getSubscriberCredentialV12();
        } else {
            verifySubscription();
        }
    }

    boolean shouldBringChromeToTop() {
        return !(this instanceof VpnServerSelectionActivity)
                && !(this instanceof VpnServerActivity);
    }

    private void checkForVpn(
            QoraiVpnWireguardProfileCredentials qoraiVpnWireguardProfileCredentials) {
        new Thread() {
            @Override
            public void run() {
                try {
                    if (QoraiVpnProfileUtils.getInstance()
                            .isQoraiVPNConnected(QoraiVpnParentActivity.this)) {
                        QoraiVpnProfileUtils.getInstance().stopVpn(QoraiVpnParentActivity.this);
                    }
                    if (WireguardConfigUtils.isConfigExist(getApplicationContext())) {
                        WireguardConfigUtils.deleteConfig(getApplicationContext());
                    }
                    WireguardConfigUtils.createConfig(
                            getApplicationContext(),
                            qoraiVpnWireguardProfileCredentials.getMappedIpv4Address(),
                            mQoraiVpnPrefModel.getHostname(),
                            mQoraiVpnPrefModel.getClientPrivateKey(),
                            qoraiVpnWireguardProfileCredentials.getServerPublicKey());

                    mQoraiVpnPrefModel.setClientId(
                            qoraiVpnWireguardProfileCredentials.getClientId());
                    mQoraiVpnPrefModel.setApiAuthToken(
                            qoraiVpnWireguardProfileCredentials.getApiAuthToken());
                    CompletableFuture<Void> awaitPrefDone = new CompletableFuture<Void>();
                    ThreadUtils.postOnUiThread(
                            () -> {
                                try {
                                    QoraiVpnPrefUtils.setPrefModel(mQoraiVpnPrefModel);
                                } finally {
                                    awaitPrefDone.complete(null);
                                }
                            });
                    awaitPrefDone.get();
                    QoraiVpnUtils.dismissProgressDialog();
                    Intent intent = GoBackend.VpnService.prepare(QoraiVpnParentActivity.this);
                    if (intent != null) {
                        mIntentActivityResultLauncher.launch(intent);
                        return;
                    }
                    QoraiVpnProfileUtils.getInstance().startVpn(QoraiVpnParentActivity.this);
                    // Only bring Chrome to the top when not in the server selection dialogs
                    // This is needed when user is registering/reactivating their account
                    if (shouldBringChromeToTop()) {
                        TabUtils.bringChromeTabbedActivityToTheTop(QoraiVpnParentActivity.this);
                    }
                } catch (Exception e) {
                    QoraiVpnUtils.dismissProgressDialog();
                    Log.e(TAG, e.getMessage());
                }
            }
        }.start();
    }

    @Override
    protected OneshotSupplier<ProfileProvider> createProfileProvider() {
        return new ActivityProfileProvider(getLifecycleDispatcher());
    }
}
