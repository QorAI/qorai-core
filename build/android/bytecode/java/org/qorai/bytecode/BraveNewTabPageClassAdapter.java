/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiNewTabPageClassAdapter extends QoraiClassVisitor {
    static String sNewTabPageClassName = "org/chromium/chrome/browser/ntp/NewTabPage";
    static String sQoraiNewTabPageClassName = "org/chromium/chrome/browser/ntp/QoraiNewTabPage";

    public QoraiNewTabPageClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sNewTabPageClassName, sQoraiNewTabPageClassName);

        deleteField(sQoraiNewTabPageClassName, "mBrowserControlsStateProvider");
        makeProtectedField(sNewTabPageClassName, "mBrowserControlsStateProvider");

        deleteField(sQoraiNewTabPageClassName, "mNewTabPageLayout");
        makeProtectedField(sNewTabPageClassName, "mNewTabPageLayout");

        deleteField(sQoraiNewTabPageClassName, "mFeedSurfaceProvider");
        makeProtectedField(sNewTabPageClassName, "mFeedSurfaceProvider");

        deleteField(sQoraiNewTabPageClassName, "mToolbarSupplier");
        makeProtectedField(sNewTabPageClassName, "mToolbarSupplier");

        deleteField(sQoraiNewTabPageClassName, "mBottomSheetController");
        makeProtectedField(sNewTabPageClassName, "mBottomSheetController");

        deleteField(sQoraiNewTabPageClassName, "mTabStripHeightSupplier");
        makeProtectedField(sNewTabPageClassName, "mTabStripHeightSupplier");

        makePublicMethod(sNewTabPageClassName, "updateSearchProvider");
        addMethodAnnotation(
                sQoraiNewTabPageClassName, "updateSearchProvider", "Ljava/lang/Override;");
    }
}
