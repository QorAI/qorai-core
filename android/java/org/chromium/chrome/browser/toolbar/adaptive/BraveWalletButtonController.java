/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.adaptive;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.view.View;

import org.chromium.base.QoraiFeatureList;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.ActivityTabProvider;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.toolbar.optional_button.BaseButtonDataProvider;
import org.chromium.ui.modaldialog.ModalDialogManager;

/** Handles displaying Qorai Wallet button on toolbar. */
@NullMarked
public class QoraiWalletButtonController extends BaseButtonDataProvider {
    private final Context mContext;

    public QoraiWalletButtonController(
            Context context,
            Drawable buttonDrawable,
            ActivityTabProvider tabProvider,
            ObservableSupplier<Profile> profileSupplier,
            ModalDialogManager modalDialogManager) {
        super(
                tabProvider,
                modalDialogManager,
                buttonDrawable,
                context.getString(R.string.menu_qorai_wallet),
                /* actionChipLabelResId= */ Resources.ID_NULL,
                /* supportsTinting= */ true,
                /* iphCommandBuilder= */ null,
                AdaptiveToolbarButtonVariant.WALLET,
                /* tooltipTextResId= */ R.string.menu_qorai_wallet);

        mContext = context;
    }

    @Override
    public void onClick(View view) {
        assert mContext instanceof QoraiActivity : "Context is not an QoraiActivity";

        // Open Qorai Wallet
        if (mContext instanceof QoraiActivity qoraiActivity) {
            qoraiActivity.openQoraiWallet(false, false, false);
        }
    }

    @Override
    protected boolean shouldShowButton(@Nullable Tab tab) {
        if (!super.shouldShowButton(tab)) return false;

        // Show the Qorai Wallet button only if the feature is enabled
        return ChromeFeatureList.isEnabled(QoraiFeatureList.NATIVE_QORAI_WALLET);
    }
}
