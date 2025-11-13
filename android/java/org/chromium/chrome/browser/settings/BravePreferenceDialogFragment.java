/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.preference.Preference;
import androidx.preference.PreferenceDialogFragmentCompat;

import org.chromium.base.shared_preferences.SharedPreferencesManager;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.preferences.website.QoraiShieldsContentSettings;
import org.chromium.chrome.browser.privacy.settings.QoraiPrivacySettings;
import org.chromium.chrome.browser.profiles.ProfileManager;

public class QoraiPreferenceDialogFragment extends PreferenceDialogFragmentCompat {
    public static final String TAG = "QoraiPreferenceDialogFragment";
    private RadioGroup mRadioGroup;

    private QoraiDialogPreference mDialogPreference;
    private Preference.OnPreferenceChangeListener mOnPreferenceChangeListener;
    private int mNewValue;

    private static String sCurrentPreference;

    public void setPreferenceDialogListener(Preference.OnPreferenceChangeListener listener) {
        this.mOnPreferenceChangeListener = listener;
    }

    @NonNull
    public static QoraiPreferenceDialogFragment newInstance(@NonNull Preference preference) {
        QoraiPreferenceDialogFragment fragment = new QoraiPreferenceDialogFragment();
        Bundle bundle = new Bundle(1);
        bundle.putString(PreferenceDialogFragmentCompat.ARG_KEY, preference.getKey());
        sCurrentPreference = preference.getKey();
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mDialogPreference = (QoraiDialogPreference) getPreference();
    }

    @Override
    public void onDialogClosed(boolean positiveResult) {
        if (mOnPreferenceChangeListener != null) {
            SharedPreferencesManager sharedPreferencesManager =
                    ChromeSharedPreferences.getInstance();
            if (sCurrentPreference.equals(QoraiPrivacySettings.PREF_FINGERPRINTING_PROTECTION)) {
                mOnPreferenceChangeListener.onPreferenceChange(
                        mDialogPreference,
                        QoraiShieldsContentSettings.getShieldsValue(
                                ProfileManager.getLastUsedRegularProfile(),
                                "",
                                QoraiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING));
            } else if (sCurrentPreference.equals(QoraiPrivacySettings.PREF_BLOCK_TRACKERS_ADS)) {
                mOnPreferenceChangeListener.onPreferenceChange(
                        mDialogPreference,
                        QoraiShieldsContentSettings.getShieldsValue(
                                ProfileManager.getLastUsedRegularProfile(),
                                "",
                                QoraiShieldsContentSettings.RESOURCE_IDENTIFIER_TRACKERS));
            } else {
                mOnPreferenceChangeListener.onPreferenceChange(
                        mDialogPreference, sharedPreferencesManager.readInt(sCurrentPreference, 1));
            }
        }
    }

