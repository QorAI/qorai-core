/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiStrictPreferenceKeyCheckerClassAdapter extends QoraiClassVisitor {
    static String sStrictPreferenceKeyCheckerClassName =
            "org/chromium/base/shared_preferences/StrictPreferenceKeyChecker";

    static String sQoraiStrictPreferenceKeyCheckerClassName =
            "org/chromium/base/shared_preferences/QoraiStrictPreferenceKeyChecker";

    public QoraiStrictPreferenceKeyCheckerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sStrictPreferenceKeyCheckerClassName, sQoraiStrictPreferenceKeyCheckerClassName);

        deleteMethod(sQoraiStrictPreferenceKeyCheckerClassName, "isKeyInUse");
        makePublicMethod(sStrictPreferenceKeyCheckerClassName, "isKeyInUse");
    }
}
