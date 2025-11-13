/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.browser_ui.site_settings;

import org.chromium.components.browser_ui.site_settings.WebsitePermissionsFetcher.WebsitePermissionsType;
import org.chromium.components.content_settings.ContentSettingsType;

public class QoraiWebsitePermissionsFetcher {
    public static WebsitePermissionsType getPermissionsType(
            @ContentSettingsType.EnumType int contentSettingsType) {
        switch (contentSettingsType) {
            case ContentSettingsType.AUTOPLAY:
            case ContentSettingsType.QORAI_GOOGLE_SIGN_IN:
            case ContentSettingsType.QORAI_LOCALHOST_ACCESS:
                return WebsitePermissionsType.CONTENT_SETTING_EXCEPTION;
            case ContentSettingsType.STORAGE_ACCESS:
                return null;
        }
        return WebsitePermissionsFetcher.getPermissionsType(contentSettingsType);
    }
}
