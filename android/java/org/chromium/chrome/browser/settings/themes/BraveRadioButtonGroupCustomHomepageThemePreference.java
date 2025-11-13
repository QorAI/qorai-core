/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings.themes;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.RadioGroup;

import androidx.preference.PreferenceViewHolder;

import org.chromium.chrome.browser.QoraiRelaunchUtils;
import org.chromium.chrome.browser.night_mode.R;
import org.chromium.chrome.browser.night_mode.settings.RadioButtonGroupThemePreference;
import org.chromium.chrome.browser.ntp_background_images.NTPBackgroundImagesBridge;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.profiles.ProfileManager;
import org.chromium.components.browser_ui.widget.RadioButtonWithDescription;
import org.chromium.components.user_prefs.UserPrefs;

public class QoraiRadioButtonGroupCustomHomepageThemePreference
        extends RadioButtonGroupThemePreference {

    private final NTPBackgroundImagesBridge mNTPBackgroundImagesBridge;

    public QoraiRadioButtonGroupCustomHomepageThemePreference(Context context, AttributeSet attrs) {
        super(context, attrs);
        Profile mProfile = ProfileManager.getLastUsedRegularProfile();
        mNTPBackgroundImagesBridge = NTPBackgroundImagesBridge.getInstance(mProfile);
    }

    @Override
    public void onBindViewHolder(PreferenceViewHolder holder) {
        super.onBindViewHolder(holder);

        holder.findViewById(R.id.system_default).setVisibility(View.GONE);

        RadioButtonWithDescription qoraiDefaultView = (RadioButtonWithDescription)holder.findViewById(R.id.light);
        RadioButtonWithDescription refView = (RadioButtonWithDescription)holder.findViewById(R.id.dark);
        if (mNTPBackgroundImagesBridge != null && mNTPBackgroundImagesBridge.isSuperReferral()) {
            refView.setPrimaryText(mNTPBackgroundImagesBridge.getSuperReferralThemeName());
            if (UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                            .getInteger(QoraiPref.NEW_TAB_PAGE_SUPER_REFERRAL_THEMES_OPTION)
                    == 1) {
                refView.setChecked(true);
                qoraiDefaultView.setChecked(false);
            } else {
                refView.setChecked(false);
                qoraiDefaultView.setChecked(true);
            }
        }
        qoraiDefaultView.setPrimaryText(
                getContext().getResources().getString(org.chromium.chrome.R.string.qorai_default));
    }

    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {
        super.onCheckedChanged(group, checkedId);
        UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                .setInteger(
                        QoraiPref.NEW_TAB_PAGE_SUPER_REFERRAL_THEMES_OPTION,
                        checkedId == R.id.light ? 0 : 1);
        QoraiRelaunchUtils.askForRelaunch(getContext());
    }
}
