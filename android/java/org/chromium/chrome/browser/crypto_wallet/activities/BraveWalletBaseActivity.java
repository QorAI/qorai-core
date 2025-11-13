/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.crypto_wallet.activities;

import android.view.MenuItem;

import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.qorai_wallet.mojom.AssetRatioService;
import org.chromium.qorai_wallet.mojom.BlockchainRegistry;
import org.chromium.qorai_wallet.mojom.QoraiWalletP3a;
import org.chromium.qorai_wallet.mojom.QoraiWalletService;
import org.chromium.qorai_wallet.mojom.EthTxManagerProxy;
import org.chromium.qorai_wallet.mojom.JsonRpcService;
import org.chromium.qorai_wallet.mojom.KeyringService;
import org.chromium.qorai_wallet.mojom.SolanaTxManagerProxy;
import org.chromium.qorai_wallet.mojom.TransactionInfo;
import org.chromium.qorai_wallet.mojom.TxService;
import org.chromium.chrome.browser.crypto_wallet.AssetRatioServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.BlockchainRegistryFactory;
import org.chromium.chrome.browser.crypto_wallet.QoraiWalletServiceFactory;
import org.chromium.chrome.browser.crypto_wallet.observers.KeyringServiceObserverImpl;
import org.chromium.chrome.browser.crypto_wallet.observers.KeyringServiceObserverImpl.KeyringServiceObserverImplDelegate;
import org.chromium.chrome.browser.crypto_wallet.observers.TxServiceObserverImpl;
import org.chromium.chrome.browser.crypto_wallet.observers.TxServiceObserverImpl.TxServiceObserverImplDelegate;
import org.chromium.chrome.browser.init.ActivityProfileProvider;
import org.chromium.chrome.browser.init.AsyncInitializationActivity;
import org.chromium.chrome.browser.profiles.ProfileProvider;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;

