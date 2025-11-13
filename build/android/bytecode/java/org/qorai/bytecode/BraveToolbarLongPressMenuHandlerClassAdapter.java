/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiToolbarLongPressMenuHandlerClassAdapter extends QoraiClassVisitor {
    static String sToolbarLongPressMenuHandlerClassName =
            "org/chromium/chrome/browser/toolbar/ToolbarLongPressMenuHandler";
    static String sQoraiToolbarLongPressMenuHandlerClassName =
            "org/chromium/chrome/browser/toolbar/QoraiToolbarLongPressMenuHandler";

    public QoraiToolbarLongPressMenuHandlerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sToolbarLongPressMenuHandlerClassName, sQoraiToolbarLongPressMenuHandlerClassName);
    }
}
