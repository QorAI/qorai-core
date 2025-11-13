/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiPasswordsPreferenceClassAdapter extends QoraiClassVisitor {
    static String sPasswordsPreferenceClassName =
            "org/chromium/chrome/browser/password_manager/settings/PasswordsPreference";

    static String sQoraiPasswordsPreferenceClassName =
            "org/chromium/chrome/browser/password_manager/settings/QoraiPasswordsPreference";

    public QoraiPasswordsPreferenceClassAdapter(ClassVisitor visitor) {
        super(visitor);

        makePublicMethod(sPasswordsPreferenceClassName, "setUpPostDeprecationWarning");
        addMethodAnnotation(
                sQoraiPasswordsPreferenceClassName,
                "setUpPostDeprecationWarning",
                "Ljava/lang/Override;");
    }
}
