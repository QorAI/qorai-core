/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiCustomizationProviderDelegateImplClassAdapter extends QoraiClassVisitor {
    static String sCustomizationProviderDelegateImplClassName =
            "org/chromium/chrome/browser/partnercustomizations/CustomizationProviderDelegateUpstreamImpl";
    static String sQoraiCustomizationProviderDelegateImplClassName =
            "org/chromium/chrome/browser/partnercustomizations/QoraiCustomizationProviderDelegateImpl";

    public QoraiCustomizationProviderDelegateImplClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sCustomizationProviderDelegateImplClassName,
                sQoraiCustomizationProviderDelegateImplClassName);
    }
}
