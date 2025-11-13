/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTabCardThemeUtilClassAdapter extends QoraiClassVisitor {
    static String sTabCardThemeUtilClassName =
            "org/chromium/chrome/browser/tab_ui/TabCardThemeUtil";
    static String sQoraiTabCardThemeUtilClassName =
            "org/chromium/chrome/browser/tab_ui/QoraiTabCardThemeUtil";

    public QoraiTabCardThemeUtilClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeMethodOwner(
                sTabCardThemeUtilClassName, "getTitleTextColor", sQoraiTabCardThemeUtilClassName);

        changeMethodOwner(
                sTabCardThemeUtilClassName,
                "getCardViewBackgroundColor",
                sQoraiTabCardThemeUtilClassName);

        changeMethodOwner(
                sTabCardThemeUtilClassName,
                "getActionButtonTintList",
                sQoraiTabCardThemeUtilClassName);
    }
}