public abstract class QoraiWalletBaseActivity extends AsyncInitializationActivity
        implements ConnectionErrorHandler,
                KeyringServiceObserverImplDelegate,
                TxServiceObserverImplDelegate {
    protected KeyringService mKeyringService;
    protected BlockchainRegistry mBlockchainRegistry;
    protected JsonRpcService mJsonRpcService;
    protected TxService mTxService;
    protected EthTxManagerProxy mEthTxManagerProxy;
    protected SolanaTxManagerProxy mSolanaTxManagerProxy;
    protected AssetRatioService mAssetRatioService;
    protected QoraiWalletP3a mQoraiWalletP3A;
    protected QoraiWalletService mQoraiWalletService;
    private KeyringServiceObserverImpl mKeyringServiceObserver;
    private TxServiceObserverImpl mTxServiceObserver;

    @Override
    public void onUserInteraction() {
        if (mKeyringService == null) {
            return;
        }
        mKeyringService.notifyUserInteraction();
    }

    @Override
    public void onConnectionError(MojoException e) {
        if (mKeyringServiceObserver != null) {
            mKeyringServiceObserver.close();
            mKeyringServiceObserver = null;
        }
        if (mTxServiceObserver != null) {
            mTxServiceObserver.close();
            mTxServiceObserver.destroy();
            mTxServiceObserver = null;
        }
        if (mKeyringService != null) mKeyringService.close();
        if (mAssetRatioService != null) mAssetRatioService.close();
        if (mBlockchainRegistry != null) mBlockchainRegistry.close();
        if (mJsonRpcService != null) mJsonRpcService.close();
        if (mTxService != null) mTxService.close();
        if (mEthTxManagerProxy != null) mEthTxManagerProxy.close();
        if (mSolanaTxManagerProxy != null) mSolanaTxManagerProxy.close();
        if (mQoraiWalletP3A != null) mQoraiWalletP3A.close();
        if (mQoraiWalletService != null) mQoraiWalletService.close();

        mKeyringService = null;
        mBlockchainRegistry = null;
        mJsonRpcService = null;
        mTxService = null;
        mEthTxManagerProxy = null;
        mSolanaTxManagerProxy = null;
        mAssetRatioService = null;
        mQoraiWalletP3A = null;
        mQoraiWalletService = null;
        initKeyringService();
        initBlockchainRegistry();
        initJsonRpcService();
        initTxService();
        initEthTxManagerProxy();
        initSolanaTxManagerProxy();
        initAssetRatioService();
        initQoraiWalletP3A();
        initQoraiWalletService();
    }

    protected void initTxService() {
        if (mTxService != null) {
            return;
        }

        mTxService = QoraiWalletServiceFactory.getInstance().getTxService(this);
        mTxServiceObserver = new TxServiceObserverImpl(this);
        mTxService.addObserver(mTxServiceObserver);
    }

    protected void initEthTxManagerProxy() {
        if (mEthTxManagerProxy != null) {
            return;
        }

        mEthTxManagerProxy = QoraiWalletServiceFactory.getInstance().getEthTxManagerProxy(this);
    }

    protected void initSolanaTxManagerProxy() {
        if (mSolanaTxManagerProxy != null) {
            return;
        }

        mSolanaTxManagerProxy =
                QoraiWalletServiceFactory.getInstance().getSolanaTxManagerProxy(this);
    }

    protected void initKeyringService() {
        if (mKeyringService != null) {
            return;
        }

        mKeyringService = QoraiWalletServiceFactory.getInstance().getKeyringService(this);
        mKeyringServiceObserver = new KeyringServiceObserverImpl(this);
        mKeyringService.addObserver(mKeyringServiceObserver);
    }

    protected void initBlockchainRegistry() {
        if (mBlockchainRegistry != null) {
            return;
        }

        mBlockchainRegistry = BlockchainRegistryFactory.getInstance().getBlockchainRegistry(this);
    }

    protected void initJsonRpcService() {
        if (mJsonRpcService != null) {
            return;
        }

        mJsonRpcService = QoraiWalletServiceFactory.getInstance().getJsonRpcService(this);
    }

    protected void initAssetRatioService() {
        if (mAssetRatioService != null) {
            return;
        }

        mAssetRatioService = AssetRatioServiceFactory.getInstance().getAssetRatioService(this);
    }

    protected void initQoraiWalletP3A() {
        if (mQoraiWalletP3A != null) {
            return;
        }

        mQoraiWalletP3A = QoraiWalletServiceFactory.getInstance().getQoraiWalletP3A(this);
    }

    protected void initQoraiWalletService() {
        if (mQoraiWalletService != null) {
            return;
        }

        mQoraiWalletService = QoraiWalletServiceFactory.getInstance().getQoraiWalletService(this);
    }

    public KeyringService getKeyringService() {
        return mKeyringService;
    }

    public BlockchainRegistry getBlockchainRegistry() {
        return mBlockchainRegistry;
    }

    public JsonRpcService getJsonRpcService() {
        return mJsonRpcService;
    }

    public TxService getTxService() {
        return mTxService;
    }

    public EthTxManagerProxy getEthTxManagerProxy() {
        return mEthTxManagerProxy;
    }

    public SolanaTxManagerProxy getSolanaTxManagerProxy() {
        return mSolanaTxManagerProxy;
    }

    public AssetRatioService getAssetRatioService() {
        return mAssetRatioService;
    }

    public QoraiWalletService getQoraiWalletService() {
        return mQoraiWalletService;
    }

    public QoraiWalletP3a getQoraiWalletP3A() {
        return mQoraiWalletP3A;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void finishNativeInitialization() {
        super.finishNativeInitialization();
        initKeyringService();
        initBlockchainRegistry();
        initJsonRpcService();
        initTxService();
        initEthTxManagerProxy();
        initSolanaTxManagerProxy();
        initAssetRatioService();
        initQoraiWalletP3A();
        initQoraiWalletService();
    }

    @Override
    public void onDestroy() {
        if (mKeyringServiceObserver != null) {
            mKeyringServiceObserver.close();
        }
        if (mTxServiceObserver != null) {
            mTxServiceObserver.close();
            mTxServiceObserver.destroy();
        }
        if (mKeyringService != null) mKeyringService.close();
        if (mAssetRatioService != null) mAssetRatioService.close();
        if (mBlockchainRegistry != null) mBlockchainRegistry.close();
        if (mJsonRpcService != null) mJsonRpcService.close();
        if (mTxService != null) mTxService.close();
        if (mEthTxManagerProxy != null) mEthTxManagerProxy.close();
        if (mSolanaTxManagerProxy != null) mSolanaTxManagerProxy.close();
        if (mQoraiWalletP3A != null) mQoraiWalletP3A.close();
        if (mQoraiWalletService != null) mQoraiWalletService.close();
        super.onDestroy();
    }

    @Override
    public boolean shouldStartGpuProcess() {
        return true;
    }

    @Override
    public void locked() {
        finish();
    }

    @Override
    public void backedUp() {}

    @Override
    public void onNewUnapprovedTx(TransactionInfo txInfo) {}

    @Override
    public void onUnapprovedTxUpdated(TransactionInfo txInfo) {}

    @Override
    public void onTransactionStatusChanged(TransactionInfo txInfo) {}

    @Override
    protected OneshotSupplier<ProfileProvider> createProfileProvider() {
        return new ActivityProfileProvider(getLifecycleDispatcher());
    }
}
