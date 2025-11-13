/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSettingsIntentUtilClassAdapter extends QoraiClassVisitor {
    static String sSettingsIntentUtilClassName =
            "org/chromium/chrome/browser/settings/SettingsIntentUtil";

    static String sQoraiSettingsIntentUtilClassName =
            "org/chromium/chrome/browser/settings/QoraiSettingsIntentUtil";

    public QoraiSettingsIntentUtilClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(
                sSettingsIntentUtilClassName, "createIntent", sQoraiSettingsIntentUtilClassName);
    }
}
