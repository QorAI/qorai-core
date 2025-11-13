/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiIdentityDiscControllerClassAdapter extends QoraiClassVisitor {
    static String sIdentityDiscControllerClassName =
            "org/chromium/chrome/browser/identity_disc/IdentityDiscController";
    static String sQoraiIdentityDiscControllerClassName =
            "org/chromium/chrome/browser/identity_disc/QoraiIdentityDiscController";

    public QoraiIdentityDiscControllerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sIdentityDiscControllerClassName, sQoraiIdentityDiscControllerClassName);

        makePublicMethod(sIdentityDiscControllerClassName, "calculateButtonData");
        addMethodAnnotation(
                sQoraiIdentityDiscControllerClassName,
                "calculateButtonData",
                "Ljava/lang/Override;");
    }
}
