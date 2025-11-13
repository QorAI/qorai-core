/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBottomControlsMediatorClassAdapter extends QoraiClassVisitor {
    static String sBottomControlsMediatorClassName =
            "org/chromium/chrome/browser/toolbar/bottom/BottomControlsMediator";
    static String sQoraiBottomControlsMediatorClassName =
            "org/chromium/chrome/browser/toolbar/bottom/QoraiBottomControlsMediator";

    public QoraiBottomControlsMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sBottomControlsMediatorClassName, sQoraiBottomControlsMediatorClassName);

        deleteField(sQoraiBottomControlsMediatorClassName, "mModel");
        makeProtectedField(sBottomControlsMediatorClassName, "mModel");

        deleteField(sQoraiBottomControlsMediatorClassName, "mBottomControlsStacker");
        makeProtectedField(sBottomControlsMediatorClassName, "mBottomControlsStacker");
    }
}
