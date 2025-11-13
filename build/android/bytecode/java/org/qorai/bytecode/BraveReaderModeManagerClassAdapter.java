/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiReaderModeManagerClassAdapter extends QoraiClassVisitor {
    static String sReaderModeManagerClassName =
            "org/chromium/chrome/browser/dom_distiller/ReaderModeManager";
    static String sQoraiReaderModeManagerClassName =
            "org/chromium/chrome/browser/dom_distiller/QoraiReaderModeManager";

    public QoraiReaderModeManagerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sReaderModeManagerClassName, sQoraiReaderModeManagerClassName);

        deleteField(sQoraiReaderModeManagerClassName, "mTab");
        makeProtectedField(sReaderModeManagerClassName, "mTab");
    }
}
