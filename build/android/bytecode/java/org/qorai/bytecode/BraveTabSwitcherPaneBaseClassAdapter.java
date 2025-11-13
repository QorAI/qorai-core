/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTabSwitcherPaneBaseClassAdapter extends QoraiClassVisitor {
    static String sQoraiTabSwitcherPaneBaseClassName =
            "org/chromium/chrome/browser/tasks/tab_management/QoraiTabSwitcherPaneBase";

    static String sTabSwitcherPaneClassName =
            "org/chromium/chrome/browser/tasks/tab_management/TabSwitcherPane";

    static String sIncognitoTabSwitcherPaneClassName =
            "org/chromium/chrome/browser/tasks/tab_management/IncognitoTabSwitcherPane";

    public QoraiTabSwitcherPaneBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sTabSwitcherPaneClassName, sQoraiTabSwitcherPaneBaseClassName);
        changeSuperName(sIncognitoTabSwitcherPaneClassName, sQoraiTabSwitcherPaneBaseClassName);
    }
}
