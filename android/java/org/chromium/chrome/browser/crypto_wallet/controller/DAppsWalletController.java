/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.crypto_wallet.controller;

import static org.chromium.chrome.browser.app.QoraiActivity.QORAI_WALLET_HOST;

import android.content.Context;
import android.content.DialogInterface;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.DefaultLifecycleObserver;
import androidx.lifecycle.LifecycleOwner;

import org.chromium.base.Log;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.qorai_wallet.mojom.AssetRatioService;
import org.chromium.qorai_wallet.mojom.QoraiWalletService;
import org.chromium.qorai_wallet.mojom.JsonRpcService;
import org.chromium.qorai_wallet.mojom.KeyringService;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.crypto_wallet.AssetRatioServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.QoraiWalletServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.modal.QoraiWalletPanel;
import org.chromium.chrome.browser.crypto_wallet.modal.DAppsDialog;
import org.chromium.chrome.browser.crypto_wallet.util.Utils;
import org.chromium.chrome.browser.fullscreen.BrowserControlsManager;
import org.chromium.chrome.browser.fullscreen.FullscreenManager;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarConfiguration;
import org.chromium.chrome.browser.util.ConfigurationUtils;
import org.chromium.content_public.browser.WebContents;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;
import org.chromium.url.GURL;

public class DAppsWalletController implements ConnectionErrorHandler {
    private static final String TAG = DAppsWalletController.class.getSimpleName();
    private FullscreenManager mFullscreenManager;
    private final Context mContext;
    private final View mAnchorViewHost;
    private AssetRatioService mAssetRatioService;
    private KeyringService mKeyringService;
    private QoraiWalletService mQoraiWalletService;
    protected JsonRpcService mJsonRpcService;
    private boolean mHasStateInitialise;
    private DAppsDialog mDAppsDialog;
    private QoraiWalletPanel mQoraiWalletPanel;
    private DialogInterface.OnDismissListener mOnDismissListener;
    private final AppCompatActivity mActivity;
    @Nullable private final GURL mVisibleUrl;

    @NonNull private final DefaultLifecycleObserver mDefaultLifecycleObserver;

    @NonNull private final DialogInterface.OnDismissListener mDialogOrPanelDismissListener;

    public DAppsWalletController(Context mContext, View mAnchorViewHost) {
        this.mContext = mContext;
        this.mAnchorViewHost = mAnchorViewHost;
        this.mActivity = QoraiActivity.getChromeTabbedActivity();
        WebContents webContents = null;
        mDefaultLifecycleObserver =
                new DefaultLifecycleObserver() {
                    @Override
                    public void onResume(@NonNull LifecycleOwner owner) {
                        if (mQoraiWalletPanel != null) {
                            mQoraiWalletPanel.resume();
                        }
                    }

                    @Override
                    public void onPause(@NonNull LifecycleOwner owner) {
                        if (mQoraiWalletPanel != null) {
                            mQoraiWalletPanel.pause();
                        }
                    }
                };
        mDialogOrPanelDismissListener =
                dialog -> {
                    if (mOnDismissListener != null) {
                        mOnDismissListener.onDismiss(dialog);
                    }
                    DAppsWalletController.this.cleanUp();
                };
        try {
            QoraiActivity activity = QoraiActivity.getQoraiActivity();
            webContents = activity.getCurrentWebContents();

            ObservableSupplier<BrowserControlsManager> managerSupplier =
                    activity.getBrowserControlsManagerSupplier();
            mFullscreenManager = managerSupplier.get().getFullscreenManager();
        } catch (QoraiActivity.QoraiActivityNotFoundException | NullPointerException e) {
            Log.e(TAG, "Constructor", e);
        }

        if (webContents != null) {
            mVisibleUrl = webContents.getVisibleUrl();
        } else {
            mVisibleUrl = null;
        }
    }

    public DAppsWalletController(
            Context context,
            View anchorViewHost,
            DialogInterface.OnDismissListener onDismissListener) {
        this(context, anchorViewHost);
        this.mOnDismissListener = onDismissListener;
    }

    public void showWalletPanel() {
        initAssetRatioService();
        initKeyringService();
        initJsonRpcService();
        initQoraiWalletService();
        if (Utils.shouldShowCryptoOnboarding()) {
            showOnBoardingOrUnlock();
        } else {
            mKeyringService.isLocked(
                    isLocked -> {
                        if (isLocked) {
                            showOnBoardingOrUnlock();
                        } else {
                            boolean isFoundPendingDAppsTx = false;
                            // TODO: check if pending dapps transaction are available and implement
                            // an action accrodingly
                            if (!isFoundPendingDAppsTx) {
                                createAndShowWalletPanel();
                            }
                        }
                    });
        }
    }

