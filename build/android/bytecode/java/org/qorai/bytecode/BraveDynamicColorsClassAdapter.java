/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiDynamicColorsClassAdapter extends QoraiClassVisitor {
    static String sDynamicColorsClassName = "com/google/android/material/color/DynamicColors";

    static String sQoraiDynamicColorsClassName =
            "org/chromium/chrome/browser/util/QoraiDynamicColors";

    public QoraiDynamicColorsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(sDynamicColorsClassName, "applyToActivityIfAvailable",
                sQoraiDynamicColorsClassName);
    }
}
