/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMostVisitedTilesMediatorClassAdapter extends QoraiClassVisitor {
    static String sMostVisitedTilesMediatorClassName =
            "org/chromium/chrome/browser/suggestions/tile/MostVisitedTilesMediator";
    static String sQoraiMostVisitedTilesMediatorClassName =
            "org/chromium/chrome/browser/suggestions/tile/QoraiMostVisitedTilesMediator";

    public QoraiMostVisitedTilesMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sMostVisitedTilesMediatorClassName, sQoraiMostVisitedTilesMediatorClassName);

        deleteField(sQoraiMostVisitedTilesMediatorClassName, "mTileGroup");
        makeProtectedField(sMostVisitedTilesMediatorClassName, "mTileGroup");
    }
}
