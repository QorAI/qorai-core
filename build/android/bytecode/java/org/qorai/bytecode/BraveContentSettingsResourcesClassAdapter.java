/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiContentSettingsResourcesClassAdapter extends QoraiClassVisitor {
    static String sContentSettingsResourcesClassName =
            "org/chromium/components/browser_ui/site_settings/ContentSettingsResources";
    static String sQoraiContentSettingsResourcesClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiContentSettingsResources";
    static String sContentSettingsResourcesResourceItemClassName =
            "org/chromium/components/browser_ui/site_settings/ContentSettingsResources$ResourceItem";
    static String sQoraiContentSettingsResourcesResourceItemClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiContentSettingsResources$ResourceItem";

    public QoraiContentSettingsResourcesClassAdapter(ClassVisitor visitor) {
        super(visitor);

        makePublicMethod(sContentSettingsResourcesClassName, "getResourceItem");
        changeMethodOwner(sContentSettingsResourcesClassName, "getResourceItem",
                sQoraiContentSettingsResourcesClassName);
        makePublicInnerClass(sContentSettingsResourcesClassName, "ResourceItem");
        redirectConstructor(sQoraiContentSettingsResourcesResourceItemClassName,
                sContentSettingsResourcesResourceItemClassName);
        redirectTypeInMethod(sQoraiContentSettingsResourcesClassName, "getResourceItem",
                sQoraiContentSettingsResourcesResourceItemClassName,
                sContentSettingsResourcesResourceItemClassName);
    }
}
