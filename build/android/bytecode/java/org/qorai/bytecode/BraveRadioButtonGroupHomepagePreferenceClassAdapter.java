/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiRadioButtonGroupHomepagePreferenceClassAdapter extends QoraiClassVisitor {
    static String sRadioButtonGroupHomepagePreferenceClassName =
            "org/chromium/chrome/browser/homepage/settings/RadioButtonGroupHomepagePreference";
    static String sQoraiRadioButtonGroupHomepagePreferenceClassName =
            "org/chromium/chrome/browser/homepage/settings/QoraiRadioButtonGroupHomepagePreference";

    public QoraiRadioButtonGroupHomepagePreferenceClassAdapter(ClassVisitor visitor) {
        super(visitor);

        makeNonFinalClass(sRadioButtonGroupHomepagePreferenceClassName);

        changeSuperName(
                sQoraiRadioButtonGroupHomepagePreferenceClassName,
                sRadioButtonGroupHomepagePreferenceClassName);
    }
}
