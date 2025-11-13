/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSiteSettingsPreferencesBaseClassAdapter extends QoraiClassVisitor {
    static String sSiteSettingsClassName =
            "org/chromium/components/browser_ui/site_settings/SiteSettings";
    static String sQoraiSiteSettingsPreferencesBaseClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiSiteSettingsPreferencesBase";

    public QoraiSiteSettingsPreferencesBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sSiteSettingsClassName, sQoraiSiteSettingsPreferencesBaseClassName);
    }
}
