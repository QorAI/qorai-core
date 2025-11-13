/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAppMenuClassAdapter extends QoraiClassVisitor {
    static String sAppMenuClassName = "org/chromium/chrome/browser/ui/appmenu/AppMenu";

    static String sQoraiAppMenuClassName = "org/chromium/chrome/browser/ui/appmenu/QoraiAppMenu";

    public QoraiAppMenuClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sQoraiAppMenuClassName, sAppMenuClassName);

        redirectConstructor(sAppMenuClassName, sQoraiAppMenuClassName);

        changeMethodOwner(sAppMenuClassName, "getPopupPosition", sQoraiAppMenuClassName);

        makePublicMethod(sAppMenuClassName, "runMenuItemEnterAnimations");

        makePublicMethod(sAppMenuClassName, "createAppMenuContentView");
    }
}
