/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.billing;

import android.app.Activity;
import android.content.Context;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.style.ForegroundColorSpan;
import android.text.style.TextAppearanceSpan;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.android.billingclient.api.AcknowledgePurchaseParams;
import com.android.billingclient.api.BillingClient;
import com.android.billingclient.api.BillingClientStateListener;
import com.android.billingclient.api.BillingFlowParams;
import com.android.billingclient.api.BillingResult;
import com.android.billingclient.api.ProductDetails;
import com.android.billingclient.api.Purchase;
import com.android.billingclient.api.PurchasesUpdatedListener;
import com.android.billingclient.api.QueryProductDetailsParams;
import com.android.billingclient.api.QueryPurchasesParams;

import org.chromium.base.ContextUtils;
import org.chromium.base.Log;
import org.chromium.base.ThreadUtils;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraPrefUtils;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraUtils;
import org.chromium.chrome.browser.qorai_origin.QoraiOriginSubscriptionPrefs;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.util.QoraiConstants;
import org.chromium.chrome.browser.util.LiveDataUtil;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnPrefUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnUtils;
import org.chromium.ui.widget.Toast;

import java.util.ArrayList;
import java.util.Currency;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

@NullMarked
public class InAppPurchaseWrapper {
    public static final String MANAGE_SUBSCRIPTION_PAGE =
            "https://play.google.com/store/account/subscriptions";
    private static final String TAG = "InAppPurchaseWrapper";
    // Qorai Qora AI Chat subscription product IDs
    private static final String QORA_MONTHLY_SUBSCRIPTION = "qorai.qora.monthly";
    private static final String QORA_YEARLY_SUBSCRIPTION = "qorai.qora.yearly";

    // Qorai Origin premium features subscription product IDs
    private static final String ORIGIN_MONTHLY_SUBSCRIPTION = "qorai.origin.monthly";
    private static final String ORIGIN_YEARLY_SUBSCRIPTION = "qorai.origin.yearly";

    private static final String ORIGIN_NIGHTLY_MONTHLY_SUBSCRIPTION = "nightly.origin.monthly";
    private static final String ORIGIN_NIGHTLY_YEARLY_SUBSCRIPTION = "nightly.origin.yearly";

    private static final String ORIGIN_BETA_MONTHLY_SUBSCRIPTION = "beta.origin.monthly";
    private static final String ORIGIN_BETA_YEARLY_SUBSCRIPTION = "beta.origin.yearly";

    private static final String VPN_NIGHTLY_MONTHLY_SUBSCRIPTION = "nightly.qoraivpn.monthly";
    private static final String VPN_NIGHTLY_YEARLY_SUBSCRIPTION = "nightly.qoraivpn.yearly";

    private static final String VPN_BETA_MONTHLY_SUBSCRIPTION = "beta.qoraivpn.monthly";
    private static final String VPN_BETA_YEARLY_SUBSCRIPTION = "beta.qoraivpn.yearly";

    public static final String VPN_RELEASE_MONTHLY_SUBSCRIPTION = "qorai.vpn.monthly";
    public static final String VPN_RELEASE_YEARLY_SUBSCRIPTION = "qorai.vpn.yearly";
    private @Nullable BillingClient mBillingClient;

    // Profile context for current purchase flow
    private @Nullable Profile mPurchaseProfile;

    private static final long MICRO_UNITS =
            1000000; // 1,000,000 micro-units equal one unit of the currency

    private static volatile @Nullable InAppPurchaseWrapper sInAppPurchaseWrapper;
    private static final Object sMutex = new Object();

    public enum SubscriptionType {
        MONTHLY,
        YEARLY
    }

    /**
     * Enumeration of available subscription products in Qorai browser. Each product represents a
     * different premium service offering.
     */
    public enum SubscriptionProduct {
        VPN, // Qorai VPN service for secure browsing
        QORA, // Qorai Qora AI Chat premium features
        ORIGIN // Qorai Origin premium privacy and advanced features
    }

