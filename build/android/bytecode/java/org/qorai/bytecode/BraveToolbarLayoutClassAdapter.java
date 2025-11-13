/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiToolbarLayoutClassAdapter extends QoraiClassVisitor {
    static String sCustomTabToolbarClassName =
            "org/chromium/chrome/browser/customtabs/features/toolbar/CustomTabToolbar";
    static String sToolbarPhoneClassName = "org/chromium/chrome/browser/toolbar/top/ToolbarPhone";
    static String sToolbarTabletClassName = "org/chromium/chrome/browser/toolbar/top/ToolbarTablet";
    static String sQoraiToolbarLayoutClassName =
            "org/chromium/chrome/browser/toolbar/top/QoraiToolbarLayoutImpl";

    public QoraiToolbarLayoutClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeSuperName(sCustomTabToolbarClassName, sQoraiToolbarLayoutClassName);

        changeSuperName(sToolbarPhoneClassName, sQoraiToolbarLayoutClassName);

        changeSuperName(sToolbarTabletClassName, sQoraiToolbarLayoutClassName);

        deleteMethod(sToolbarPhoneClassName, "onHomeButtonUpdate");
    }
}
