/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiPasswordManagerHelperClassAdapter extends QoraiClassVisitor {
    static String sChromePasswordManagerHelperClassName =
            "org/chromium/chrome/browser/password_manager/PasswordManagerHelper";
    static String sQoraiPasswordManagerHelperClassName =
            "org/chromium/chrome/browser/password_manager/QoraiPasswordManagerHelper";

    QoraiPasswordManagerHelperClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiPasswordManagerHelperClassName, "sProfileMap");
        makeProtectedField(sChromePasswordManagerHelperClassName, "sProfileMap");

        changeMethodOwner(
                sChromePasswordManagerHelperClassName,
                "getForProfile",
                sQoraiPasswordManagerHelperClassName);
    }
}
