/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.vpn.activities;

import android.graphics.Rect;
import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.materialswitch.MaterialSwitch;

import org.chromium.qorai_vpn.mojom.QoraiVpnConstants;
import org.chromium.qorai_vpn.mojom.Region;
import org.chromium.qorai_vpn.mojom.ServiceHandler;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.vpn.QoraiVpnServiceFactoryAndroid;
import org.chromium.chrome.browser.vpn.adapters.QoraiVpnServerSelectionAdapter;
import org.chromium.chrome.browser.vpn.models.QoraiVpnServerRegion;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnPrefUtils;
import org.chromium.chrome.browser.vpn.utils.QoraiVpnUtils;
import org.chromium.mojo.bindings.ConnectionErrorHandler;
import org.chromium.mojo.system.MojoException;
import org.chromium.ui.widget.Toast;

import java.util.Arrays;

public class VpnServerSelectionActivity extends QoraiVpnParentActivity
        implements ConnectionErrorHandler {
    private QoraiVpnServerSelectionAdapter mQoraiVpnServerSelectionAdapter;
    private LinearLayout mServerSelectionListLayout;
    private ProgressBar mServerSelectionProgress;
    private RecyclerView mServerRegionList;
    private TextView mServersSectionText;
    private MaterialSwitch mAutomaticSwitch;

    private ServiceHandler mServiceHandler;

    @Override
    public void onConnectionError(MojoException e) {
        if (mServiceHandler != null) {
            mServiceHandler.close();
            mServiceHandler = null;
        }
        initVpnService();
    }

    private void initVpnService() {
        if (mServiceHandler != null) {
            mServiceHandler.close();
            mServiceHandler = null;
        }
        mServiceHandler =
                QoraiVpnServiceFactoryAndroid.getInstance()
                        .getVpnService(
                                getProfileProviderSupplier().get().getOriginalProfile(), this);
    }

    public interface OnServerRegionSelection {
        void onServerRegionClick(Region region);
    }

    public interface OnQuickServerSelection {
        void onQuickServerSelect(Region region);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish();
        }
        return super.onOptionsItemSelected(item);
    }

    private void initializeViews() {
        setContentView(R.layout.activity_vpn_server_selection);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        ActionBar actionBar = getSupportActionBar();
        assert actionBar != null;
        actionBar.setDisplayHomeAsUpEnabled(true);
        actionBar.setTitle(getResources().getString(R.string.server_region));

        mServerRegionList = (RecyclerView) findViewById(R.id.server_selection_list);

        mServersSectionText = (TextView) findViewById(R.id.servers_section_text);
        mAutomaticSwitch = (MaterialSwitch) findViewById(R.id.automatic_server_switch);
        mAutomaticSwitch.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        if (mAutomaticSwitch.isChecked()) {
                            QoraiVpnUtils.selectedServerRegion =
                                    new QoraiVpnServerRegion(
                                            true,
                                            "",
                                            "",
                                            "",
                                            QoraiVpnPrefUtils.PREF_QORAI_VPN_AUTOMATIC,
                                            "",
                                            QoraiVpnConstants.REGION_PRECISION_COUNTRY);
                            changeServerRegion();
                        } else {
                            QoraiVpnPrefUtils.setAutomaticServerSelection(
                                    mAutomaticSwitch.isChecked());
                        }

                        updateAutomaticSelection(mAutomaticSwitch.isChecked());
                    }
                });
        mServerSelectionListLayout = (LinearLayout) findViewById(R.id.server_selection_list_layout);
        mServerSelectionProgress = (ProgressBar) findViewById(R.id.server_selection_progress);

        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
        mServerRegionList.addItemDecoration(
                new DividerItemDecoration(
                        VpnServerSelectionActivity.this, linearLayoutManager.getOrientation()) {
                    @Override
                    public void getItemOffsets(
                            Rect outRect,
                            View view,
                            RecyclerView parent,
                            RecyclerView.State state) {
                        int position = parent.getChildAdapterPosition(view);
                        // hide the divider for the last child
                        if (position == state.getItemCount() - 1) {
                            outRect.setEmpty();
                        } else {
                            super.getItemOffsets(outRect, view, parent, state);
                        }
                    }
                });
        mServerRegionList.setLayoutManager(linearLayoutManager);
        boolean isAutomatic = QoraiVpnPrefUtils.isAutomaticServerSelection();
        mAutomaticSwitch.setChecked(isAutomatic);
    }

    private void updateAutomaticSelection(boolean isAutomatic) {
        mServerRegionList.setVisibility(isAutomatic ? View.GONE : View.VISIBLE);
        mServersSectionText.setVisibility(isAutomatic ? View.GONE : View.VISIBLE);
    }

    @Override
    public void finishNativeInitialization() {
        super.finishNativeInitialization();
        initVpnService();
        showProgress();
        if (mServiceHandler != null) {
            mServiceHandler.getAllRegions(
                    regions -> {
                        if (regions.length > 0) {
                            mQoraiVpnServerSelectionAdapter =
                                    new QoraiVpnServerSelectionAdapter(
                                            VpnServerSelectionActivity.this);
                            mQoraiVpnServerSelectionAdapter.setVpnServerRegions(
                                    Arrays.asList(regions));
                            mQoraiVpnServerSelectionAdapter.setOnServerRegionSelection(
                                    new OnServerRegionSelection() {
                                        @Override
                                        public void onServerRegionClick(Region region) {
                                            QoraiVpnUtils.selectedRegion = region;
                                            QoraiVpnUtils.openVpnServerActivity(
                                                    VpnServerSelectionActivity.this, region);
                                        }
                                    });
                            mQoraiVpnServerSelectionAdapter.setOnQuickServerSelection(
                                    new OnQuickServerSelection() {
                                        @Override
                                        public void onQuickServerSelect(Region region) {
                                            QoraiVpnUtils.selectedRegion = region;
                                            QoraiVpnUtils.selectedServerRegion =
                                                    new QoraiVpnServerRegion(
                                                            false,
                                                            region.country,
                                                            region.continent,
                                                            region.countryIsoCode,
                                                            region.name,
                                                            region.namePretty,
                                                            QoraiVpnConstants
                                                                    .REGION_PRECISION_COUNTRY);
                                            changeServerRegion();
                                        }
                                    });
                            mServerRegionList.setAdapter(mQoraiVpnServerSelectionAdapter);
                            boolean isAutomatic = QoraiVpnPrefUtils.isAutomaticServerSelection();
                            updateAutomaticSelection(isAutomatic);
                            hideProgress();
                        } else {
                            Toast.makeText(
                                            VpnServerSelectionActivity.this,
                                            R.string.fail_to_get_server_locations,
                                            Toast.LENGTH_LONG)
                                    .show();
                        }
                    });
        }
    }

    @Override
    protected void triggerLayoutInflation() {
        initializeViews();
        onInitialLayoutInflationComplete();
    }

    @Override
    public boolean shouldStartGpuProcess() {
        return true;
    }

    public void showProgress() {
        if (mServerSelectionProgress != null) {
            mServerSelectionProgress.setVisibility(View.VISIBLE);
        }
        if (mServerSelectionListLayout != null) {
            mServerSelectionListLayout.setAlpha(0.4f);
        }
    }

    public void hideProgress() {
        if (mServerSelectionProgress != null) {
            mServerSelectionProgress.setVisibility(View.GONE);
        }
        if (mServerSelectionListLayout != null) {
            mServerSelectionListLayout.setAlpha(1f);
        }
    }

    @Override
    public void showRestoreMenu(boolean shouldShowRestore) {}

    @Override
    public void updateProfileView() {}

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mServiceHandler != null) {
            mServiceHandler.close();
            mServiceHandler = null;
        }
    }
}
