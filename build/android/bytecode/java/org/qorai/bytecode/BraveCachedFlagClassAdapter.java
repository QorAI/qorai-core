/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiCachedFlagClassAdapter extends QoraiClassVisitor {
    static String sCachedFlagClassName = "org/chromium/components/cached_flags/CachedFlag";
    static String sQoraiCachedFlagClassName =
            "org/chromium/components/cached_flags/QoraiCachedFlag";

    public QoraiCachedFlagClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sCachedFlagClassName, sQoraiCachedFlagClassName);

        deleteField(sQoraiCachedFlagClassName, "mDefaultValue");
        makeProtectedField(sCachedFlagClassName, "mDefaultValue");
    }
}
