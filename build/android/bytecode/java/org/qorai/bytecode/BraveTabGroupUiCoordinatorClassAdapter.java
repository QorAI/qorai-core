/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTabGroupUiCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sTabGroupUiCoordinatorClassName =
            "org/chromium/chrome/browser/tasks/tab_management/TabGroupUiCoordinator";
    static String sQoraiTabGroupUiCoordinatorClassName =
            "org/chromium/chrome/browser/tasks/tab_management/QoraiTabGroupUiCoordinator";

    public QoraiTabGroupUiCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sTabGroupUiCoordinatorClassName, sQoraiTabGroupUiCoordinatorClassName);

        deleteField(sQoraiTabGroupUiCoordinatorClassName, "mToolbarView");
        makeProtectedField(sTabGroupUiCoordinatorClassName, "mToolbarView");
    }
}
