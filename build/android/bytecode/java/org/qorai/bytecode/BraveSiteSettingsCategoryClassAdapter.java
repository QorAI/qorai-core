/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSiteSettingsCategoryClassAdapter extends QoraiClassVisitor {
    static String sSiteSettingsCategoryClassName =
            "org/chromium/components/browser_ui/site_settings/SiteSettingsCategory";
    static String sQoraiSiteSettingsCategoryClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiSiteSettingsCategory";

    public QoraiSiteSettingsCategoryClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(sSiteSettingsCategoryClassName, "contentSettingsType",
                sQoraiSiteSettingsCategoryClassName);
        changeMethodOwner(sSiteSettingsCategoryClassName, "preferenceKey",
                sQoraiSiteSettingsCategoryClassName);
    }
}
