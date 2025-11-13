/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMultiInstanceManagerApi31ClassAdapter extends QoraiClassVisitor {
    static String sMultiInstanceManagerApi31 =
            "org/chromium/chrome/browser/multiwindow/MultiInstanceManagerApi31";
    static String sQoraiMultiInstanceManagerApi31 =
            "org/chromium/chrome/browser/multiwindow/QoraiMultiInstanceManagerApi31";

    public QoraiMultiInstanceManagerApi31ClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sMultiInstanceManagerApi31, sQoraiMultiInstanceManagerApi31);

        deleteField(sQoraiMultiInstanceManagerApi31, "mInstanceId");
        makeProtectedField(sMultiInstanceManagerApi31, "mInstanceId");
    }
}
