/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiPreferenceFragmentClassAdapter extends QoraiClassVisitor {
    static String sDeveloperSettingsClassName =
            "org/chromium/chrome/browser/tracing/settings/DeveloperSettings";

    static String sQoraiPreferenceFragmentClassName =
            "org/chromium/chrome/browser/settings/QoraiPreferenceFragment";

    public QoraiPreferenceFragmentClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sDeveloperSettingsClassName, sQoraiPreferenceFragmentClassName);
    }
}