    @Override
    protected void onPrepareDialogBuilder(AlertDialog.Builder builder) {
        super.onPrepareDialogBuilder(builder);
        builder.setCancelable(false);
        if (mRadioGroup != null) {
            mRadioGroup.setOnCheckedChangeListener(
                    new RadioGroup.OnCheckedChangeListener() {
                        @Override
                        public void onCheckedChanged(RadioGroup group, int checkedId) {
                            mNewValue = checkedId;
                            SharedPreferencesManager sharedPreferencesManager =
                                    ChromeSharedPreferences.getInstance();
                            if (sCurrentPreference.equals(
                                    QoraiPrivacySettings.PREF_FINGERPRINTING_PROTECTION)) {
                                if ((int) mNewValue == 0) {
                                    QoraiShieldsContentSettings.setShieldsValue(
                                            ProfileManager.getLastUsedRegularProfile(),
                                            "",
                                            QoraiShieldsContentSettings
                                                    .RESOURCE_IDENTIFIER_FINGERPRINTING,
                                            QoraiShieldsContentSettings.BLOCK_RESOURCE,
                                            false);
                                } else if ((int) mNewValue == 1) {
                                    QoraiShieldsContentSettings.setShieldsValue(
                                            ProfileManager.getLastUsedRegularProfile(),
                                            "",
                                            QoraiShieldsContentSettings
                                                    .RESOURCE_IDENTIFIER_FINGERPRINTING,
                                            QoraiShieldsContentSettings.DEFAULT,
                                            false);
                                } else {
                                    QoraiShieldsContentSettings.setShieldsValue(
                                            ProfileManager.getLastUsedRegularProfile(),
                                            "",
                                            QoraiShieldsContentSettings
                                                    .RESOURCE_IDENTIFIER_FINGERPRINTING,
                                            QoraiShieldsContentSettings.ALLOW_RESOURCE,
                                            false);
                                }
                            } else if (sCurrentPreference.equals(
                                    QoraiPrivacySettings.PREF_BLOCK_TRACKERS_ADS)) {
                                switch ((int) mNewValue) {
                                    case 0:
                                        QoraiShieldsContentSettings.setShieldsValue(
                                                ProfileManager.getLastUsedRegularProfile(),
                                                "",
                                                QoraiShieldsContentSettings
                                                        .RESOURCE_IDENTIFIER_TRACKERS,
                                                QoraiShieldsContentSettings.BLOCK_RESOURCE,
                                                false);
                                        break;
                                    case 1:
                                        QoraiShieldsContentSettings.setShieldsValue(
                                                ProfileManager.getLastUsedRegularProfile(),
                                                "",
                                                QoraiShieldsContentSettings
                                                        .RESOURCE_IDENTIFIER_TRACKERS,
                                                QoraiShieldsContentSettings.DEFAULT,
                                                false);
                                        break;
                                    default:
                                        QoraiShieldsContentSettings.setShieldsValue(
                                                ProfileManager.getLastUsedRegularProfile(),
                                                "",
                                                QoraiShieldsContentSettings
                                                        .RESOURCE_IDENTIFIER_TRACKERS,
                                                QoraiShieldsContentSettings.ALLOW_RESOURCE,
                                                false);
                                        break;
                                }
                            } else {
                                sharedPreferencesManager.writeInt(
                                        sCurrentPreference, (int) mNewValue);
                            }
                        }
                    });
        }

        builder.setPositiveButton(null, null);
        builder.setNegativeButton(getResources().getString(R.string.qorai_sync_btn_done), null);
    }

    @Override
    protected void onBindDialogView(View view) {
        super.onBindDialogView(view);

        String subtitle = mDialogPreference.getDialogSubtitle();
        TextView subTitle = view.findViewById(R.id.summary);
        subTitle.setText(subtitle);
        subTitle.refreshDrawableState();
        mRadioGroup = view.findViewById(R.id.options);
        QoraiDialogPreference.DialogEntry[] dialogEntries = mDialogPreference.getDialogEntries();
        int index = 0;

        for (QoraiDialogPreference.DialogEntry entry : dialogEntries) {
            RadioButton radioButton = new RadioButton(getContext());
            radioButton.setLayoutParams(setParams());
            radioButton.setTextAppearance(R.style.QoraiShieldsBlockCookieModeText);
            radioButton.setText(entry.getEntryText());
            radioButton.setVisibility(entry.isVisible() ? View.VISIBLE : View.GONE);
            radioButton.setId(index);
            if (mRadioGroup != null) {
                mRadioGroup.addView(radioButton);
            }
            if (index == mDialogPreference.getCheckedIndex()) {
                radioButton.setChecked(true);
            }
            index++;
        }
    }

    private RadioGroup.LayoutParams setParams() {
        RadioGroup.LayoutParams params = new RadioGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        float density = getResources().getDisplayMetrics().density;
        params.setMargins((int) (20 * density), (int) (10 * density), (int) (20 * density), 0);
        return params;
    }
}