    // VPN monthly subscription product details
    private final MutableLiveData<ProductDetails> mMutableMonthlyProductDetailsVPN =
            new MutableLiveData();
    private final LiveData<ProductDetails> mMonthlyProductDetailsVPN =
            mMutableMonthlyProductDetailsVPN;
    // Qora monthly subscription product details
    private final MutableLiveData<ProductDetails> mMutableMonthlyProductDetailsQora =
            new MutableLiveData();
    private final LiveData<ProductDetails> mMonthlyProductDetailsQora =
            mMutableMonthlyProductDetailsQora;
    // Origin monthly subscription product details
    private final MutableLiveData<ProductDetails> mMutableMonthlyProductDetailsOrigin =
            new MutableLiveData();
    private final LiveData<ProductDetails> mMonthlyProductDetailsOrigin =
            mMutableMonthlyProductDetailsOrigin;

    /**
     * Sets the monthly subscription product details for the specified subscription product. Updates
     * the appropriate LiveData based on the product type.
     *
     * @param productDetails The Google Play Billing product details
     * @param product The subscription product type (VPN, QORA, or ORIGIN)
     */
    private void setMonthlyProductDetails(
            @Nullable ProductDetails productDetails, SubscriptionProduct product) {
        if (product.equals(SubscriptionProduct.QORA)) {
            mMutableMonthlyProductDetailsQora.postValue(productDetails);
        } else if (product.equals(SubscriptionProduct.VPN)) {
            mMutableMonthlyProductDetailsVPN.postValue(productDetails);
        } else if (product.equals(SubscriptionProduct.ORIGIN)) {
            // Set Origin monthly subscription product details
            mMutableMonthlyProductDetailsOrigin.postValue(productDetails);
        }
    }

    /**
     * Gets the LiveData containing monthly subscription product details for the specified product.
     *
     * @param product The subscription product type (VPN, QORA, or ORIGIN)
     * @return LiveData containing the product details, defaults to VPN if product not recognized
     */
    public LiveData<ProductDetails> getMonthlyProductDetails(SubscriptionProduct product) {
        if (product.equals(SubscriptionProduct.QORA)) {
            return mMonthlyProductDetailsQora;
        } else if (product.equals(SubscriptionProduct.ORIGIN)) {
            // Return Origin monthly subscription product details
            return mMonthlyProductDetailsOrigin;
        }
        // Default to VPN product details
        return mMonthlyProductDetailsVPN;
    }

    // VPN yearly subscription product details
    private final MutableLiveData<ProductDetails> mMutableYearlyProductDetailsVPN =
            new MutableLiveData();
    private final LiveData<ProductDetails> mYearlyProductDetailsVPN =
            mMutableYearlyProductDetailsVPN;
    // Qora yearly subscription product details
    private final MutableLiveData<ProductDetails> mMutableYearlyProductDetailsQora =
            new MutableLiveData();
    private final LiveData<ProductDetails> mYearlyProductDetailsQora =
            mMutableYearlyProductDetailsQora;
    // Origin yearly subscription product details
    private final MutableLiveData<ProductDetails> mMutableYearlyProductDetailsOrigin =
            new MutableLiveData();
    private final LiveData<ProductDetails> mYearlyProductDetailsOrigin =
            mMutableYearlyProductDetailsOrigin;

    private void setYearlyProductDetails(
            @Nullable ProductDetails productDetails, SubscriptionProduct product) {
        if (product.equals(SubscriptionProduct.QORA)) {
            mMutableYearlyProductDetailsQora.postValue(productDetails);
        } else if (product.equals(SubscriptionProduct.VPN)) {
            mMutableYearlyProductDetailsVPN.postValue(productDetails);
        } else if (product.equals(SubscriptionProduct.ORIGIN)) {
            mMutableYearlyProductDetailsOrigin.postValue(productDetails);
        }
    }

    public LiveData<ProductDetails> getYearlyProductDetails(SubscriptionProduct product) {
        if (product.equals(SubscriptionProduct.QORA)) {
            return mYearlyProductDetailsQora;
        } else if (product.equals(SubscriptionProduct.ORIGIN)) {
            return mYearlyProductDetailsOrigin;
        }
        return mYearlyProductDetailsVPN;
    }

