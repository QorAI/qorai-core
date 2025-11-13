/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiThemeUtilsClassAdapter extends QoraiClassVisitor {
    static String sThemeUtilsClassName = "org/chromium/chrome/browser/theme/ThemeUtils";
    static String sQoraiThemeUtilsClassName = "org/chromium/chrome/browser/theme/QoraiThemeUtils";

    public QoraiThemeUtilsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(sThemeUtilsClassName,
                "getTextBoxColorForToolbarBackgroundInNonNativePage", sQoraiThemeUtilsClassName);
    }
}
