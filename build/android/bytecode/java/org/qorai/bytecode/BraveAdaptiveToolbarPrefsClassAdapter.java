/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAdaptiveToolbarPrefsClassAdapter extends QoraiClassVisitor {
    static String sAdaptiveToolbarPrefsClassName =
            "org/chromium/chrome/browser/toolbar/adaptive/AdaptiveToolbarPrefs";
    static String sQoraiAdaptiveToolbarPrefsClassName =
            "org/chromium/chrome/browser/toolbar/adaptive/QoraiAdaptiveToolbarPrefs";

    public QoraiAdaptiveToolbarPrefsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sAdaptiveToolbarPrefsClassName,
                "getCustomizationSetting",
                sQoraiAdaptiveToolbarPrefsClassName);

        changeMethodOwner(
                sAdaptiveToolbarPrefsClassName,
                "isCustomizationPreferenceEnabled",
                sQoraiAdaptiveToolbarPrefsClassName);
    }
}