    private InAppPurchaseWrapper() {}

    public static InAppPurchaseWrapper getInstance() {
        InAppPurchaseWrapper result = sInAppPurchaseWrapper;
        if (result == null) {
            synchronized (sMutex) {
                result = sInAppPurchaseWrapper;
                if (result == null) sInAppPurchaseWrapper = result = new InAppPurchaseWrapper();
            }
        }
        return result;
    }

    public boolean isMonthlySubscription(String productId) {
        return productId.equals(VPN_NIGHTLY_MONTHLY_SUBSCRIPTION)
                || productId.equals(VPN_BETA_MONTHLY_SUBSCRIPTION)
                || productId.equals(VPN_RELEASE_MONTHLY_SUBSCRIPTION);
    }

    private void startBillingServiceConnection(
            @Nullable MutableLiveData<Boolean> billingClientConnectionState) {
        Context context = ContextUtils.getApplicationContext();
        // End existing connection if any before we start another connection
        endConnection();

        mBillingClient = BillingClient.newBuilder(context)
                                 .enablePendingPurchases()
                                 .setListener(getPurchasesUpdatedListener(context))
                                 .build();
        if (!mBillingClient.isReady()) {
            try {
                mBillingClient.startConnection(
                        new BillingClientStateListener() {
                            @Override
                            public void onBillingServiceDisconnected() {
                                retryBillingServiceConnection(billingClientConnectionState);
                            }

                            @Override
                            public void onBillingSetupFinished(BillingResult billingResult) {
                                if (billingResult.getResponseCode()
                                        == BillingClient.BillingResponseCode.OK) {
                                    if (billingClientConnectionState != null) {
                                        billingClientConnectionState.postValue(true);
                                    }
                                } else {
                                    showToast(billingResult.getDebugMessage());
                                    retryBillingServiceConnection(billingClientConnectionState);
                                }
                            }
                        });
            } catch (IllegalStateException exc) {
                // That prevents a crash that some users experience
                // https://github.com/qorai/qorai-browser/issues/27751.
                // It's unknown what causes it, we tried to add retries, but it
                // didn't help.
                Log.e(TAG, "startBillingServiceConnection " + exc.getMessage());
            }
        } else {
            if (billingClientConnectionState != null) {
                billingClientConnectionState.postValue(mBillingClient.getConnectionState()
                        == BillingClient.ConnectionState.CONNECTED);
            }
        }
    }

    private void endConnection() {
        if (mBillingClient != null) {
            mBillingClient.endConnection();
            mBillingClient = null;
        }
    }

    public String getProductId(SubscriptionProduct product, SubscriptionType subscriptionType) {
        if (product.equals(SubscriptionProduct.VPN)) {
            String qoraiPackageName = ContextUtils.getApplicationContext().getPackageName();
            if (qoraiPackageName.equals(QoraiConstants.QORAI_PRODUCTION_PACKAGE_NAME)) {
                return subscriptionType == SubscriptionType.MONTHLY ?
                        VPN_RELEASE_MONTHLY_SUBSCRIPTION
                        : VPN_RELEASE_YEARLY_SUBSCRIPTION;
            } else if (qoraiPackageName.equals(QoraiConstants.QORAI_BETA_PACKAGE_NAME)) {
                return subscriptionType == SubscriptionType.MONTHLY
                        ? VPN_BETA_MONTHLY_SUBSCRIPTION
                        : VPN_BETA_YEARLY_SUBSCRIPTION;
            } else {
                return subscriptionType == SubscriptionType.MONTHLY ?
                        VPN_NIGHTLY_MONTHLY_SUBSCRIPTION
                        : VPN_NIGHTLY_YEARLY_SUBSCRIPTION;
            }
        } else if (product.equals(SubscriptionProduct.QORA)) {
            return subscriptionType == SubscriptionType.MONTHLY
                    ? QORA_MONTHLY_SUBSCRIPTION
                    : QORA_YEARLY_SUBSCRIPTION;
        } else if (product.equals(SubscriptionProduct.ORIGIN)) {
            String qoraiPackageName = ContextUtils.getApplicationContext().getPackageName();
            if (qoraiPackageName.equals(QoraiConstants.QORAI_PRODUCTION_PACKAGE_NAME)) {
                return subscriptionType == SubscriptionType.MONTHLY
                        ? ORIGIN_MONTHLY_SUBSCRIPTION
                        : ORIGIN_YEARLY_SUBSCRIPTION;
            } else if (qoraiPackageName.equals(QoraiConstants.QORAI_BETA_PACKAGE_NAME)) {
                return subscriptionType == SubscriptionType.MONTHLY
                        ? ORIGIN_BETA_MONTHLY_SUBSCRIPTION
                        : ORIGIN_BETA_YEARLY_SUBSCRIPTION;
            } else {
                return subscriptionType == SubscriptionType.MONTHLY
                        ? ORIGIN_NIGHTLY_MONTHLY_SUBSCRIPTION
                        : ORIGIN_NIGHTLY_YEARLY_SUBSCRIPTION;
            }
        } else {
            assert false;
            return "";
        }
    }

