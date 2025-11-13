/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiHttpURLConnectionFactoryImplClassAdapter extends QoraiClassVisitor {
    static String sConnectionFactoryClassName =
            "org/chromium/components/minidump_uploader/util/HttpURLConnectionFactoryImpl";
    static String sQoraiConnectionFactoryClassName =
            "org/chromium/components/minidump_uploader/util/QoraiHttpURLConnectionFactoryImpl";

    public QoraiHttpURLConnectionFactoryImplClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sConnectionFactoryClassName, sQoraiConnectionFactoryClassName);
    }
}
