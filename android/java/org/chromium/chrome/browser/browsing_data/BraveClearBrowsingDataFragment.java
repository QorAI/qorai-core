/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.browsing_data;

import android.os.Bundle;
import android.text.SpannableString;
import android.view.View;

import org.chromium.base.Callback;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.QoraiAdsNativeHelper;
import org.chromium.chrome.browser.QoraiRewardsHelper;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraMojomHelper;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.components.browser_ui.settings.ClickableSpansTextMessagePreference;
import org.chromium.components.browser_ui.settings.SpinnerPreference;
import org.chromium.ui.text.ChromeClickableSpan;
import org.chromium.ui.text.SpanApplier;
import org.chromium.ui.text.SpanApplier.SpanInfo;

public class QoraiClearBrowsingDataFragment extends ClearBrowsingDataFragment {
    ClearBrowsingDataCheckBoxPreference mClearAIChatDataCheckBoxPreference;

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        super.onCreatePreferences(savedInstanceState, rootKey);

        getPreferenceScreen().addPreference(buildClearQoraAIHistory());
        getPreferenceScreen()
                .addPreference(
                        QoraiRewardsHelper.isRewardsEnabled()
                                ? buildResetQoraiRewardsDataPref()
                                : buildClearQoraiAdsDataPref());
    }

    private ClearBrowsingDataCheckBoxPreference buildClearQoraAIHistory() {
        mClearAIChatDataCheckBoxPreference =
                new ClearBrowsingDataCheckBoxPreference(getContext(), null);
        mClearAIChatDataCheckBoxPreference.setTitle(R.string.qorai_clear_ai_history_title);
        mClearAIChatDataCheckBoxPreference.setSummary(R.string.qorai_clear_ai_history_summary);
        mClearAIChatDataCheckBoxPreference.setIcon(R.drawable.ic_qorai_ai);

        return mClearAIChatDataCheckBoxPreference;
    }

    private ClickableSpansTextMessagePreference buildResetQoraiRewardsDataPref() {
        SpannableString resetQoraiRewardsDataText =
                SpanApplier.applySpans(
                        getContext().getString(R.string.reset_qorai_rewards_data),
                        new SpanInfo(
                                "<link1>",
                                "</link1>",
                                new ChromeClickableSpan(
                                        requireContext(), resetQoraiRewardsDataCallback())));

        ClickableSpansTextMessagePreference resetQoraiRewardsDataPref =
                new ClickableSpansTextMessagePreference(getContext(), null);
        resetQoraiRewardsDataPref.setSummary(resetQoraiRewardsDataText);
        return resetQoraiRewardsDataPref;
    }

    private ClickableSpansTextMessagePreference buildClearQoraiAdsDataPref() {
        SpannableString clearQoraiAdsDataText =
                SpanApplier.applySpans(
                        getContext().getString(R.string.clear_qorai_ads_data),
                        new SpanInfo(
                                "<link1>",
                                "</link1>",
                                new ChromeClickableSpan(
                                        requireContext(), clearQoraiAdsDataCallback())));

        ClickableSpansTextMessagePreference clearQoraiAdsDataPref =
                new ClickableSpansTextMessagePreference(getContext(), null);
        clearQoraiAdsDataPref.setSummary(clearQoraiAdsDataText);
        return clearQoraiAdsDataPref;
    }

    private Callback<View> resetQoraiRewardsDataCallback() {
        return (view) -> {
            try {
                TabUtils.openUrlInNewTab(false, QoraiActivity.QORAI_REWARDS_RESET_PAGE);
                TabUtils.bringChromeTabbedActivityToTheTop(QoraiActivity.getQoraiActivity());
            } catch (QoraiActivity.QoraiActivityNotFoundException e) {
            }
        };
    }

    private Callback<View> clearQoraiAdsDataCallback() {
        return (view) -> {
            Profile profile = getProfile();
            if (profile != null) {
                QoraiAdsNativeHelper.nativeClearData(profile);
            }

            if (getActivity() != null) {
                getActivity().finish();
            }
        };
    }

    @Override
    protected void onClearBrowsingData() {
        super.onClearBrowsingData();

        if (mClearAIChatDataCheckBoxPreference != null
                && mClearAIChatDataCheckBoxPreference.isChecked()) {
            Profile profile = getProfile();
            if (profile == null) {
                return;
            }
            Object spinnerSelection =
                    ((SpinnerPreference) findPreference(PREF_TIME_RANGE)).getSelectedOption();
            @TimePeriod
            int lastSelectedTimePeriod =
                    ((TimePeriodUtils.TimePeriodSpinnerOption) spinnerSelection).getTimePeriod();

            QoraiQoraMojomHelper.getInstance(profile).deleteConversations(lastSelectedTimePeriod);
        }
    }
}