    public void queryProductDetailsAsync(SubscriptionProduct product) {
        Map<String, ProductDetails> productDetails = new HashMap<>();
        List<QueryProductDetailsParams.Product> products = new ArrayList<>();
        products.add(
                QueryProductDetailsParams.Product.newBuilder()
                        .setProductId(getProductId(product, SubscriptionType.MONTHLY))
                        .setProductType(BillingClient.ProductType.SUBS)
                        .build());
        products.add(
                QueryProductDetailsParams.Product.newBuilder()
                        .setProductId(getProductId(product, SubscriptionType.YEARLY))
                        .setProductType(BillingClient.ProductType.SUBS)
                        .build());
        QueryProductDetailsParams queryProductDetailsParams =
                QueryProductDetailsParams.newBuilder().setProductList(products).build();

        MutableLiveData<Boolean> _billingConnectionState = new MutableLiveData();
        LiveData<Boolean> billingConnectionState = _billingConnectionState;
        startBillingServiceConnection(_billingConnectionState);
        LiveDataUtil.observeOnce(
                billingConnectionState,
                isConnected -> {
                    if (isConnected && mBillingClient != null) {
                        mBillingClient.queryProductDetailsAsync(
                                queryProductDetailsParams,
                                (billingResult, productDetailsList) -> {
                                    // End connection after getting the product details
                                    endConnection();

                                    if (billingResult.getResponseCode()
                                            == BillingClient.BillingResponseCode.OK) {
                                        for (ProductDetails productDetail : productDetailsList) {
                                            productDetails.put(
                                                    productDetail.getProductId(), productDetail);
                                        }
                                        setMonthlyProductDetails(
                                                productDetails.get(
                                                        getProductId(
                                                                product, SubscriptionType.MONTHLY)),
                                                product);
                                        setYearlyProductDetails(
                                                productDetails.get(
                                                        getProductId(
                                                                product, SubscriptionType.YEARLY)),
                                                product);
                                    } else {
                                        Log.e(
                                                TAG,
                                                "queryProductDetailsAsync failed"
                                                        + billingResult.getDebugMessage());
                                        showToast(billingResult.getDebugMessage());
                                    }
                                });
                    }
                });
    }

