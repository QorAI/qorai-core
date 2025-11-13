/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.ntp;

import android.app.Activity;

import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.QoraiRewardsHelper;
import org.chromium.chrome.browser.infobar.QoraiInfoBarIdentifier;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.ui.messages.infobar.QoraiSimpleConfirmInfoBarBuilder;
import org.chromium.chrome.browser.ui.messages.infobar.SimpleConfirmInfoBarBuilder;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.components.prefs.PrefService;
import org.chromium.components.user_prefs.UserPrefs;
import org.chromium.content_public.browser.WebContents;

@NullMarked
public class QoraiNewTabTakeoverInfobar {
    private static final String TAG = "NewTabTakeover";
    private static final String LEARN_MORE_URL =
            "https://support.qorai.app/hc/en-us/articles/35182999599501";
    private final Profile mProfile;

    public QoraiNewTabTakeoverInfobar(Profile profile) {
        mProfile = profile;
    }

    public void maybeDisplayAndIncrementCounter(Activity activity, WebContents webContents) {
        if (!shouldDisplayInfobar()) {
            return;
        }
        recordInfobarWasDisplayed();

        QoraiSimpleConfirmInfoBarBuilder.create(
                webContents,
                new SimpleConfirmInfoBarBuilder.Listener() {
                    @Override
                    public void onInfoBarDismissed() {
                        suppressInfobar();
                    }

                    @Override
                    public boolean onInfoBarButtonClicked(boolean isPrimary) {
                        suppressInfobar();
                        return false;
                    }

                    @Override
                    public boolean onInfoBarLinkClicked() {
                        suppressInfobar();
                        TabUtils.openUrlInNewTab(/* isIncognito= */ false, LEARN_MORE_URL);
                        // Return false to immediately close the infobar. This is different
                        // from ConfirmInfoBarDelegate where we return true to close the
                        // infobar.
                        return false;
                    }
                },
                QoraiInfoBarIdentifier.NEW_TAB_TAKEOVER_INFOBAR_DELEGATE,
                activity,
                /* drawableId= */ 0,
                activity.getString(R.string.new_tab_takeover_infobar_message, ""),
                /* primaryText= */ "",
                /* secondaryText= */ "",
                activity.getString(
                        R.string.new_tab_takeover_infobar_learn_more_opt_out_choices, ""),
                /* autoExpire= */ true);
    }

    private boolean shouldDisplayInfobar() {
        if (QoraiRewardsHelper.isRewardsEnabled()) {
            return false;
        }

        PrefService prefService = UserPrefs.get(mProfile);
        final int infobarDisplayCount =
                prefService.getInteger(QoraiPref.NEW_TAB_TAKEOVER_INFOBAR_REMAINING_DISPLAY_COUNT);
        return infobarDisplayCount > 0;
    }

    private void recordInfobarWasDisplayed() {
        PrefService prefService = UserPrefs.get(mProfile);
        final int infobarDisplayCount =
                prefService.getInteger(QoraiPref.NEW_TAB_TAKEOVER_INFOBAR_REMAINING_DISPLAY_COUNT);
        prefService.setInteger(
                QoraiPref.NEW_TAB_TAKEOVER_INFOBAR_REMAINING_DISPLAY_COUNT,
                infobarDisplayCount - 1);
    }

    private void suppressInfobar() {
        PrefService prefService = UserPrefs.get(mProfile);
        prefService.setInteger(QoraiPref.NEW_TAB_TAKEOVER_INFOBAR_REMAINING_DISPLAY_COUNT, 0);
    }
}
