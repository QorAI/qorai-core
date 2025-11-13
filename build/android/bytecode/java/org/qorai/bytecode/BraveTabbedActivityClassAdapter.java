/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiTabbedActivityClassAdapter extends QoraiClassVisitor {
    static String sChromeTabbedActivityClassName =
            "org/chromium/chrome/browser/ChromeTabbedActivity";
    static String sQoraiActivityClassName = "org/chromium/chrome/browser/app/QoraiActivity";
    static String sTabbedRootUiCoordinatorClassName =
            "org/chromium/chrome/browser/tabbed_mode/TabbedRootUiCoordinator";
    static String sTabbedAppMenuPropertiesDelegateClassName =
            "org/chromium/chrome/browser/tabbed_mode/TabbedAppMenuPropertiesDelegate";
    static String sQoraiTabbedAppMenuPropertiesDelegateClassName =
            "org/chromium/chrome/browser/tabbed_mode/QoraiTabbedAppMenuPropertiesDelegate";

    static String sChromeTabCreatorClassName =
            "org/chromium/chrome/browser/tabmodel/ChromeTabCreator";
    static String sRedirectTabCreatorClassName =
            "org/chromium/chrome/browser/tabmodel/RedirectTabCreator";
    static String sQoraiTabCreatorClassName =
            "org/chromium/chrome/browser/tabmodel/QoraiTabCreator";

    public QoraiTabbedActivityClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sChromeTabbedActivityClassName, sQoraiActivityClassName);

        redirectConstructor(
                sTabbedAppMenuPropertiesDelegateClassName,
                sQoraiTabbedAppMenuPropertiesDelegateClassName);

        changeSuperName(sRedirectTabCreatorClassName, sQoraiTabCreatorClassName);

        redirectConstructor(sChromeTabCreatorClassName, sQoraiTabCreatorClassName);

        makePublicMethod(sChromeTabbedActivityClassName, "hideOverview");

        deleteMethod(sChromeTabbedActivityClassName, "supportsDynamicColors");

        makePublicMethod(sChromeTabbedActivityClassName, "maybeHandleUrlIntent");
        changeMethodOwner(
                sChromeTabbedActivityClassName, "maybeHandleUrlIntent", sQoraiActivityClassName);
        makeProtectedField(sChromeTabbedActivityClassName, "mLayoutManager");
        makeProtectedField(sChromeTabbedActivityClassName, "mMultiInstanceManager");
    }
}