    public void queryPurchases(MutableLiveData<PurchaseModel> mutableActivePurchases,
                               SubscriptionProduct type) {
        MutableLiveData<Boolean> _billingConnectionState = new MutableLiveData();
        LiveData<Boolean> billingConnectionState = _billingConnectionState;
        startBillingServiceConnection(_billingConnectionState);
        LiveDataUtil.observeOnce(
                billingConnectionState,
                isConnected -> {
                    if (isConnected && mBillingClient != null) {
                        mBillingClient.queryPurchasesAsync(
                                QueryPurchasesParams.newBuilder()
                                        .setProductType(BillingClient.ProductType.SUBS)
                                        .build(),
                                (billingResult, purchases) -> {
                                    // End connection after getting purchases
                                    endConnection();

                                    PurchaseModel activePurchaseModel = null;
                                    if (billingResult.getResponseCode()
                                            == BillingClient.BillingResponseCode.OK) {
                                        for (Purchase purchase : purchases) {
                                            if (purchase.getPurchaseState()
                                                    != Purchase.PurchaseState.PURCHASED) {
                                                continue;
                                            }
                                            List<String> productIds = purchase.getProducts();
                                            boolean isVPNProduct = isVPNProduct(productIds);
                                            boolean isQoraProduct = isQoraProduct(productIds);
                                            boolean isOriginProduct = isOriginProduct(productIds);
                                            if ((isVPNProduct
                                                            && type.equals(SubscriptionProduct.VPN))
                                                    || (isQoraProduct
                                                            && type.equals(SubscriptionProduct.QORA))
                                                    || (isOriginProduct
                                                            && type.equals(
                                                                    SubscriptionProduct.ORIGIN))) {
                                                activePurchaseModel =
                                                        new PurchaseModel(
                                                                purchase.getPurchaseToken(),
                                                                purchase.getProducts()
                                                                        .get(0)
                                                                        .toString(),
                                                                purchase);
                                                break;
                                            }
                                        }
                                    } else {
                                        Log.e(
                                                TAG,
                                                "queryPurchases failed"
                                                        + billingResult.getDebugMessage());
                                        showToast(billingResult.getDebugMessage());
                                    }
                                    mutableActivePurchases.postValue(activePurchaseModel);
                                });
                    } else {
                        mutableActivePurchases.postValue(null);
                    }
                });
    }

    public void initiatePurchase(Activity activity, ProductDetails productDetails) {
        List<ProductDetails.SubscriptionOfferDetails> offerDetails =
                productDetails.getSubscriptionOfferDetails();
        if (offerDetails == null || offerDetails.isEmpty()) {
            Log.e(TAG, "No subscription offer details available");
            return;
        }
        String offerToken = offerDetails.get(0).getOfferToken();
        List<BillingFlowParams.ProductDetailsParams> productDetailsParamsList = new ArrayList<>();
        productDetailsParamsList.add(
                BillingFlowParams.ProductDetailsParams.newBuilder()
                        .setProductDetails(productDetails)
                        .setOfferToken(offerToken)
                        .build());

        BillingFlowParams billingFlowParams =
                BillingFlowParams.newBuilder()
                        .setProductDetailsParamsList(productDetailsParamsList)
                        .build();
        MutableLiveData<Boolean> _billingConnectionState = new MutableLiveData();
        LiveData<Boolean> billingConnectionState = _billingConnectionState;
        startBillingServiceConnection(_billingConnectionState);
        LiveDataUtil.observeOnce(
                billingConnectionState,
                isConnected -> {
                    if (isConnected && mBillingClient != null) {
                        BillingResult unused_billingResult =
                                mBillingClient.launchBillingFlow(activity, billingFlowParams);
                    }
                });
    }

    /**
     * Initiates a subscription purchase flow with profile context.
     *
     * @param activity The activity to launch the billing flow from
     * @param productDetails The subscription product details to purchase
     * @param profile The current user profile for context (can be null)
     */
    public void initiatePurchase(
            Activity activity, ProductDetails productDetails, @Nullable Profile profile) {
        // Store the profile for use in the asynchronous purchase callback flow
        mPurchaseProfile = profile;

        // Delegate to the original method
        initiatePurchase(activity, productDetails);
    }

    public void processPurchases(Context context, Purchase activePurchase) {
        acknowledgePurchase(context, activePurchase);
    }

