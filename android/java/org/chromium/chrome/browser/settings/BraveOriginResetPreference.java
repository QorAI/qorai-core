/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.TextView;

import androidx.preference.Preference;
import androidx.preference.PreferenceViewHolder;

import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
import org.chromium.chrome.R;

/** The preference used to reset Qorai Origin settings. */
@NullMarked
public class QoraiOriginResetPreference extends Preference
        implements Preference.OnPreferenceClickListener {
    private static final String TAG = "QoraiOriginResetPreference";

    public QoraiOriginResetPreference(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);

        setOnPreferenceClickListener(this);
    }

    @Override
    public void onBindViewHolder(PreferenceViewHolder holder) {
        super.onBindViewHolder(holder);
        TextView titleView = (TextView) holder.findViewById(android.R.id.title);
        titleView.setTextAppearance(R.style.LargeRegularPrimitiveBlurple40);
    }

    @Override
    public boolean onPreferenceClick(Preference preference) {
        return false;
    }
}
