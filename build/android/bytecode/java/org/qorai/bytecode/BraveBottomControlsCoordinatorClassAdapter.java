/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBottomControlsCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sBottomControlsCoordinatorClassName =
            "org/chromium/chrome/browser/toolbar/bottom/BottomControlsCoordinator";
    static String sQoraiBottomControlsCoordinatorClassName =
            "org/chromium/chrome/browser/toolbar/bottom/QoraiBottomControlsCoordinator";

    public QoraiBottomControlsCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiBottomControlsCoordinatorClassName, "mMediator");
        makeProtectedField(sBottomControlsCoordinatorClassName, "mMediator");
    }
}
