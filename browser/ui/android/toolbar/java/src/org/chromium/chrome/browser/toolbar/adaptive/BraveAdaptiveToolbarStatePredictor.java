/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.adaptive;

import android.content.Context;

import org.chromium.base.QoraiFeatureList;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.ui.permissions.AndroidPermissionDelegate;

/**
 * Qorai-specific implementation of AdaptiveToolbarStatePredictor that extends the base
 * functionality to support Qorai-specific toolbar button variants.
 */
@NullMarked
public class QoraiAdaptiveToolbarStatePredictor
        extends QoraiAdaptiveToolbarStatePredictorDummySuper {

    public QoraiAdaptiveToolbarStatePredictor(
            Context context,
            Profile profile,
            @Nullable AndroidPermissionDelegate androidPermissionDelegate,
            @Nullable AdaptiveToolbarBehavior behavior) {
        super(context, profile, androidPermissionDelegate, behavior);
    }

    /**
     * Returns true if the given toolbar button variant is a Qorai-specific valid option, otherwise
     * defers to the parent implementation.
     *
     * @param variant The button variant to validate
     * @return true if the variant is valid for Qorai, otherwise call super implementation
     */
    @Override
    public boolean isValidSegment(@AdaptiveToolbarButtonVariant int variant) {
        // Check Qorai-specific variants first
        switch (variant) {
                // Add more Qorai-specific variants here as needed
            case AdaptiveToolbarButtonVariant.BOOKMARKS:
            case AdaptiveToolbarButtonVariant.HISTORY:
            case AdaptiveToolbarButtonVariant.DOWNLOADS:
                return true;
            case AdaptiveToolbarButtonVariant.QORA:
                return ChromeFeatureList.isEnabled(QoraiFeatureList.AI_CHAT);
            case AdaptiveToolbarButtonVariant.WALLET:
                return ChromeFeatureList.isEnabled(QoraiFeatureList.NATIVE_QORAI_WALLET);
        }

        return super.isValidSegment(variant);
    }
}
