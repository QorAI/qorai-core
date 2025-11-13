/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.site_settings;

import android.annotation.SuppressLint;
import android.content.Context;
import android.util.AttributeSet;

import androidx.preference.Preference;
import androidx.preference.PreferenceViewHolder;
import androidx.recyclerview.widget.RecyclerView;

import org.chromium.qorai_wallet.mojom.QoraiWalletService;
import org.chromium.qorai_wallet.mojom.CoinType;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.crypto_wallet.QoraiWalletServiceFactory;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;

public class QoraiWalletEthereumConnectedSitesPreference
        extends Preference implements ConnectionErrorHandler,
                                      QoraiWalletEthereumConnectedSitesListAdapter
                                              .QoraiEthereumPermissionConnectedSitesDelegate {
    private RecyclerView mRecyclerView;
    private QoraiWalletService mQoraiWalletService;
    private QoraiWalletEthereumConnectedSitesListAdapter mAdapter;

    public QoraiWalletEthereumConnectedSitesPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void onBindViewHolder(PreferenceViewHolder holder) {
        super.onBindViewHolder(holder);

        initQoraiWalletService();

        mRecyclerView = (RecyclerView) holder.findViewById(R.id.connected_sites_list);
        updateWebSitestList();
    }

    public void destroy() {
        mQoraiWalletService.close();
        mQoraiWalletService = null;
    }

    @SuppressLint("NotifyDataSetChanged")
    private void updateWebSitestList() {
        mQoraiWalletService.getWebSitesWithPermission(CoinType.ETH, webSites -> {
            if (mAdapter == null) {
                mAdapter = new QoraiWalletEthereumConnectedSitesListAdapter(webSites, this);
                mRecyclerView.setAdapter(mAdapter);
            } else {
                mAdapter.setWebSites(webSites);
                mAdapter.notifyDataSetChanged();
            }
        });
    }

    @Override
    public void removePermission(String webSite) {
        mQoraiWalletService.resetWebSitePermission(CoinType.ETH, webSite, success -> {
            if (success) {
                updateWebSitestList();
            }
        });
    }

    @Override
    public void onConnectionError(MojoException e) {
        mQoraiWalletService.close();
        mQoraiWalletService = null;
        initQoraiWalletService();
    }

    private void initQoraiWalletService() {
        if (mQoraiWalletService != null) {
            return;
        }

        mQoraiWalletService = QoraiWalletServiceFactory.getInstance().getQoraiWalletService(this);
    }
}
