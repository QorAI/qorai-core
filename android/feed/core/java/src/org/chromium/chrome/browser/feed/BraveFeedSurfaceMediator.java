/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.feed;

import android.content.Context;
import android.widget.FrameLayout;

import androidx.annotation.Nullable;

import org.chromium.chrome.browser.feed.componentinterfaces.SurfaceCoordinator;
import org.chromium.chrome.browser.feed.sort_ui.FeedOptionsCoordinator;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.components.browser_ui.widget.displaystyle.UiConfig;
import org.chromium.ui.modelutil.PropertyModel;

public class QoraiFeedSurfaceMediator extends FeedSurfaceMediator {
    // Own members.
    private final Profile mProfile;

    // To delete in bytecode, members from parent class will be used instead.
    private FeedSurfaceCoordinator mCoordinator;
    private SnapScrollHelper mSnapScrollHelper;

    QoraiFeedSurfaceMediator(
            FeedSurfaceCoordinator coordinator,
            Context context,
            @Nullable SnapScrollHelper snapScrollHelper,
            @Nullable PropertyModel headerModel,
            @SurfaceCoordinator.StreamTabId int openingTabId,
            FeedActionDelegate actionDelegate,
            FeedOptionsCoordinator optionsCoordinator,
            @Nullable UiConfig uiConfig,
            Profile profile) {
        super(
                coordinator,
                context,
                snapScrollHelper,
                headerModel,
                openingTabId,
                actionDelegate,
                optionsCoordinator,
                uiConfig,
                profile);

        mProfile = profile;
    }

    @Override
    void updateContent() {
        assert !FeedFeatures.isFeedEnabled(mProfile) : "Feed should be disabled in Qorai!";
        assert mCoordinator instanceof QoraiFeedSurfaceCoordinator
                : "Wrong feed surface coordinator!";

        if (FeedFeatures.isFeedEnabled(mProfile)
                || !(mCoordinator instanceof QoraiFeedSurfaceCoordinator)) {
            super.updateContent();
            return;
        }

        FrameLayout view = ((QoraiFeedSurfaceCoordinator) mCoordinator).getFrameLayoutForPolicy();
        if (view != null) {
            return;
        }
        destroyPropertiesForStream();
        ((QoraiFeedSurfaceCoordinator) mCoordinator).createFrameLayoutForPolicy();
        view = ((QoraiFeedSurfaceCoordinator) mCoordinator).getFrameLayoutForPolicy();
        if (mSnapScrollHelper != null) {
            mSnapScrollHelper.setView(view);
            view.getViewTreeObserver().addOnScrollChangedListener(mSnapScrollHelper::handleScroll);
        }
    }

    @Override
    public void onTemplateURLServiceChanged() {
        if (!FeedFeatures.isFeedEnabled(mProfile)) {
            // We don't need any special handling since feed is disabled.
            return;
        }
        super.onTemplateURLServiceChanged();
    }
}
