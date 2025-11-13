/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiLogoMediatorClassAdapter extends QoraiClassVisitor {
    static String sLogoMediator = "org/chromium/chrome/browser/logo/LogoMediator";
    static String sQoraiLogoMediator = "org/chromium/chrome/browser/logo/QoraiLogoMediator";

    public QoraiLogoMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sLogoMediator, sQoraiLogoMediator);

        deleteField(sQoraiLogoMediator, "mLogoModel");
        makeProtectedField(sLogoMediator, "mLogoModel");

        deleteField(sQoraiLogoMediator, "mShouldShowLogo");
        makeProtectedField(sLogoMediator, "mShouldShowLogo");

        makePublicMethod(sLogoMediator, "updateVisibility");
        addMethodAnnotation(sQoraiLogoMediator, "updateVisibility", "Ljava/lang/Override;");
    }
}
