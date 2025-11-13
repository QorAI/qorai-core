/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAppHooksClassAdapter extends QoraiClassVisitor {
    static String sAppHooksClassName = "org/chromium/chrome/browser/AppHooks";
    static String sQoraiAppHooksClassName = "org/chromium/chrome/browser/QoraiAppHooks";

    public QoraiAppHooksClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sAppHooksClassName, sQoraiAppHooksClassName);
    }
}