    private void acknowledgePurchase(Context context, Purchase purchase) {
        AcknowledgePurchaseParams acknowledgePurchaseParams =
                AcknowledgePurchaseParams.newBuilder()
                        .setPurchaseToken(purchase.getPurchaseToken())
                        .build();
        List<String> productIds = purchase.getProducts();
        boolean isVPNProduct = isVPNProduct(productIds);
        boolean isQoraProduct = isQoraProduct(productIds);
        boolean isOriginProduct = isOriginProduct(productIds);
        if (!purchase.isAcknowledged()) {
            MutableLiveData<Boolean> _billingConnectionState = new MutableLiveData();
            LiveData<Boolean> billingConnectionState = _billingConnectionState;
            startBillingServiceConnection(_billingConnectionState);
            LiveDataUtil.observeOnce(
                    billingConnectionState,
                    isConnected -> {
                        if (isConnected && mBillingClient != null) {
                            mBillingClient.acknowledgePurchase(
                                    acknowledgePurchaseParams,
                                    billingResult -> {
                                        // End connection after getting the response of the purchase
                                        // acknowledgment
                                        endConnection();
                                        if (billingResult.getResponseCode()
                                                == BillingClient.BillingResponseCode.OK) {
                                            receiptAcknowledged(
                                                    context,
                                                    purchase,
                                                    isVPNProduct,
                                                    isQoraProduct,
                                                    isOriginProduct);
                                        } else {
                                            showToast(
                                                    context.getResources()
                                                            .getString(
                                                                    R.string.fail_to_aknowledge));
                                        }
                                    });
                        }
                    });
        } else {
            if (isVPNProduct) {
                QoraiVpnPrefUtils.setSubscriptionPurchase(true);
            } else if (isQoraProduct) {
                receiptAcknowledged(context, purchase, false, true, false);
            } else if (isOriginProduct) {
                receiptAcknowledged(context, purchase, false, false, true);
            }
        }
    }

    private void receiptAcknowledged(
            Context context,
            Purchase purchase,
            boolean isVPNProduct,
            boolean isQoraProduct,
            boolean isOriginProduct) {
        QoraiActivity activity = null;
        try {
            activity = QoraiActivity.getQoraiActivity();
        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            Log.e(TAG, "acknowledgePurchase " + e.getMessage());
        }
        if (isVPNProduct) {
            QoraiVpnPrefUtils.setSubscriptionPurchase(true);
            if (activity != null) {
                QoraiVpnUtils.openQoraiVpnProfileActivity(activity);
            }
        } else if (isQoraProduct && activity != null) {
            activity.runOnUiThread(
                    new Runnable() {
                        @Override
                        public void run() {
                            QoraiQoraPrefUtils.setIsSubscriptionActive(true);
                            QoraiQoraPrefUtils.setChatPackageName();
                            QoraiQoraPrefUtils.setChatProductId(
                                    purchase.getProducts().get(0).toString());
                            QoraiQoraPrefUtils.setChatPurchaseToken(purchase.getPurchaseToken());
                            QoraiQoraUtils.bringMainActivityOnTop();
                        }
                    });
        } else if (isOriginProduct && activity != null) {
            final QoraiActivity finalActivity = activity;
            ThreadUtils.runOnUiThread(
                    () -> {
                        QoraiOriginSubscriptionPrefs.setIsSubscriptionActive(
                                mPurchaseProfile, true);
                        QoraiOriginSubscriptionPrefs.setOriginPackageName(mPurchaseProfile);
                        QoraiOriginSubscriptionPrefs.setOriginProductId(
                                mPurchaseProfile, purchase.getProducts().get(0));
                        QoraiOriginSubscriptionPrefs.setOriginPurchaseToken(
                                mPurchaseProfile, purchase.getPurchaseToken());
                        QoraiOriginSubscriptionPrefs.openOriginPreferences(finalActivity);
                    });
        }
        showToast(context.getResources().getString(R.string.subscription_consumed));

        // Clear the stored profile after processing
        mPurchaseProfile = null;
    }

    private boolean isVPNProduct(List<String> productIds) {
        return productIds.contains(VPN_NIGHTLY_MONTHLY_SUBSCRIPTION) ||
                productIds.contains(VPN_NIGHTLY_YEARLY_SUBSCRIPTION) ||
                productIds.contains(VPN_BETA_MONTHLY_SUBSCRIPTION) ||
                productIds.contains(VPN_BETA_YEARLY_SUBSCRIPTION) ||
                productIds.contains(VPN_RELEASE_MONTHLY_SUBSCRIPTION) ||
                productIds.contains(VPN_RELEASE_YEARLY_SUBSCRIPTION);
    }

