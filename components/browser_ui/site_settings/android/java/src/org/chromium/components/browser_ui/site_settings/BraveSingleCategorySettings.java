/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.browser_ui.site_settings;

import android.os.Bundle;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.build.annotations.UsedByReflection;

@UsedByReflection("qorai_site_settings_preferences.xml")
public class QoraiSingleCategorySettings extends BaseSiteSettingsFragment
        implements AddExceptionPreference.SiteAddedCallback {
    private static final String ADD_EXCEPTION_KEY = "add_exception";

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {}

    public int getAddExceptionDialogMessageResourceId() {
        int resource = 0;
        SiteSettingsCategory mCategory =
                (SiteSettingsCategory)
                        QoraiReflectionUtil.getField(
                                SingleCategorySettings.class, "mCategory", this);

        if (mCategory.getType() == SiteSettingsCategory.Type.AUTOPLAY) {
            resource = R.string.website_settings_add_site_description_autoplay;
        } else if (mCategory.getType() == SiteSettingsCategory.Type.QORAI_GOOGLE_SIGN_IN) {
            resource = R.string.website_settings_google_sign_in_allow_exceptions;
        } else if (mCategory.getType() == SiteSettingsCategory.Type.QORAI_LOCALHOST_ACCESS) {
            resource = R.string.website_settings_localhost_allow_exceptions;
        } else {
            return (int)
                    QoraiReflectionUtil.invokeMethod(
                            SingleCategorySettings.class,
                            this,
                            "getAddExceptionDialogMessageResourceId");
        }
        assert resource > 0;
        return resource;
    }

    public void resetList() {
        QoraiReflectionUtil.invokeMethod(SingleCategorySettings.class, this, "resetList");
        boolean exception = false;
        SiteSettingsCategory mCategory =
                (SiteSettingsCategory)
                        QoraiReflectionUtil.getField(
                                SingleCategorySettings.class, "mCategory", this);

        if (mCategory.getType() == SiteSettingsCategory.Type.AUTOPLAY
                || mCategory.getType() == SiteSettingsCategory.Type.QORAI_GOOGLE_SIGN_IN
                || mCategory.getType() == SiteSettingsCategory.Type.QORAI_LOCALHOST_ACCESS) {
            exception = true;
        }
        if (exception) {
            boolean enableAddExceptionButton = !mCategory.isManaged();
            getPreferenceScreen()
                    .addPreference(
                            new AddExceptionPreference(
                                    getPreferenceManager().getContext(),
                                    ADD_EXCEPTION_KEY,
                                    getString(getAddExceptionDialogMessageResourceId()),
                                    enableAddExceptionButton,
                                    mCategory,
                                    this));
        }
    }

    @Override
    public void onAddSite(String primaryPattern, String secondaryPattern) {
        assert false;
    }
}
