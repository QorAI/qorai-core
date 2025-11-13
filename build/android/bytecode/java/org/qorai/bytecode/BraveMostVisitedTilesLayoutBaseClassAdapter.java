/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMostVisitedTilesLayoutBaseClassAdapter extends QoraiClassVisitor {
    static String sMostVisitedTilesLayoutClassName =
            "org/chromium/chrome/browser/suggestions/tile/MostVisitedTilesLayout";
    static String sQoraiMostVisitedTilesLayoutBaseClassName =
            "org/chromium/chrome/browser/suggestions/tile/QoraiMostVisitedTilesLayoutBase";

    public QoraiMostVisitedTilesLayoutBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(
                sMostVisitedTilesLayoutClassName, sQoraiMostVisitedTilesLayoutBaseClassName);

        changeSuperName(
                "org/chromium/chrome/browser/suggestions/tile/TilesLinearLayout",
                "android/widget/GridLayout");

        deleteMethod(sQoraiMostVisitedTilesLayoutBaseClassName, "getColumnCount");
        deleteMethod(sQoraiMostVisitedTilesLayoutBaseClassName, "setColumnCount");
        deleteMethod(sQoraiMostVisitedTilesLayoutBaseClassName, "getRowCount");
        deleteMethod(sQoraiMostVisitedTilesLayoutBaseClassName, "setRowCount");
    }
}
