/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiIncognitoTabSwitcherPaneClassAdapter extends QoraiClassVisitor {
    static String sIncognitoTabSwitcherPaneClassName =
            "org/chromium/chrome/browser/tasks/tab_management/IncognitoTabSwitcherPane";

    static String sQoraiIncognitoTabSwitcherPaneClassName =
            "org/chromium/chrome/browser/tasks/tab_management/QoraiIncognitoTabSwitcherPane";

    public QoraiIncognitoTabSwitcherPaneClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sIncognitoTabSwitcherPaneClassName, sQoraiIncognitoTabSwitcherPaneClassName);
    }
}
