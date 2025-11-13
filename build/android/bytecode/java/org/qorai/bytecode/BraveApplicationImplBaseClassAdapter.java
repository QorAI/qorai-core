/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiApplicationImplBaseClassAdapter extends QoraiClassVisitor {
    static String sChromeApplicationImplClassName =
            "org/chromium/chrome/browser/ChromeApplicationImpl";

    static String sQoraiApplicationImplBaseClassName =
            "org/chromium/chrome/browser/QoraiApplicationImplBase";

    public QoraiApplicationImplBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeSuperName(sChromeApplicationImplClassName, sQoraiApplicationImplBaseClassName);
    }
}