    private void createAndShowWalletPanel() {
        boolean showExpandButton =
                mVisibleUrl != null && !mVisibleUrl.getHost().equals(QORAI_WALLET_HOST);
        mQoraiWalletPanel =
                new QoraiWalletPanel(
                        mAnchorViewHost, mDialogOrPanelDismissListener, showExpandButton);
        mQoraiWalletPanel.showLikeMenu();
        setupLifeCycleUpdater();
    }

    private void setupLifeCycleUpdater() {
        mActivity.getLifecycle().addObserver(mDefaultLifecycleObserver);
    }

    private void showOnBoardingOrUnlock() {
        int dialogStyle = DAppsDialog.DAppsDialogStyle.BOTTOM;
        if ((mFullscreenManager != null && mFullscreenManager.getPersistentFullscreenMode())
                || shouldShowNotificationAtTop(mActivity)) {
            dialogStyle = DAppsDialog.DAppsDialogStyle.TOP;
        }
        mDAppsDialog =
                DAppsDialog.newInstance(mContext, mDialogOrPanelDismissListener, dialogStyle);
        mDAppsDialog.showOnboarding(Utils.shouldShowCryptoOnboarding());
    }

    @Override
    public void onConnectionError(MojoException e) {
        if (mKeyringService != null) {
            mKeyringService.close();
            mKeyringService = null;
        }
        if (mJsonRpcService != null) {
            mJsonRpcService.close();
            mJsonRpcService = null;
        }
        if (mQoraiWalletService != null) {
            mQoraiWalletService.close();
            mQoraiWalletService = null;
        }
        if (mAssetRatioService != null) {
            mAssetRatioService.close();
            mAssetRatioService = null;
        }
        initAssetRatioService();
        initKeyringService();
        initJsonRpcService();
        initQoraiWalletService();
        updateState();
    }

    public void dismiss() {
        if (isShowingPanel()) {
            mQoraiWalletPanel.dismiss();
        }
        if (isShowingDialog()) {
            mDAppsDialog.dismiss();
        }
        mQoraiWalletPanel = null;
        mDAppsDialog = null;
        cleanUp();
    }

    public boolean isShowingPanel() {
        return mQoraiWalletPanel != null && mQoraiWalletPanel.isShowing();
    }

    public boolean isShowingDialog() {
        return mDAppsDialog != null && mDAppsDialog.isShowing();
    }

    private void updateState() {
        if (mHasStateInitialise) return;
        // remember the dialog has been shown
        mHasStateInitialise = true;
    }

    private void initKeyringService() {
        if (mKeyringService != null) {
            return;
        }
        mKeyringService = QoraiWalletServiceFactory.getInstance().getKeyringService(this);
    }

    private void initJsonRpcService() {
        if (mJsonRpcService != null) {
            return;
        }
        mJsonRpcService = QoraiWalletServiceFactory.getInstance().getJsonRpcService(this);
    }

    private void initQoraiWalletService() {
        if (mQoraiWalletService != null) {
            return;
        }
        mQoraiWalletService = QoraiWalletServiceFactory.getInstance().getQoraiWalletService(this);
    }

    private void initAssetRatioService() {
        if (mAssetRatioService != null) {
            return;
        }
        mAssetRatioService = AssetRatioServiceFactory.getInstance().getAssetRatioService(this);
    }

    private void cleanUp() {
        if (mKeyringService != null) {
            mKeyringService.close();
            mKeyringService = null;
        }
        if (mJsonRpcService != null) {
            mJsonRpcService.close();
            mJsonRpcService = null;
        }
        if (mQoraiWalletService != null) {
            mQoraiWalletService.close();
            mQoraiWalletService = null;
        }
        if (mAssetRatioService != null) {
            mAssetRatioService.close();
            mAssetRatioService = null;
        }
        if (mActivity != null) {
            mActivity.getLifecycle().removeObserver(mDefaultLifecycleObserver);
        }
    }

    private boolean shouldShowNotificationAtTop(Context context) {
        return ConfigurationUtils.isTablet(context)
                || !BottomToolbarConfiguration.isQoraiBottomControlsEnabled();
    }
}
