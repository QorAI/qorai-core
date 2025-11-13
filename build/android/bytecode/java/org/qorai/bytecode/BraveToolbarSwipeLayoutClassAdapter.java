/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiToolbarSwipeLayoutClassAdapter extends QoraiClassVisitor {
    static String sToolbarSwipeLayoutClassName =
            "org/chromium/chrome/browser/compositor/layouts/ToolbarSwipeLayout";
    static String sQoraiToolbarSwipeLayoutClassName =
            "org/chromium/chrome/browser/compositor/layouts/QoraiToolbarSwipeLayout";

    public QoraiToolbarSwipeLayoutClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sToolbarSwipeLayoutClassName, sQoraiToolbarSwipeLayoutClassName);

        deleteField(sQoraiToolbarSwipeLayoutClassName, "mMoveToolbar");
        makeProtectedField(sToolbarSwipeLayoutClassName, "mMoveToolbar");
    }
}
