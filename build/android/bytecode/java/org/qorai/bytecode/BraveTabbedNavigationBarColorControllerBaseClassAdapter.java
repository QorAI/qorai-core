/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTabbedNavigationBarColorControllerBaseClassAdapter extends QoraiClassVisitor {
    static String sTabbedNavigationBarColorControllerClassName =
            "org/chromium/chrome/browser/tabbed_mode/TabbedNavigationBarColorController";
    static String sQoraiTabbedNavigationBarColorControllerBaseClassName =
            "org/chromium/chrome/browser/tabbed_mode/QoraiTabbedNavigationBarColorControllerBase";

    public QoraiTabbedNavigationBarColorControllerBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(
                sTabbedNavigationBarColorControllerClassName,
                sQoraiTabbedNavigationBarColorControllerBaseClassName);

        deleteField(sTabbedNavigationBarColorControllerClassName, "mContext");

        deleteField(sTabbedNavigationBarColorControllerClassName, "mActiveTab");

        deleteField(sTabbedNavigationBarColorControllerClassName, "mTabModelSelector");

        changeMethodOwner(
                sTabbedNavigationBarColorControllerClassName,
                "getNavigationBarColor",
                sQoraiTabbedNavigationBarColorControllerBaseClassName);

        changeMethodOwner(
                sTabbedNavigationBarColorControllerClassName,
                "useActiveTabColor",
                sQoraiTabbedNavigationBarColorControllerBaseClassName);
    }
}
