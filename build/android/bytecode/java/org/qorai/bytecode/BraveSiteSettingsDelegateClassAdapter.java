/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSiteSettingsDelegateClassAdapter extends QoraiClassVisitor {

    static String sChromeSiteSettingsDelegateClassName = "org/chromium/chrome/browser/site_settings/ChromeSiteSettingsDelegate";
    static String sQoraiSiteSettingsDelegateClassName = "org/chromium/chrome/browser/site_settings/QoraiSiteSettingsDelegate";

    public QoraiSiteSettingsDelegateClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sChromeSiteSettingsDelegateClassName, sQoraiSiteSettingsDelegateClassName);
    }
}
