/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.vpn.settings;

import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.Uri;
import android.os.Bundle;
import android.util.Pair;

import androidx.appcompat.app.AlertDialog;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.preference.Preference;
import androidx.preference.PreferenceCategory;

import com.wireguard.android.backend.GoBackend;
import com.wireguard.crypto.KeyPair;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.Log;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.task.PostTask;
import org.chromium.base.task.TaskTraits;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.InternetConnection;
import org.chromium.chrome.browser.billing.InAppPurchaseWrapper;
import org.chromium.chrome.browser.billing.LinkSubscriptionUtils;
import org.chromium.chrome.browser.billing.PurchaseModel;
import org.chromium.chrome.browser.customtabs.CustomTabActivity;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.settings.QoraiPreferenceFragment;
import org.chromium.chrome.browser.util.LiveDataUtil;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.chrome.browser.vpn.QoraiVpnNativeWorker;
import org.chromium.chrome.browser.vpn.QoraiVpnObserver;
import org.chromium.chrome.browser.vpn.models.QoraiVpnPrefModel;
import org.chromium.chrome.browser.vpn.models.QoraiVpnWireguardProfileCredentials;
import org.chromium.chrome.browser.vpn.timer.TimerDialogFragment;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnApiResponseUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnPrefUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnProfileUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnUtils;
import org.chromium.chrome.browser.vpn.wireguard.WireguardConfigUtils;
import org.chromium.components.browser_ui.settings.ChromeBasePreference;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;
import org.chromium.ui.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class QoraiVpnPreferences extends QoraiPreferenceFragment implements QoraiVpnObserver {
    private static final String TAG = "QoraiVPN";
    public static final String PREF_VPN_SWITCH = "vpn_switch";
    public static final String PREF_SUBSCRIPTION_MANAGE = "subscription_manage";
    public static final String PREF_LINK_SUBSCRIPTION = "link_subscription";
    public static final String PREF_SUBSCRIPTION_STATUS = "subscription_status";
    public static final String PREF_SUBSCRIPTION_EXPIRES = "subscription_expires";
    public static final String PREF_SERVER_CHANGE_LOCATION = "server_change_location";
    public static final String PREF_SUPPORT_TECHNICAL = "support_technical";
    public static final String PREF_SUPPORT_VPN = "support_vpn";
    public static final String PREF_SERVER_RESET_CONFIGURATION = "server_reset_configuration";
    private static final String PREF_SPLIT_TUNNELING = "split_tunneling";
    private static final String PREF_AUTO_RECONNECT_VPN = "auto_reconnect_vpn";
    private static final String PREF_QORAI_VPN_SUBSCRIPTION_SECTION =
            "qorai_vpn_subscription_section";

    private static final int INVALIDATE_CREDENTIAL_TIMER_COUNT = 5000;

    private static final String VPN_SUPPORT_PAGE =
            "https://support.qorai.app/hc/en-us/articles/4410838268429";

    private static final String DATE_FORMAT = "dd/MM/yyyy";

    private ChromeSwitchPreference mVpnSwitch;
    private ChromeBasePreference mSubscriptionStatus;
    private ChromeBasePreference mSubscriptionExpires;
    private ChromeBasePreference mLinkSubscriptionPreference;
    private QoraiVpnPrefModel mQoraiVpnPrefModel;
    private final ObservableSupplierImpl<String> mPageTitle = new ObservableSupplierImpl<>();

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        mPageTitle.set(getString(R.string.qorai_firewall_vpn));
        SettingsUtils.addPreferencesFromResource(this, R.xml.qorai_vpn_preferences);

        mVpnSwitch = (ChromeSwitchPreference) findPreference(PREF_VPN_SWITCH);
        mVpnSwitch.setChecked(
                QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(getActivity()));
        mVpnSwitch.setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
            @Override
            public boolean onPreferenceClick(Preference preference) {
                if (mVpnSwitch != null) {
                    mVpnSwitch.setChecked(
                            QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(getActivity()));
                }
                if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(getActivity())) {
                    TimerDialogFragment timerDialogFragment = new TimerDialogFragment();
                    timerDialogFragment.show(
                            getActivity().getSupportFragmentManager(), TimerDialogFragment.TAG);
                } else {
                    if (QoraiVpnNativeWorker.getInstance().isPurchasedUser()) {
                        QoraiVpnPrefUtils.setSubscriptionPurchase(true);
                        if (WireguardConfigUtils.isConfigExist(getActivity())) {
                            QoraiVpnProfileUtils.getInstance().startVpn(getActivity());
                        } else {
                            QoraiVpnUtils.openQoraiVpnProfileActivity(getActivity());
                        }
                    } else {
                        QoraiVpnUtils.showProgressDialog(
                                getActivity(), getResources().getString(R.string.vpn_connect_text));
                        if (QoraiVpnPrefUtils.isSubscriptionPurchase()) {
                            verifyPurchase(true);
                        } else {
                            QoraiVpnUtils.openQoraiVpnPlansActivity(getActivity());
                            QoraiVpnUtils.dismissProgressDialog();
                        }
                    }
                }
                return false;
            }
        });

        mSubscriptionStatus = (ChromeBasePreference) findPreference(PREF_SUBSCRIPTION_STATUS);
        mSubscriptionExpires = (ChromeBasePreference) findPreference(PREF_SUBSCRIPTION_EXPIRES);

        findPreference(PREF_SUPPORT_TECHNICAL)
                .setOnPreferenceClickListener(
                        new Preference.OnPreferenceClickListener() {
                            @Override
                            public boolean onPreferenceClick(Preference preference) {
                                QoraiVpnUtils.openQoraiVpnSupportActivity(getActivity());
                                return true;
                            }
                        });

        findPreference(PREF_SUPPORT_VPN)
                .setOnPreferenceClickListener(
                        new Preference.OnPreferenceClickListener() {
                            @Override
                            public boolean onPreferenceClick(Preference preference) {
                                CustomTabActivity.showInfoPage(getActivity(), VPN_SUPPORT_PAGE);
                                return true;
                            }
                        });

        findPreference(PREF_SUBSCRIPTION_MANAGE)
                .setOnPreferenceClickListener(
                        new Preference.OnPreferenceClickListener() {
                            @Override
                            public boolean onPreferenceClick(Preference preference) {
                                Intent browserIntent =
                                        new Intent(
                                                Intent.ACTION_VIEW,
                                                Uri.parse(
                                                        InAppPurchaseWrapper
                                                                .MANAGE_SUBSCRIPTION_PAGE));
                                getActivity().startActivity(browserIntent);
                                return true;
                            }
                        });

        findPreference(PREF_SERVER_RESET_CONFIGURATION)
                .setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
                    @Override
                    public boolean onPreferenceClick(Preference preference) {
                        showConfirmDialog();
                        return true;
                    }
                });

        findPreference(PREF_SPLIT_TUNNELING)
                .setOnPreferenceClickListener(
                        new Preference.OnPreferenceClickListener() {
                            @Override
                            public boolean onPreferenceClick(Preference preference) {
                                QoraiVpnUtils.openSplitTunnelActivity(getActivity());
                                return true;
                            }
                        });
        findPreference(PREF_AUTO_RECONNECT_VPN)
                .setOnPreferenceClickListener(
                        new Preference.OnPreferenceClickListener() {
                            @Override
                            public boolean onPreferenceClick(Preference preference) {
                                QoraiVpnUtils.openAutoReconnectVpnActivity(getActivity());
                                return true;
                            }
                        });
        mLinkSubscriptionPreference = new ChromeBasePreference(getActivity());
        mLinkSubscriptionPreference.setTitle(
                getResources().getString(R.string.link_subscription_title));
        mLinkSubscriptionPreference.setSummary(
                getResources().getString(R.string.link_subscription_text));
        mLinkSubscriptionPreference.setKey(PREF_LINK_SUBSCRIPTION);
        mLinkSubscriptionPreference.setVisible(
                ChromeFeatureList.isEnabled(QoraiFeatureList.QORAI_VPN_LINK_SUBSCRIPTION_ANDROID_UI)
                && QoraiVpnPrefUtils.isSubscriptionPurchase());
        mLinkSubscriptionPreference.setOnPreferenceClickListener(
                new Preference.OnPreferenceClickListener() {
                    @Override
                    public boolean onPreferenceClick(Preference preference) {
                        TabUtils.openURLWithQoraiActivity(
                                LinkSubscriptionUtils.getQoraiAccountLinkUrl(
                                        InAppPurchaseWrapper.SubscriptionProduct.VPN));
                        return true;
                    }
                });
        PreferenceCategory preferenceCategory =
                (PreferenceCategory) findPreference(PREF_QORAI_VPN_SUBSCRIPTION_SECTION);
        preferenceCategory.addPreference(mLinkSubscriptionPreference);
        preferenceCategory.setVisible(!QoraiVpnNativeWorker.getInstance().isPurchasedUser());
    }

    @Override
    public ObservableSupplier<String> getPageTitle() {
        return mPageTitle;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context != null) {
            ConnectivityManager connectivityManager =
                    (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkRequest networkRequest =
                    new NetworkRequest.Builder()
                            .addTransportType(NetworkCapabilities.TRANSPORT_VPN)
                            .removeCapability(NetworkCapabilities.NET_CAPABILITY_NOT_VPN)
                            .build();
            connectivityManager.registerNetworkCallback(networkRequest, mNetworkCallback);
        }
        if (!InternetConnection.isNetworkAvailable(getActivity())) {
            Toast.makeText(getActivity(), R.string.no_internet, Toast.LENGTH_SHORT).show();
            getActivity().finish();
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        if (QoraiVpnUtils.mUpdateProfileAfterSplitTunnel) {
            QoraiVpnUtils.mUpdateProfileAfterSplitTunnel = false;
            QoraiVpnUtils.showProgressDialog(
                    getActivity(), getResources().getString(R.string.updating_vpn_profile));
            QoraiVpnUtils.updateProfileConfiguration(getActivity());
        } else {
            QoraiVpnUtils.dismissProgressDialog();
        }
        if (mLinkSubscriptionPreference != null) {
            mLinkSubscriptionPreference.setVisible(
                    ChromeFeatureList.isEnabled(
                                    QoraiFeatureList.QORAI_VPN_LINK_SUBSCRIPTION_ANDROID_UI)
                            && QoraiVpnPrefUtils.isSubscriptionPurchase());
        }
        // Ensures preference screen is fully loaded before updating summaries
        PostTask.postTask(TaskTraits.UI_DEFAULT, this::updateSummaries);
    }

    private void updateSummary(String preferenceString, String summary) {
        Preference p = findPreference(preferenceString);
        p.setSummary(summary);
    }

    private void updateSummaries() {
        if (getActivity() == null) {
            return;
        }
        if (!QoraiVpnPrefUtils.getProductId().isEmpty()) {
            String subscriptionStatus =
                    String.format(
                            InAppPurchaseWrapper.getInstance()
                                            .isMonthlySubscription(QoraiVpnPrefUtils.getProductId())
                                    ? getActivity()
                                            .getResources()
                                            .getString(R.string.monthly_subscription)
                                    : getActivity()
                                            .getResources()
                                            .getString(R.string.yearly_subscription),
                            (QoraiVpnPrefUtils.isTrialSubscription()
                                    ? getActivity().getResources().getString(R.string.trial)
                                    : ""));
            updateSummary(PREF_SUBSCRIPTION_STATUS, subscriptionStatus);
        }

        if (QoraiVpnPrefUtils.getPurchaseExpiry() > 0) {
            long expiresInMillis = QoraiVpnPrefUtils.getPurchaseExpiry();
            SimpleDateFormat formatter = new SimpleDateFormat(DATE_FORMAT, Locale.getDefault());
            updateSummary(PREF_SUBSCRIPTION_EXPIRES, formatter.format(new Date(expiresInMillis)));
        }
        if (mVpnSwitch != null) {
            mVpnSwitch.setChecked(
                    QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(getActivity()));
        }
        new Thread() {
            @Override
            public void run() {
                if (getActivity() != null) {
                    getActivity()
                            .runOnUiThread(
                                    new Runnable() {
                                        @Override
                                        public void run() {
                                            findPreference(PREF_SERVER_CHANGE_LOCATION)
                                                    .setVisible(
                                                            QoraiVpnPrefUtils
                                                                    .isSubscriptionPurchase());
                                            findPreference(PREF_SPLIT_TUNNELING)
                                                    .setEnabled(
                                                            QoraiVpnPrefUtils
                                                                    .isSubscriptionPurchase());
                                            findPreference(PREF_AUTO_RECONNECT_VPN)
                                                    .setEnabled(
                                                            QoraiVpnPrefUtils
                                                                    .isSubscriptionPurchase());
                                            findPreference(PREF_SUPPORT_TECHNICAL)
                                                    .setEnabled(
                                                            QoraiVpnPrefUtils
                                                                    .isSubscriptionPurchase());
                                        }
                                    });
                }
            }
        }.start();
        QoraiVpnUtils.dismissProgressDialog();
    }

    private final ConnectivityManager.NetworkCallback mNetworkCallback =
            new ConnectivityManager.NetworkCallback() {
                @Override
                public void onAvailable(Network network) {
                    QoraiVpnUtils.dismissProgressDialog();
                    // Run updateSummaries on UI thread
                    PostTask.postTask(
                            TaskTraits.UI_DEFAULT, QoraiVpnPreferences.this::updateSummaries);
                }

                @Override
                public void onLost(Network network) {
                    QoraiVpnUtils.dismissProgressDialog();
                    // Run updateSummaries on UI thread
                    PostTask.postTask(
                            TaskTraits.UI_DEFAULT, QoraiVpnPreferences.this::updateSummaries);
                }
            };

    private void verifyPurchase(boolean isVerification) {
        MutableLiveData<PurchaseModel> _activePurchases = new MutableLiveData();
        LiveData<PurchaseModel> activePurchases = _activePurchases;
        InAppPurchaseWrapper.getInstance().queryPurchases(
                _activePurchases, InAppPurchaseWrapper.SubscriptionProduct.VPN);
        LiveDataUtil.observeOnce(activePurchases, activePurchaseModel -> {
            mQoraiVpnPrefModel = new QoraiVpnPrefModel();
            if (activePurchaseModel != null) {
                mQoraiVpnPrefModel.setPurchaseToken(activePurchaseModel.getPurchaseToken());
                mQoraiVpnPrefModel.setProductId(activePurchaseModel.getProductId());
                if (QoraiVpnPrefUtils.isResetConfiguration()) {
                    QoraiVpnUtils.dismissProgressDialog();
                    QoraiVpnUtils.openQoraiVpnProfileActivity(getActivity());
                    return;
                }
                if (!isVerification) {
                    QoraiVpnNativeWorker.getInstance().getSubscriberCredential(
                            QoraiVpnUtils.SUBSCRIPTION_PARAM_TEXT,
                            mQoraiVpnPrefModel.getProductId(), QoraiVpnUtils.IAP_ANDROID_PARAM_TEXT,
                            mQoraiVpnPrefModel.getPurchaseToken(), getActivity().getPackageName());
                } else {
                    QoraiVpnNativeWorker.getInstance().verifyPurchaseToken(
                            mQoraiVpnPrefModel.getPurchaseToken(),
                            mQoraiVpnPrefModel.getProductId(),
                            QoraiVpnUtils.SUBSCRIPTION_PARAM_TEXT, getActivity().getPackageName());
                }
            } else {
                QoraiVpnApiResponseUtils.queryPurchaseFailed(getActivity());
                QoraiVpnUtils.openQoraiVpnPlansActivity(getActivity());
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
                if (mSubscriptionStatus != null) {
                    String subscriptionStatus = String.format(
                            InAppPurchaseWrapper.getInstance().isMonthlySubscription(
                                    QoraiVpnPrefUtils.getProductId())
                                    ? getActivity().getResources().getString(
                                              R.string.monthly_subscription)
                                    : getActivity().getResources().getString(
                                              R.string.yearly_subscription),
                            (QoraiVpnPrefUtils.isTrialSubscription()
                                            ? getActivity().getResources().getString(R.string.trial)
                                            : ""));
                    mSubscriptionStatus.setSummary(subscriptionStatus);
                }

                if (mSubscriptionExpires != null) {
                    SimpleDateFormat formatter =
                            new SimpleDateFormat(DATE_FORMAT, Locale.getDefault());
                    mSubscriptionExpires.setSummary(formatter.format(new Date(purchaseExpiry)));
                }
                checkVpnAfterVerification();
            } else {
                QoraiVpnApiResponseUtils.queryPurchaseFailed(getActivity());
            }
        }
    };

    private void checkVpnAfterVerification() {
        new Thread() {
            @Override
            public void run() {
                Intent intent = GoBackend.VpnService.prepare(getActivity());
                if (intent != null || !WireguardConfigUtils.isConfigExist(getActivity())) {
                    QoraiVpnUtils.dismissProgressDialog();
                    QoraiVpnUtils.openQoraiVpnProfileActivity(getActivity());
                    return;
                }
                QoraiVpnProfileUtils.getInstance().startVpn(getActivity());
            }
        }.start();
    }

    @Override
    public void onGetSubscriberCredential(String subscriberCredential, boolean isSuccess) {
        mQoraiVpnPrefModel.setSubscriberCredential(subscriberCredential);
        QoraiVpnApiResponseUtils.handleOnGetSubscriberCredential(getActivity(), isSuccess);
    };

    @Override
    public void onGetTimezonesForRegions(String jsonTimezones, boolean isSuccess) {
        QoraiVpnApiResponseUtils.handleOnGetTimezonesForRegions(
                getActivity(), mQoraiVpnPrefModel, jsonTimezones, isSuccess);
    }

    @Override
    public void onGetHostnamesForRegion(String jsonHostNames, boolean isSuccess) {
        KeyPair keyPair = new KeyPair();
        mQoraiVpnPrefModel.setClientPrivateKey(keyPair.getPrivateKey().toBase64());
        mQoraiVpnPrefModel.setClientPublicKey(keyPair.getPublicKey().toBase64());
        Pair<String, String> host = QoraiVpnApiResponseUtils.handleOnGetHostnamesForRegion(
                getActivity(), mQoraiVpnPrefModel, jsonHostNames, isSuccess);
        mQoraiVpnPrefModel.setHostname(host.first);
        mQoraiVpnPrefModel.setHostnameDisplay(host.second);
    }

    @Override
    public void onGetWireguardProfileCredentials(
            String jsonWireguardProfileCredentials, boolean isSuccess) {
        if (isSuccess && mQoraiVpnPrefModel != null) {
            QoraiVpnWireguardProfileCredentials qoraiVpnWireguardProfileCredentials =
                    QoraiVpnUtils.getWireguardProfileCredentials(jsonWireguardProfileCredentials);
            stopStartConnection(qoraiVpnWireguardProfileCredentials);
        } else {
            Toast.makeText(getActivity(), R.string.vpn_profile_creation_failed, Toast.LENGTH_LONG)
                    .show();
            QoraiVpnUtils.dismissProgressDialog();
            PostTask.postTask(TaskTraits.UI_DEFAULT, this::updateSummaries);
        }
    }

    private void stopStartConnection(
            QoraiVpnWireguardProfileCredentials qoraiVpnWireguardProfileCredentials) {
        new Thread() {
            @Override
            public void run() {
                try {
                    if (QoraiVpnProfileUtils.getInstance().isQoraiVPNConnected(getActivity())) {
                        QoraiVpnProfileUtils.getInstance().stopVpn(getActivity());
                    }
                    WireguardConfigUtils.deleteConfig(getActivity());
                    if (!WireguardConfigUtils.isConfigExist(getActivity())) {
                        WireguardConfigUtils.createConfig(
                                getActivity(),
                                qoraiVpnWireguardProfileCredentials.getMappedIpv4Address(),
                                mQoraiVpnPrefModel.getHostname(),
                                mQoraiVpnPrefModel.getClientPrivateKey(),
                                qoraiVpnWireguardProfileCredentials.getServerPublicKey());
                    }
                    QoraiVpnProfileUtils.getInstance().startVpn(getActivity());
                } catch (Exception e) {
                    Log.e(TAG, e.getMessage());
                }
                mQoraiVpnPrefModel.setClientId(qoraiVpnWireguardProfileCredentials.getClientId());
                mQoraiVpnPrefModel.setApiAuthToken(
                        qoraiVpnWireguardProfileCredentials.getApiAuthToken());
                QoraiVpnPrefUtils.setPrefModel(mQoraiVpnPrefModel);
                PostTask.postTask(TaskTraits.UI_DEFAULT, QoraiVpnPreferences.this::updateSummaries);
            }
        }.start();
    }

    @Override
    public void onStart() {
        super.onStart();
        QoraiVpnNativeWorker.getInstance().addObserver(this);
    }

    @Override
    public void onStop() {
        QoraiVpnNativeWorker.getInstance().removeObserver(this);
        super.onStop();
    }

    private void showConfirmDialog() {
        AlertDialog.Builder confirmDialog = new AlertDialog.Builder(getActivity());
        confirmDialog.setTitle(
                getActivity().getResources().getString(R.string.reset_vpn_config_dialog_title));
        confirmDialog.setMessage(
                getActivity().getResources().getString(R.string.reset_vpn_config_dialog_message));
        confirmDialog.setPositiveButton(
                getActivity().getResources().getString(android.R.string.yes), (dialog, which) -> {
                    resetConfiguration();
                    dialog.dismiss();
                });
        confirmDialog.setNegativeButton(getActivity().getResources().getString(android.R.string.no),
                (dialog, which) -> { dialog.dismiss(); });
        confirmDialog.show();
    }

    private void resetConfiguration() {
        QoraiVpnNativeWorker.getInstance().invalidateCredentials(QoraiVpnPrefUtils.getHostname(),
                QoraiVpnPrefUtils.getClientId(), QoraiVpnPrefUtils.getSubscriberCredential(),
                QoraiVpnPrefUtils.getApiAuthToken());
        QoraiVpnUtils.showProgressDialog(
                getActivity(), getResources().getString(R.string.resetting_config));
        PostTask.postDelayedTask(
                TaskTraits.UI_DEFAULT,
                () -> {
                    if (isResumed()) {
                        QoraiVpnUtils.resetProfileConfiguration(getActivity());
                        PostTask.postTask(TaskTraits.UI_DEFAULT, this::updateSummaries);
                    }
                },
                INVALIDATE_CREDENTIAL_TIMER_COUNT);
    }

    @Override
    public void onDestroy() {
        QoraiVpnUtils.dismissProgressDialog();
        super.onDestroy();
    }
}
