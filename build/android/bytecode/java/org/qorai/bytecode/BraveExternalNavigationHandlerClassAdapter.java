/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiExternalNavigationHandlerClassAdapter extends QoraiClassVisitor {
    static String sExternalNavigationHandlerClassName =
            "org/chromium/components/external_intents/ExternalNavigationHandler";
    static String sQoraiQoraiExternalNavigationHandlerClassName =
            "org/chromium/chrome/browser/externalnav/QoraiExternalNavigationHandler";

    public QoraiExternalNavigationHandlerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sExternalNavigationHandlerClassName, sQoraiQoraiExternalNavigationHandlerClassName);
    }
}
