/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.tabmodel;

import android.app.Activity;
import android.os.Build;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.base.supplier.OneshotSupplier;
import org.chromium.build.annotations.Nullable;
import org.chromium.chrome.browser.ChromeTabbedActivity;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.compositor.CompositorViewHolder;
import org.chromium.chrome.browser.multiwindow.MultiInstanceManager;
import org.chromium.chrome.browser.ntp_background_images.util.SponsoredImageUtil;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.profiles.ProfileManager;
import org.chromium.chrome.browser.profiles.ProfileProvider;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabDelegateFactory;
import org.chromium.chrome.browser.tab.TabLaunchType;
import org.chromium.components.embedder_support.util.UrlConstants;
import org.chromium.components.user_prefs.UserPrefs;
import org.chromium.ui.base.WindowAndroid;

import java.util.function.Supplier;

public class QoraiTabCreator extends ChromeTabCreator {
    public QoraiTabCreator(
            Activity activity,
            WindowAndroid nativeWindow,
            Supplier<TabDelegateFactory> tabDelegateFactory,
            OneshotSupplier<ProfileProvider> profileProviderSupplier,
            boolean incognito,
            AsyncTabParamsManager asyncTabParamsManager,
            Supplier<TabModelSelector> tabModelSelectorSupplier,
            Supplier<CompositorViewHolder> compositorViewHolderSupplier,
            @Nullable MultiInstanceManager multiInstanceManager) {
        super(
                activity,
                nativeWindow,
                tabDelegateFactory,
                profileProviderSupplier,
                incognito,
                asyncTabParamsManager,
                tabModelSelectorSupplier,
                compositorViewHolderSupplier,
                multiInstanceManager);
    }

    @Override
    public Tab launchUrl(String url, @TabLaunchType int type) {
        if (url.equals(UrlConstants.NTP_URL)
                && (type == TabLaunchType.FROM_CHROME_UI
                        || type == TabLaunchType.FROM_STARTUP
                        || type == TabLaunchType.FROM_TAB_SWITCHER_UI)) {
            ChromeTabbedActivity chromeTabbedActivity = QoraiActivity.getChromeTabbedActivity();
            if (chromeTabbedActivity != null && Build.VERSION.SDK_INT <= Build.VERSION_CODES.M) {
                TabModel tabModel = chromeTabbedActivity.getCurrentTabModel();
                if (tabModel.getCount() >= SponsoredImageUtil.MAX_TABS
                        && UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                                .getBoolean(QoraiPref.NEW_TAB_PAGE_SHOW_BACKGROUND_IMAGE)) {
                    Tab tab =
                            QoraiActivity.class
                                    .cast(chromeTabbedActivity)
                                    .selectExistingTab(UrlConstants.NTP_URL);
                    if (tab != null) {
                        QoraiReflectionUtil.invokeMethod(
                                ChromeTabbedActivity.class,
                                chromeTabbedActivity,
                                "hideOverview",
                                boolean.class,
                                false);
                        return tab;
                    }
                }
            }
        }
        return super.launchUrl(url, type);
    }
}
