/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiLocationBarMediatorClassAdapter extends QoraiClassVisitor {
    static String sLocationBarMediator = "org/chromium/chrome/browser/omnibox/LocationBarMediator";
    static String sQoraiLocationBarMediator =
            "org/chromium/chrome/browser/omnibox/QoraiLocationBarMediator";

    public QoraiLocationBarMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sLocationBarMediator, sQoraiLocationBarMediator);

        deleteMethod(sQoraiLocationBarMediator, "shouldShowDeleteButton");
        makePublicMethod(sLocationBarMediator, "shouldShowDeleteButton");

        deleteField(sQoraiLocationBarMediator, "mNativeInitialized");
        makeProtectedField(sLocationBarMediator, "mNativeInitialized");
        deleteField(sQoraiLocationBarMediator, "mWindowAndroid");
        makeProtectedField(sLocationBarMediator, "mWindowAndroid");
        deleteField(sQoraiLocationBarMediator, "mLocationBarLayout");
        makeProtectedField(sLocationBarMediator, "mLocationBarLayout");
        deleteField(sQoraiLocationBarMediator, "mIsUrlFocusChangeInProgress");
        makeProtectedField(sLocationBarMediator, "mIsUrlFocusChangeInProgress");
        deleteField(sQoraiLocationBarMediator, "mUrlHasFocus");
        makeProtectedField(sLocationBarMediator, "mUrlHasFocus");
        deleteField(sQoraiLocationBarMediator, "mIsTablet");
        makeProtectedField(sLocationBarMediator, "mIsTablet");
        deleteField(sQoraiLocationBarMediator, "mIsLocationBarFocusedFromNtpScroll");
        makeProtectedField(sLocationBarMediator, "mIsLocationBarFocusedFromNtpScroll");
        deleteField(sQoraiLocationBarMediator, "mContext");
        makeProtectedField(sLocationBarMediator, "mContext");
        deleteField(sQoraiLocationBarMediator, "mBrandedColorScheme");
        makeProtectedField(sLocationBarMediator, "mBrandedColorScheme");
        deleteField(sQoraiLocationBarMediator, "mTemplateUrlServiceSupplier");
        makeProtectedField(sLocationBarMediator, "mTemplateUrlServiceSupplier");
    }
}
