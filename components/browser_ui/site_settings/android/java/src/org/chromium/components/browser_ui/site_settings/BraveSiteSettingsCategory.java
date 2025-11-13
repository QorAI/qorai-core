/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.browser_ui.site_settings;

import org.chromium.components.browser_ui.site_settings.SiteSettingsCategory.Type;
import org.chromium.components.content_settings.ContentSettingsType;

public class QoraiSiteSettingsCategory {
    public static int contentSettingsType(@Type int type) {
        switch (type) {
            case Type.AUTOPLAY:
                return ContentSettingsType.AUTOPLAY;
            case Type.QORAI_GOOGLE_SIGN_IN:
                return ContentSettingsType.QORAI_GOOGLE_SIGN_IN;
            case Type.QORAI_LOCALHOST_ACCESS:
                return ContentSettingsType.QORAI_LOCALHOST_ACCESS;
            default:
                return SiteSettingsCategory.contentSettingsType(type);
        }
    }

    public static String preferenceKey(@Type int type) {
        switch (type) {
            case Type.AUTOPLAY:
                return "autoplay";
            case Type.QORAI_GOOGLE_SIGN_IN:
                return "qorai_google_sign_in";
            case Type.QORAI_LOCALHOST_ACCESS:
                return "qorai_localhost_access";
            default:
                return SiteSettingsCategory.preferenceKey(type);
        }
    }
}
