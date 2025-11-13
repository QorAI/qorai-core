/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiActivityClassAdapter extends QoraiClassVisitor {
    static String sChromeActivityClassName = "org/chromium/chrome/browser/app/ChromeActivity";
    static String sQoraiActivityClassName = "org/chromium/chrome/browser/app/QoraiActivity";

    public QoraiActivityClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiActivityClassName, "mBrowserControlsManagerSupplier");
        makeProtectedField(sChromeActivityClassName, "mBrowserControlsManagerSupplier");
    }
}
