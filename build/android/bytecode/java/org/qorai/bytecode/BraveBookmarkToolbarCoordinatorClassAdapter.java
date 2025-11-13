/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkToolbarCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sBookmarkToolbarCoordinatorClassName =
            "org/chromium/chrome/browser/bookmarks/BookmarkToolbarCoordinator";
    static String sQoraiBookmarkToolbarCoordinatorClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkToolbarCoordinator";

    public QoraiBookmarkToolbarCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sBookmarkToolbarCoordinatorClassName, sQoraiBookmarkToolbarCoordinatorClassName);

        deleteField(sQoraiBookmarkToolbarCoordinatorClassName, "mToolbar");
        makeProtectedField(sBookmarkToolbarCoordinatorClassName, "mToolbar");
    }
}
