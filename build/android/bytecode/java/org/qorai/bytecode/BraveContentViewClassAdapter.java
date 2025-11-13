/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiContentViewClassAdapter extends QoraiClassVisitor {
    static String sContentViewClassName =
            "org/chromium/components/embedder_support/view/ContentView";
    static String sQoraiContentViewClassName =
            "org/chromium/components/embedder_support/view/QoraiContentView";

    public QoraiContentViewClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sContentViewClassName, sQoraiContentViewClassName);
    }
}
