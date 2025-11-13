/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.content.Context;
import android.content.DialogInterface;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.preference.Preference;
import androidx.preference.PreferenceViewHolder;

import org.chromium.base.Log;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.app.QoraiActivity;
import org.chromium.chrome.browser.qoraiqora.QoraiQoraMojomHelper;
import org.chromium.chrome.browser.browsing_data.TimePeriod;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.components.user_prefs.UserPrefs;

/**
 * The preference used to reset Qorai Qora.
 */
public class QoraiQoraResetPreference
        extends Preference implements Preference.OnPreferenceClickListener {
    private static final String TAG = "QoraiQoraResetPref";

    /**
     * Constructor for QoraiQoraResetPreference.
     */
    public QoraiQoraResetPreference(Context context, AttributeSet attrs) {
        super(context, attrs);

        setOnPreferenceClickListener(this);
    }

    @Override
    public void onBindViewHolder(@NonNull PreferenceViewHolder holder) {
        super.onBindViewHolder(holder);
        TextView titleView = (TextView) holder.findViewById(android.R.id.title);
        assert titleView != null;
        titleView.setTextAppearance(R.style.QoraiQoraResetTextColor);
    }

    @Override
    public boolean onPreferenceClick(@NonNull Preference preference) {
        showQoraiQoraResetDialog();
        return true;
    }

    private void showQoraiQoraResetDialog() {
        LayoutInflater inflater =
                (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View view = inflater.inflate(R.layout.qorai_qora_reset_dialog, null);

        DialogInterface.OnClickListener onClickListener =
                (dialog, button) -> {
                    if (button == AlertDialog.BUTTON_POSITIVE) {
                        Profile profile = null;
                        try {
                            QoraiActivity activity = QoraiActivity.getQoraiActivity();
                            profile = activity.getCurrentProfile();
                        } catch (QoraiActivity.QoraiActivityNotFoundException e) {
                            Log.e(TAG, "get QoraiActivity exception", e);
                        }
                        if (profile == null) {
                            Log.e(TAG, "showQoraiQoraResetDialog profile is null");
                            return;
                        }
                        UserPrefs.get(profile).clearPref(QoraiPref.LAST_ACCEPTED_DISCLAIMER);
                        QoraiQoraMojomHelper.getInstance(profile)
                                .deleteConversations(TimePeriod.ALL_TIME);
                    } else {
                        dialog.dismiss();
                    }
                };

        AlertDialog.Builder alert =
                new AlertDialog.Builder(getContext(), R.style.ThemeOverlay_BrowserUI_AlertDialog);
        AlertDialog alertDialog =
                alert.setTitle(R.string.qora_reset_data)
                        .setView(view)
                        .setPositiveButton(R.string.qorai_qora_confirm_text, onClickListener)
                        .setNegativeButton(R.string.cancel, onClickListener)
                        .create();
        alertDialog.getDelegate().setHandleNativeActionModesEnabled(false);
        alertDialog.show();
    }
}