    private boolean isQoraProduct(List<String> productIds) {
        return productIds.contains(QORA_MONTHLY_SUBSCRIPTION)
                || productIds.contains(QORA_YEARLY_SUBSCRIPTION);
    }

    /**
     * Checks if the given product IDs contain any Qorai Origin subscription products.
     *
     * @param productIds List of product IDs from the purchase
     * @return true if any Origin product ID is found, false otherwise
     */
    private boolean isOriginProduct(List<String> productIds) {
        return productIds.contains(ORIGIN_MONTHLY_SUBSCRIPTION)
                || productIds.contains(ORIGIN_YEARLY_SUBSCRIPTION)
                || productIds.contains(ORIGIN_NIGHTLY_MONTHLY_SUBSCRIPTION)
                || productIds.contains(ORIGIN_NIGHTLY_YEARLY_SUBSCRIPTION)
                || productIds.contains(ORIGIN_BETA_MONTHLY_SUBSCRIPTION)
                || productIds.contains(ORIGIN_BETA_YEARLY_SUBSCRIPTION);
    }

    private PurchasesUpdatedListener getPurchasesUpdatedListener(Context context) {
        return (billingResult, purchases) -> {
            endConnection();
            if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK) {
                if (purchases != null) {
                    for (Purchase purchase : purchases) {
                        if (purchase.getPurchaseState() == Purchase.PurchaseState.PURCHASED) {
                            processPurchases(context, purchase);
                        }
                    }
                }
            } else if (billingResult.getResponseCode()
                    == BillingClient.BillingResponseCode.ITEM_ALREADY_OWNED) {
                showToast(context.getResources().getString(R.string.already_subscribed));
            } else if (billingResult.getResponseCode()
                    == BillingClient.BillingResponseCode.USER_CANCELED) {
                showToast(context.getResources().getString(R.string.error_caused_by_user));
            } else {
                showToast(context.getResources().getString(R.string.purchased_failed));
            }
        };
    }

    private int mMaxTries;
    private int mTries;
    private boolean mIsConnectionEstablished;

    private void retryBillingServiceConnection(
            @Nullable MutableLiveData<Boolean> billingClientConnectionState) {
        mMaxTries = 3;
        mTries = 1;
        mIsConnectionEstablished = false;
        do {
            try {
                // End existing connection if any before we start another connection
                endConnection();

                Context context = ContextUtils.getApplicationContext();

                mBillingClient =
                        BillingClient.newBuilder(context)
                                .enablePendingPurchases()
                                .setListener(getPurchasesUpdatedListener(context))
                                .build();

                mBillingClient.startConnection(
                        new BillingClientStateListener() {
                            @Override
                            public void onBillingServiceDisconnected() {
                                if (mTries == mMaxTries && billingClientConnectionState != null) {
                                    billingClientConnectionState.postValue(false);
                                }
                            }

                            @Override
                            public void onBillingSetupFinished(BillingResult billingResult) {
                                if (billingResult.getResponseCode()
                                        == BillingClient.BillingResponseCode.OK) {
                                    mIsConnectionEstablished = true;
                                    if (billingClientConnectionState != null) {
                                        billingClientConnectionState.postValue(true);
                                    }
                                } else {
                                    showToast(billingResult.getDebugMessage());
                                }
                            }
                        });
            } catch (Exception ex) {
                Log.e(TAG, "retryBillingServiceConnection " + ex.getMessage());
            } finally {
                mTries++;
            }
        } while (mTries <= mMaxTries && !mIsConnectionEstablished);
    }

    private ProductDetails.@Nullable PricingPhase getPricingPhase(ProductDetails productDetails) {
        if (productDetails.getSubscriptionOfferDetails() != null) {
            for (ProductDetails.SubscriptionOfferDetails subscriptionOfferDetails :
                    productDetails.getSubscriptionOfferDetails()) {
                if (subscriptionOfferDetails.getOfferId() == null) {
                    for (ProductDetails.PricingPhase pricingPhase :
                            subscriptionOfferDetails.getPricingPhases().getPricingPhaseList()) {
                        if (pricingPhase.getPriceAmountMicros() > 0) {
                            return pricingPhase;
                        }
                    }
                }
            }
        }
        return null;
    }

    public @Nullable SpannableString getFormattedProductPrice(
            Context context, ProductDetails productDetails, int stringRes) {
        ProductDetails.PricingPhase pricingPhase = getPricingPhase(productDetails);
        if (pricingPhase != null) {
            double price = ((double) pricingPhase.getPriceAmountMicros() / MICRO_UNITS);
            String priceString = String.format(Locale.getDefault(), "%.2f", price);
            String currencySymbol =
                    Currency.getInstance(pricingPhase.getPriceCurrencyCode()).getSymbol();
            String priceWithSymbol = currencySymbol + priceString;
            String finalPrice =
                    context.getResources()
                            .getString(
                                    stringRes,
                                    pricingPhase.getPriceCurrencyCode() + " " + priceWithSymbol);
            SpannableString priceSpannable = new SpannableString(finalPrice);
            int index = finalPrice.indexOf(priceWithSymbol);
            priceSpannable.setSpan(
                    new TextAppearanceSpan(context, R.style.LargeSemibold),
                    index,
                    index + priceWithSymbol.length(),
                    Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
            priceSpannable.setSpan(
                    new ForegroundColorSpan(context.getColor(android.R.color.white)),
                    index,
                    index + priceWithSymbol.length(),
                    Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
            return priceSpannable;
        }
        return null;
    }

    public @Nullable SpannableString getFormattedFullProductPrice(
            Context context, ProductDetails productDetails) {
        ProductDetails.PricingPhase pricingPhase = getPricingPhase(productDetails);
        if (pricingPhase != null) {
            double yearlyPrice = ((double) pricingPhase.getPriceAmountMicros() / MICRO_UNITS) * 12;
            String priceString = String.format(Locale.getDefault(), "%.2f", yearlyPrice);
            String currencySymbol =
                    Currency.getInstance(pricingPhase.getPriceCurrencyCode()).getSymbol();
            String priceWithSymbol = currencySymbol + priceString;
            String finalPrice = pricingPhase.getPriceCurrencyCode() + " " + priceWithSymbol;
            SpannableString priceSpannable = new SpannableString(finalPrice);
            int index = finalPrice.indexOf(priceWithSymbol);
            priceSpannable.setSpan(
                    new TextAppearanceSpan(context, R.style.LargeSemibold),
                    index,
                    index + priceWithSymbol.length(),
                    Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
            priceSpannable.setSpan(
                    new ForegroundColorSpan(context.getColor(android.R.color.white)),
                    index,
                    index + priceWithSymbol.length(),
                    Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
            return priceSpannable;
        }
        return null;
    }

    public int getYearlyDiscountPercentage(
            ProductDetails monthlyProductDetails, ProductDetails yearlyProductDetails) {
        ProductDetails.PricingPhase monthlyPricingPhase = getPricingPhase(monthlyProductDetails);
        ProductDetails.PricingPhase yearlyPricingPhase = getPricingPhase(yearlyProductDetails);
        if (monthlyPricingPhase != null && yearlyPricingPhase != null) {
            double yearlyPrice =
                    ((double) monthlyPricingPhase.getPriceAmountMicros() / MICRO_UNITS) * 12;
            double yearlyActualPrice =
                    ((double) yearlyPricingPhase.getPriceAmountMicros() / MICRO_UNITS);
            if (yearlyPrice == 0) {
                return 0;
            }
            double discountPrice = yearlyPrice - yearlyActualPrice;
            double discountPercentage = (discountPrice / yearlyPrice) * 100;
            return (int) Math.round(discountPercentage);
        }
        return 0;
    }

    private void showToast(String message) {
        Context context = ContextUtils.getApplicationContext();
        Toast.makeText(context, message, Toast.LENGTH_SHORT).show();
    }
}
