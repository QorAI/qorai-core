/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiReturnToChromeUtilClassAdapter extends QoraiClassVisitor {
    static String sReturnToChromeUtilClassName =
            "org/chromium/chrome/browser/tasks/ReturnToChromeUtil";
    static String sQoraiReturnToChromeUtilClassName =
            "org/chromium/chrome/browser/tasks/QoraiReturnToChromeUtil";

    public QoraiReturnToChromeUtilClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sReturnToChromeUtilClassName,
                "shouldShowNtpAsHomeSurfaceAtStartup",
                sQoraiReturnToChromeUtilClassName);
    }
}
