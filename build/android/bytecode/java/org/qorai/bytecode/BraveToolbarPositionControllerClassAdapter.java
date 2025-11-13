/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiToolbarPositionControllerClassAdapter extends QoraiClassVisitor {
    static String sToolbarPositionControllerClassName =
            "org/chromium/chrome/browser/toolbar/ToolbarPositionController";
    static String sQoraiToolbarPositionControllerClassName =
            "org/chromium/chrome/browser/toolbar/QoraiToolbarPositionController";

    public QoraiToolbarPositionControllerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sToolbarPositionControllerClassName,
                "calculateStateTransition",
                sQoraiToolbarPositionControllerClassName);
    }
}
