/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAdaptiveToolbarStatePredictorClassAdapter extends QoraiClassVisitor {
    static String sAdaptiveToolbarStatePredictor =
            "org/chromium/chrome/browser/toolbar/adaptive/AdaptiveToolbarStatePredictor";
    static String sQoraiAdaptiveToolbarStatePredictor =
            "org/chromium/chrome/browser/toolbar/adaptive/QoraiAdaptiveToolbarStatePredictor";

    public QoraiAdaptiveToolbarStatePredictorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sQoraiAdaptiveToolbarStatePredictor, sAdaptiveToolbarStatePredictor);

        makePublicMethod(sAdaptiveToolbarStatePredictor, "isValidSegment");

        redirectConstructor(sAdaptiveToolbarStatePredictor, sQoraiAdaptiveToolbarStatePredictor);
    }
}
