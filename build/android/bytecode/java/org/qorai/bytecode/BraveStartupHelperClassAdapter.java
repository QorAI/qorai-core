/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiStartupHelperClassAdapter extends QoraiClassVisitor {
    static String sStartupHelperClassName =
            "org/chromium/chrome/browser/tab_group_sync/StartupHelper";
    static String sQoraiStartupHelperClassName =
            "org/chromium/chrome/browser/tab_group_sync/QoraiStartupHelper";

    public QoraiStartupHelperClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sStartupHelperClassName, sQoraiStartupHelperClassName);
        changeMethodOwner(
                sStartupHelperClassName,
                "handleUnsavedLocalTabGroups",
                sQoraiStartupHelperClassName);
    }
}
