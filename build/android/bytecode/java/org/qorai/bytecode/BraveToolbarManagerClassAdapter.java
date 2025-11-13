/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiToolbarManagerClassAdapter extends QoraiClassVisitor {
    static String sToolbarManagerClassName = "org/chromium/chrome/browser/toolbar/ToolbarManager";
    static String sQoraiToolbarManagerClassName =
            "org/chromium/chrome/browser/toolbar/QoraiToolbarManager";

    public QoraiToolbarManagerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sToolbarManagerClassName, sQoraiToolbarManagerClassName);

        deleteField(sQoraiToolbarManagerClassName, "mBottomControlsCoordinatorSupplier");
        makeProtectedField(sToolbarManagerClassName, "mBottomControlsCoordinatorSupplier");

        deleteField(sQoraiToolbarManagerClassName, "mCallbackController");
        makeProtectedField(sToolbarManagerClassName, "mCallbackController");

        deleteField(sQoraiToolbarManagerClassName, "mBottomControlsStacker");
        makeProtectedField(sToolbarManagerClassName, "mBottomControlsStacker");

        deleteField(sQoraiToolbarManagerClassName, "mFullscreenManager");
        makeProtectedField(sToolbarManagerClassName, "mFullscreenManager");

        deleteField(sQoraiToolbarManagerClassName, "mActivityTabProvider");
        makeProtectedField(sToolbarManagerClassName, "mActivityTabProvider");

        deleteField(sQoraiToolbarManagerClassName, "mAppThemeColorProvider");
        makeProtectedField(sToolbarManagerClassName, "mAppThemeColorProvider");

        deleteField(sQoraiToolbarManagerClassName, "mScrimManager");
        makeProtectedField(sToolbarManagerClassName, "mScrimManager");

        deleteField(sQoraiToolbarManagerClassName, "mMenuButtonCoordinator");
        makeProtectedField(sToolbarManagerClassName, "mMenuButtonCoordinator");

        deleteField(sQoraiToolbarManagerClassName, "mToolbarTabController");
        makeProtectedField(sToolbarManagerClassName, "mToolbarTabController");

        deleteField(sQoraiToolbarManagerClassName, "mLocationBar");
        makeProtectedField(sToolbarManagerClassName, "mLocationBar");

        deleteField(sQoraiToolbarManagerClassName, "mActionModeController");
        makeProtectedField(sToolbarManagerClassName, "mActionModeController");

        deleteField(sQoraiToolbarManagerClassName, "mLocationBarModel");
        makeProtectedField(sToolbarManagerClassName, "mLocationBarModel");

        deleteField(sQoraiToolbarManagerClassName, "mToolbar");
        makeProtectedField(sToolbarManagerClassName, "mToolbar");

        deleteField(sQoraiToolbarManagerClassName, "mBookmarkModelSupplier");
        makeProtectedField(sToolbarManagerClassName, "mBookmarkModelSupplier");

        deleteField(sQoraiToolbarManagerClassName, "mLayoutManager");
        makeProtectedField(sToolbarManagerClassName, "mLayoutManager");

        deleteField(sQoraiToolbarManagerClassName, "mOverlayPanelVisibilitySupplier");
        makeProtectedField(sToolbarManagerClassName, "mOverlayPanelVisibilitySupplier");

        deleteField(sQoraiToolbarManagerClassName, "mTabModelSelector");
        makeProtectedField(sToolbarManagerClassName, "mTabModelSelector");

        deleteField(sQoraiToolbarManagerClassName, "mIncognitoStateProvider");
        makeProtectedField(sToolbarManagerClassName, "mIncognitoStateProvider");

        deleteField(sQoraiToolbarManagerClassName, "mBottomSheetController");
        makeProtectedField(sToolbarManagerClassName, "mBottomSheetController");

        deleteField(sQoraiToolbarManagerClassName, "mTabContentManager");
        makeProtectedField(sToolbarManagerClassName, "mTabContentManager");

        deleteField(sQoraiToolbarManagerClassName, "mTabCreatorManager");
        makeProtectedField(sToolbarManagerClassName, "mTabCreatorManager");

        deleteField(sQoraiToolbarManagerClassName, "mModalDialogManagerSupplier");
        makeProtectedField(sToolbarManagerClassName, "mModalDialogManagerSupplier");

        deleteField(sQoraiToolbarManagerClassName, "mTabObscuringHandler");
        makeProtectedField(sToolbarManagerClassName, "mTabObscuringHandler");

        deleteField(sQoraiToolbarManagerClassName, "mReadAloudControllerSupplier");
        makeProtectedField(sToolbarManagerClassName, "mReadAloudControllerSupplier");

        deleteField(sQoraiToolbarManagerClassName, "mTopUiThemeColorProvider");
        makeProtectedField(sToolbarManagerClassName, "mTopUiThemeColorProvider");

        deleteField(sQoraiToolbarManagerClassName, "mCurrentOrientation");
        makeProtectedField(sToolbarManagerClassName, "mCurrentOrientation");

        deleteField(sQoraiToolbarManagerClassName, "mInitializedWithNative");
        makeProtectedField(sToolbarManagerClassName, "mInitializedWithNative");

        deleteField(sQoraiToolbarManagerClassName, "mTabGroupUiOneshotSupplier");
        makeProtectedField(sToolbarManagerClassName, "mTabGroupUiOneshotSupplier");

        deleteField(sQoraiToolbarManagerClassName, "mUndoBarThrottle");
        makeProtectedField(sToolbarManagerClassName, "mUndoBarThrottle");

        makePublicMethod(sToolbarManagerClassName, "onOrientationChange");
        addMethodAnnotation(
                sQoraiToolbarManagerClassName, "onOrientationChange", "Ljava/lang/Override;");

        makePublicMethod(sToolbarManagerClassName, "updateBookmarkButtonStatus");
        addMethodAnnotation(sQoraiToolbarManagerClassName, "updateBookmarkButtonStatus",
                "Ljava/lang/Override;");

        makePublicMethod(sToolbarManagerClassName, "updateReloadState");
        deleteMethod(sQoraiToolbarManagerClassName, "updateReloadState");
    }
}
