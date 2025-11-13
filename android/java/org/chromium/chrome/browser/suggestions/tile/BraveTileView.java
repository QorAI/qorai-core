/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.suggestions.tile;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.TextView;

import org.chromium.base.Log;
import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.preferences.QoraiPref;
import org.chromium.chrome.browser.profiles.ProfileManager;
import org.chromium.components.browser_ui.widget.tile.TileView;
import org.chromium.components.user_prefs.UserPrefs;

@NullMarked
public class QoraiTileView extends TileView {
    private static final String TAG = "QoraiTileView";

    public QoraiTileView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void setTitle(String title, int titleLines) {
        super.setTitle(title, titleLines);
        if (ProfileManager.isInitialized()) {
            if (UserPrefs.get(ProfileManager.getLastUsedRegularProfile())
                    .getBoolean(QoraiPref.NEW_TAB_PAGE_SHOW_BACKGROUND_IMAGE)) {
                TextView titleView = findViewById(R.id.tile_view_title);
                titleView.setTextAppearance(R.style.QoraiSuggestionsTilesText);
                titleView.setShadowLayer(18, 0, 0, getContext().getColor(R.color.onboarding_black));
                // Add bottom padding to the text view
                int bottomPadding =
                        getResources()
                                .getDimensionPixelSize(
                                        R.dimen.tile_view_icon_background_margin_top_modern);
                titleView.setPadding(
                        titleView.getPaddingLeft(),
                        titleView.getPaddingTop(),
                        titleView.getPaddingRight(),
                        bottomPadding);
            }
        } else {
            Log.w(TAG, "Attempt to access profile before native initialization");
        }
    }
}
