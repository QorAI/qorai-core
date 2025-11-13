/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiRadioButtonGroupAdaptiveToolbarPreferenceClassAdapter extends QoraiClassVisitor {
    static String sRadioButtonGroupAdaptiveToolbarPreference =
            "org/chromium/chrome/browser/toolbar/adaptive/settings/RadioButtonGroupAdaptiveToolbarPreference"; // presubmit: ignore-long-line
    static String sQoraiRadioButtonGroupAdaptiveToolbarPreference =
            "org/chromium/chrome/browser/toolbar/adaptive/settings/QoraiRadioButtonGroupAdaptiveToolbarPreference"; // presubmit: ignore-long-line

    public QoraiRadioButtonGroupAdaptiveToolbarPreferenceClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiRadioButtonGroupAdaptiveToolbarPreference, "mSelected");
        makeProtectedField(sRadioButtonGroupAdaptiveToolbarPreference, "mSelected");

        deleteField(sQoraiRadioButtonGroupAdaptiveToolbarPreference, "mIsBound");
        makeProtectedField(sRadioButtonGroupAdaptiveToolbarPreference, "mIsBound");

        deleteField(sQoraiRadioButtonGroupAdaptiveToolbarPreference, "mAutoButton");
        makeProtectedField(sRadioButtonGroupAdaptiveToolbarPreference, "mAutoButton");

        deleteField(sQoraiRadioButtonGroupAdaptiveToolbarPreference, "mNewTabButton");
        makeProtectedField(sRadioButtonGroupAdaptiveToolbarPreference, "mNewTabButton");

        deleteField(sQoraiRadioButtonGroupAdaptiveToolbarPreference, "mShareButton");
        makeProtectedField(sRadioButtonGroupAdaptiveToolbarPreference, "mShareButton");

        makePublicMethod(sRadioButtonGroupAdaptiveToolbarPreference, "buildUiStateForStats");
        addMethodAnnotation(
                sQoraiRadioButtonGroupAdaptiveToolbarPreference,
                "buildUiStateForStats",
                "Ljava/lang/Override;");
    }
}
