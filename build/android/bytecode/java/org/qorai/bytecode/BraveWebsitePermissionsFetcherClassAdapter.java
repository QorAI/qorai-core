/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiWebsitePermissionsFetcherClassAdapter extends QoraiClassVisitor {
    static String sWebsitePermissionsFetcherClassName =
            "org/chromium/components/browser_ui/site_settings/WebsitePermissionsFetcher";
    static String sQoraiWebsitePermissionsFetcherClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiWebsitePermissionsFetcher";

    public QoraiWebsitePermissionsFetcherClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(sWebsitePermissionsFetcherClassName, "getPermissionsType",
                sQoraiWebsitePermissionsFetcherClassName);
    }
}
