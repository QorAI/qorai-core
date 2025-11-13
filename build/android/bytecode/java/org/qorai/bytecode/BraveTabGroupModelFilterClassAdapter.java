/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTabGroupModelFilterClassAdapter extends QoraiClassVisitor {
    static String sTabGroupModelFilterClassName =
            "org/chromium/chrome/browser/tabmodel/TabGroupModelFilterImpl";
    static String sQoraiTabGroupModelFilterClassName =
            "org/chromium/chrome/browser/tabmodel/QoraiTabGroupModelFilter";

    public QoraiTabGroupModelFilterClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sTabGroupModelFilterClassName, sQoraiTabGroupModelFilterClassName);

        deleteField(sTabGroupModelFilterClassName, "mIsResetting");

        changeMethodOwner(
                sTabGroupModelFilterClassName,
                "shouldGroupWithParent",
                sQoraiTabGroupModelFilterClassName);
    }
}
