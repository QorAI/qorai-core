/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiForegroundServiceUtilsClassAdapter extends QoraiClassVisitor {
    static String sForegroundServiceUtilsClassName =
            "org/chromium/components/browser_ui/notifications/ForegroundServiceUtils";

    static String sQoraiForegroundServiceUtilsClassName =
            "org/chromium/components/browser_ui/notifications/QoraiForegroundServiceUtils";

    public QoraiForegroundServiceUtilsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sForegroundServiceUtilsClassName, sQoraiForegroundServiceUtilsClassName);
    }
}
