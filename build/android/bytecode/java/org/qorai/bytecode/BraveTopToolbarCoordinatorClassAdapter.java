/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTopToolbarCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sTopToolbarCoordinatorClassName =
            "org/chromium/chrome/browser/toolbar/top/TopToolbarCoordinator";
    static String sQoraiTopToolbarCoordinatorClassName =
            "org/chromium/chrome/browser/toolbar/top/QoraiTopToolbarCoordinator";

    public QoraiTopToolbarCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sTopToolbarCoordinatorClassName, sQoraiTopToolbarCoordinatorClassName);

        deleteField(sQoraiTopToolbarCoordinatorClassName, "mOptionalButtonController");
        makeProtectedField(sTopToolbarCoordinatorClassName, "mOptionalButtonController");
    }
}
