/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMultiWindowUtilsClassAdapter extends QoraiClassVisitor {
    static String sMultiWindowUtilsClassName =
            "org/chromium/chrome/browser/multiwindow/MultiWindowUtils";
    static String sQoraiMultiWindowUtilsClassName =
            "org/chromium/chrome/browser/multiwindow/QoraiMultiWindowUtils";

    public QoraiMultiWindowUtilsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sMultiWindowUtilsClassName, sQoraiMultiWindowUtilsClassName);
        changeMethodOwner(
                sMultiWindowUtilsClassName,
                "shouldShowManageWindowsMenu",
                sQoraiMultiWindowUtilsClassName);
    }
}
