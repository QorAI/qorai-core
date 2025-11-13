/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSingleWebsiteSettingsClassAdapter extends QoraiClassVisitor {
    static String sSingleWebsiteSettingsClassName =
            "org/chromium/components/browser_ui/site_settings/SingleWebsiteSettings";
    static String sQoraiSingleWebsiteSettingsClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiSingleWebsiteSettings";

    public QoraiSingleWebsiteSettingsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sSingleWebsiteSettingsClassName, sQoraiSingleWebsiteSettingsClassName);

        changeMethodOwner(sSingleWebsiteSettingsClassName, "getPreferenceKey",
                sQoraiSingleWebsiteSettingsClassName);
        changeMethodOwner(sSingleWebsiteSettingsClassName, "setupContentSettingsPreferences",
                sQoraiSingleWebsiteSettingsClassName);

        makePublicMethod(sSingleWebsiteSettingsClassName, "setupContentSettingsPreference");
        changeMethodOwner(sQoraiSingleWebsiteSettingsClassName, "setupContentSettingsPreference",
                sSingleWebsiteSettingsClassName);
    }
}
