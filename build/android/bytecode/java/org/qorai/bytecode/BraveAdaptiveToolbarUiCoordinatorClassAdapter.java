/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiAdaptiveToolbarUiCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sAdaptiveToolbarUiCoordinator =
            "org/chromium/chrome/browser/ui/AdaptiveToolbarUiCoordinator";
    static String sQoraiAdaptiveToolbarUiCoordinator =
            "org/chromium/chrome/browser/ui/QoraiAdaptiveToolbarUiCoordinator";

    public QoraiAdaptiveToolbarUiCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sAdaptiveToolbarUiCoordinator, sQoraiAdaptiveToolbarUiCoordinator);

        deleteField(sQoraiAdaptiveToolbarUiCoordinator, "mContext");
        makeProtectedField(sAdaptiveToolbarUiCoordinator, "mContext");

        deleteField(sQoraiAdaptiveToolbarUiCoordinator, "mActivityTabProvider");
        makeProtectedField(sAdaptiveToolbarUiCoordinator, "mActivityTabProvider");

        deleteField(sQoraiAdaptiveToolbarUiCoordinator, "mModalDialogManagerSupplier");
        makeProtectedField(sAdaptiveToolbarUiCoordinator, "mModalDialogManagerSupplier");

        deleteField(sQoraiAdaptiveToolbarUiCoordinator, "mProfileSupplier");
        makeProtectedField(sAdaptiveToolbarUiCoordinator, "mProfileSupplier");

        deleteField(sQoraiAdaptiveToolbarUiCoordinator, "mAdaptiveToolbarButtonController");
        makeProtectedField(sAdaptiveToolbarUiCoordinator, "mAdaptiveToolbarButtonController");
    }
}
