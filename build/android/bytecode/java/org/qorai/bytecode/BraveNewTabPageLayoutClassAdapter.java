/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiNewTabPageLayoutClassAdapter extends QoraiClassVisitor {
    static String sNewTabPageLayoutClassName = "org/chromium/chrome/browser/ntp/NewTabPageLayout";
    static String sQoraiNewTabPageLayoutClassName =
            "org/chromium/chrome/browser/ntp/QoraiNewTabPageLayout";
    static String sNewTabPageLayoutSuperClassName = "android/widget/FrameLayout";

    public QoraiNewTabPageLayoutClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiNewTabPageLayoutClassName, "mMvTilesContainerLayout");
        makeProtectedField(sNewTabPageLayoutClassName, "mMvTilesContainerLayout");

        deleteField(sQoraiNewTabPageLayoutClassName, "mMvtContentFits");
        makeProtectedField(sNewTabPageLayoutClassName, "mMvtContentFits");

        deleteField(sQoraiNewTabPageLayoutClassName, "mProfile");
        makeProtectedField(sNewTabPageLayoutClassName, "mProfile");

        makePublicMethod(sNewTabPageLayoutClassName, "initializeSiteSectionView");
        addMethodAnnotation(
                sQoraiNewTabPageLayoutClassName,
                "initializeSiteSectionView",
                "Ljava/lang/Override;");

        makePublicMethod(sNewTabPageLayoutClassName, "setSearchProviderTopMargin");
        addMethodAnnotation(
                sQoraiNewTabPageLayoutClassName,
                "setSearchProviderTopMargin",
                "Ljava/lang/Override;");

        makePublicMethod(sNewTabPageLayoutClassName, "setSearchProviderBottomMargin");
        addMethodAnnotation(
                sQoraiNewTabPageLayoutClassName,
                "setSearchProviderBottomMargin",
                "Ljava/lang/Override;");

        makePublicMethod(sNewTabPageLayoutClassName, "calculateTabletMvtWidth");
        addMethodAnnotation(
                sQoraiNewTabPageLayoutClassName, "calculateTabletMvtWidth", "Ljava/lang/Override;");

        deleteMethod(sQoraiNewTabPageLayoutClassName, "getLogoMargin");
        makePublicMethod(sNewTabPageLayoutClassName, "getLogoMargin");

        deleteMethod(sQoraiNewTabPageLayoutClassName, "updateMvtOnTablet");
        makePublicMethod(sNewTabPageLayoutClassName, "updateMvtOnTablet");

        changeSuperName(sNewTabPageLayoutClassName, sNewTabPageLayoutSuperClassName);
    }
}
