/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiPartialCustomTabBottomSheetStrategyClassAdapter extends QoraiClassVisitor {
    static String sNamespace = "org/chromium/chrome/browser/customtabs/features/partialcustomtab/";
    static String sStrategy = sNamespace + "PartialCustomTabBottomSheetStrategy";
    static String sQoraiStrategy = sNamespace + "QoraiPartialCustomTabBottomSheetStrategy";

    QoraiPartialCustomTabBottomSheetStrategyClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sStrategy, sQoraiStrategy);

        deleteField(sQoraiStrategy, "mStopShowingSpinner");
        makeProtectedField(sStrategy, "mStopShowingSpinner");

        deleteField(sQoraiStrategy, "mTab");
        makeProtectedField(sStrategy, "mTab");
    }
}
