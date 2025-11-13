/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiPermissionDialogDelegateClassAdapter extends QoraiClassVisitor {
    static String sPermissionDialogDelegateClassName =
            "org/chromium/components/permissions/PermissionDialogDelegate";

    static String sQoraiPermissionDialogDelegateClassName =
            "org/chromium/components/permissions/QoraiPermissionDialogDelegate";

    public QoraiPermissionDialogDelegateClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeSuperName(
                sPermissionDialogDelegateClassName, sQoraiPermissionDialogDelegateClassName);
    }
}
