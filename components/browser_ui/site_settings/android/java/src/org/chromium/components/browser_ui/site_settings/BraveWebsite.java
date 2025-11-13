/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.components.browser_ui.site_settings;

import org.chromium.base.QoraiReflectionUtil;
import org.chromium.build.annotations.UsedByReflection;
import org.chromium.components.content_settings.ContentSetting;
import org.chromium.components.content_settings.ContentSettingsType;
import org.chromium.components.content_settings.ProviderType;
import org.chromium.content_public.browser.BrowserContextHandle;

@UsedByReflection("Website")
public class QoraiWebsite {
    public void setContentSetting(
            BrowserContextHandle browserContextHandle,
            @ContentSettingsType.EnumType int type,
            @ContentSetting int value) {
        PermissionInfo info =
                (PermissionInfo)
                        QoraiReflectionUtil.invokeMethod(
                                Website.class, this, "getPermissionInfo", int.class, type);
        if (info != null) {
            info.setContentSetting(browserContextHandle, value);
            return;
        }

        ContentSettingException exception =
                (ContentSettingException)
                        QoraiReflectionUtil.invokeMethod(
                                Website.class, this, "getContentSettingException", int.class, type);
        if (type == ContentSettingsType.AUTOPLAY) {
            if (exception == null) {
                exception =
                        new ContentSettingException(
                                ContentSettingsType.AUTOPLAY,
                                ((WebsiteAddress)
                                                QoraiReflectionUtil.invokeMethod(
                                                        Website.class, this, "getAddress"))
                                        .getHost(),
                                value,
                                ProviderType.NONE,
                                false);
                QoraiReflectionUtil.invokeMethod(
                        Website.class,
                        this,
                        "setContentSettingException",
                        int.class,
                        type,
                        ContentSettingException.class,
                        exception);
            }
        } else if (type == ContentSettingsType.QORAI_GOOGLE_SIGN_IN) {
            if (exception == null) {
                exception =
                        new ContentSettingException(
                                ContentSettingsType.QORAI_GOOGLE_SIGN_IN,
                                ((WebsiteAddress)
                                                QoraiReflectionUtil.invokeMethod(
                                                        Website.class, this, "getAddress"))
                                        .getHost(),
                                value,
                                ProviderType.NONE,
                                false);
                QoraiReflectionUtil.invokeMethod(
                        Website.class,
                        this,
                        "setContentSettingException",
                        int.class,
                        type,
                        ContentSettingException.class,
                        exception);
            }
        } else if (type == ContentSettingsType.QORAI_LOCALHOST_ACCESS) {
            if (exception == null) {
                exception =
                        new ContentSettingException(
                                ContentSettingsType.QORAI_LOCALHOST_ACCESS,
                                ((WebsiteAddress)
                                                QoraiReflectionUtil.invokeMethod(
                                                        Website.class, this, "getAddress"))
                                        .getHost(),
                                value,
                                ProviderType.NONE,
                                false);
                QoraiReflectionUtil.invokeMethod(
                        Website.class,
                        this,
                        "setContentSettingException",
                        int.class,
                        type,
                        ContentSettingException.class,
                        exception);
            }
        }

        QoraiReflectionUtil.invokeMethod(
                Website.class,
                this,
                "setContentSetting",
                BrowserContextHandle.class,
                browserContextHandle,
                int.class,
                type,
                int.class,
                value);
    }
}
