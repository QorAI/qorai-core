/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.os.Bundle;
import android.widget.Toast;

import androidx.preference.Preference;
import androidx.preference.Preference.OnPreferenceChangeListener;

import org.chromium.base.ContextUtils;
import org.chromium.base.ThreadUtils;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.base.task.AsyncTask;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.local_database.DatabaseHelper;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.components.browser_ui.settings.ChromeSwitchPreference;
import org.chromium.components.browser_ui.settings.SettingsUtils;

/**
 * Fragment to keep track of all the display related preferences.
 */
public class QoraiStatsPreferences extends QoraiPreferenceFragment
    implements OnPreferenceChangeListener {

    // deprecated preferences from browser-android-tabs
    public static final String PREF_QORAI_STATS = "qorai_stats";
    public static final String PREF_QORAI_STATS_NOTIFICATION = "qorai_stats_notification";
    public static final String PREF_CLEAR_QORAI_STATS = "clear_qorai_stats";

    private ChromeSwitchPreference mQoraiStatsPref;
    private ChromeSwitchPreference mQoraiStatsNotificationPref;

    private final DatabaseHelper mDatabaseHelper = DatabaseHelper.getInstance();

    private final ObservableSupplierImpl<String> mPageTitle = new ObservableSupplierImpl<>();

    public static int getPreferenceSummary() {
        return OnboardingPrefManager.getInstance().isQoraiStatsEnabled()
                ? R.string.text_on
                : R.string.text_off;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mPageTitle.set(getString(R.string.qorai_stats));
        SettingsUtils.addPreferencesFromResource(this, R.xml.qorai_stats_preferences);
        findPreference(PREF_CLEAR_QORAI_STATS)
                .setOnPreferenceClickListener(
                        new Preference.OnPreferenceClickListener() {
                            @Override
                            public boolean onPreferenceClick(Preference preference) {
                                new AsyncTask<Void>() {
                                    @Override
                                    protected Void doInBackground() {
                                        try {
                                            mDatabaseHelper.clearStatsTable();
                                            mDatabaseHelper.clearSavedBandwidthTable();
                                        } catch (Exception e) {
                                            // Do nothing if url is invalid.
                                            // Just return w/o showing shields popup.
                                            return null;
                                        }
                                        return null;
                                    }

                                    @Override
                                    protected void onPostExecute(Void result) {
                                        assert ThreadUtils.runningOnUiThread();
                                        if (isCancelled()) return;
                                        Toast.makeText(
                                                        ContextUtils.getApplicationContext(),
                                                        ContextUtils.getApplicationContext()
                                                                .getResources()
                                                                .getString(
                                                                        R.string
                                                                                .data_has_been_cleared),
                                                        Toast.LENGTH_SHORT)
                                                .show();
                                    }
                                }.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                                return true;
                            }
                        });
    }

    @Override
    public ObservableSupplier<String> getPageTitle() {
        return mPageTitle;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mQoraiStatsPref = (ChromeSwitchPreference) findPreference(PREF_QORAI_STATS);
        if (mQoraiStatsPref != null) {
            mQoraiStatsPref.setEnabled(true);
            mQoraiStatsPref.setChecked(OnboardingPrefManager.getInstance().isQoraiStatsEnabled());
            mQoraiStatsPref.setOnPreferenceChangeListener(this);
        }
        mQoraiStatsNotificationPref =
                (ChromeSwitchPreference) findPreference(PREF_QORAI_STATS_NOTIFICATION);
        if (mQoraiStatsNotificationPref != null) {
            mQoraiStatsNotificationPref.setEnabled(true);
            mQoraiStatsNotificationPref.setChecked(
                    OnboardingPrefManager.getInstance().isQoraiStatsNotificationEnabled());
            mQoraiStatsNotificationPref.setOnPreferenceChangeListener(this);
        }
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        setOnPreferenceValue(preference.getKey(), (boolean)newValue);
        return true;
    }

    public static void setOnPreferenceValue(String preferenceName, boolean newValue) {
        if (PREF_QORAI_STATS.equals(preferenceName)) {
            OnboardingPrefManager.getInstance().setQoraiStatsEnabled((boolean) newValue);
        } else if (PREF_QORAI_STATS_NOTIFICATION.equals(preferenceName)) {
            OnboardingPrefManager.getInstance()
                    .setQoraiStatsNotificationEnabled((boolean) newValue);
        } else {
            assert false : "Unexpected preferenceName " + preferenceName;
        }
    }
}
