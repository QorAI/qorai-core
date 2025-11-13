/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiLocationBarCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sLocationBarCoordinator =
            "org/chromium/chrome/browser/omnibox/LocationBarCoordinator";
    static String sQoraiLocationBarCoordinator =
            "org/chromium/chrome/browser/omnibox/QoraiLocationBarCoordinator";

    public QoraiLocationBarCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sLocationBarCoordinator, sQoraiLocationBarCoordinator);

        deleteField(sQoraiLocationBarCoordinator, "mLocationBarMediator");
        makeProtectedField(sLocationBarCoordinator, "mLocationBarMediator");

        deleteField(sQoraiLocationBarCoordinator, "mUrlBar");
        makeProtectedField(sLocationBarCoordinator, "mUrlBar");
    }
}
