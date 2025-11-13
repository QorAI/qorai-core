/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiCachedFlagsClassAdapter extends QoraiClassVisitor {
    static String sChromeCachedFlagsClassName =
            "org/chromium/chrome/browser/app/flags/ChromeCachedFlags";
    static String sQoraiCachedFlagsClassName =
            "org/chromium/chrome/browser/app/flags/QoraiCachedFlags";

    public QoraiCachedFlagsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sChromeCachedFlagsClassName, sQoraiCachedFlagsClassName);
    }
}
