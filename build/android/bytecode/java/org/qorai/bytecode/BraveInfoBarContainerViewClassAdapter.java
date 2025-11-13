/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiInfoBarContainerViewClassAdapter extends QoraiClassVisitor {
    static String sInfoBarContainerViewClassName =
            "org/chromium/chrome/browser/infobar/InfoBarContainerView";

    static String sQoraiInfoBarContainerViewClassName =
            "org/chromium/chrome/browser/infobar/QoraiInfoBarContainerView";

    public QoraiInfoBarContainerViewClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiInfoBarContainerViewClassName, "mEdgeToEdgeSupplier");
        makeProtectedField(sInfoBarContainerViewClassName, "mEdgeToEdgeSupplier");
        redirectConstructor(sInfoBarContainerViewClassName, sQoraiInfoBarContainerViewClassName);
    }
}
