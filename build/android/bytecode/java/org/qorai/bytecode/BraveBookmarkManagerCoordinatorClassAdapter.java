/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkManagerCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sBookmarkManagerCoordinatorClassName =
            "org/chromium/chrome/browser/bookmarks/BookmarkManagerCoordinator";
    static String sQoraiBookmarkManagerCoordinatorClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkManagerCoordinator";

    public QoraiBookmarkManagerCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sBookmarkManagerCoordinatorClassName, sQoraiBookmarkManagerCoordinatorClassName);
        deleteField(sQoraiBookmarkManagerCoordinatorClassName, "mMediator");
        makeProtectedField(sBookmarkManagerCoordinatorClassName, "mMediator");
    }
}
