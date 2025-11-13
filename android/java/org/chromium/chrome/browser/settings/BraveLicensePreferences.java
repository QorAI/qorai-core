/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.settings;

import android.os.Bundle;

import org.chromium.base.Log;
import org.chromium.base.supplier.ObservableSupplier;
import org.chromium.base.supplier.ObservableSupplierImpl;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.QoraiRewardsHelper;
import org.chromium.components.browser_ui.settings.SettingsUtils;

import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;

/**
 * Fragment to display Qorai license information.
 */
public class QoraiLicensePreferences extends QoraiPreferenceFragment {
    private static final String TAG = "QoraiLicense";

    private static final String PREF_QORAI_LICENSE_TEXT = "qorai_license_text";
    private static final String ASSET_QORAI_LICENSE = "LICENSE.html";

    private final ObservableSupplierImpl<String> mPageTitle = new ObservableSupplierImpl<>();

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String s) {
        // These strings are not used in Qorai, but we get them from automated string translation
        // process. These checks are just making sure that strings are still used in Chromium to
        // avoid lint issues.
        assert R.string.chrome_additional_terms_of_service_title > 0
                : "Something has changed in the upstream!";
        assert R.string.google_privacy_policy_url > 0 : "Something has changed in the upstream!";
        assert R.string.sync_reading_list > 0 : "Something has changed in the upstream!";

        SettingsUtils.addPreferencesFromResource(this, R.xml.qorai_license_preferences);
        mPageTitle.set(getString(R.string.qorai_license_text));
        QoraiLicensePreference licenseText =
                (QoraiLicensePreference) findPreference(PREF_QORAI_LICENSE_TEXT);
        try {
            InputStream in = getActivity().getAssets().open(ASSET_QORAI_LICENSE);
            Scanner scanner = new Scanner(in).useDelimiter("\\A");
            String summary = scanner.hasNext() ? scanner.next() : "";
            in.close();
            licenseText.setSummary(QoraiRewardsHelper.spannedFromHtmlString(summary));
        } catch (IOException e) {
            Log.e(TAG, "Could not load license text: " + e);
        }
    }

    @Override
    public ObservableSupplier<String> getPageTitle() {
        return mPageTitle;
    }
}
