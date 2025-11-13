/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiStatusBarColorControllerClassAdapter extends QoraiClassVisitor {
    static String sStatusBarColorControllerClassName =
            "org/chromium/chrome/browser/ui/system/StatusBarColorController";
    static String sQoraiStatusBarColorControllerClassName =
            "org/chromium/chrome/browser/ui/system/QoraiStatusBarColorController";

    public QoraiStatusBarColorControllerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sStatusBarColorControllerClassName, sQoraiStatusBarColorControllerClassName);

        deleteField(sQoraiStatusBarColorControllerClassName, "mBackgroundColorForNtp");
        makeProtectedField(sStatusBarColorControllerClassName, "mBackgroundColorForNtp");
    }
}
