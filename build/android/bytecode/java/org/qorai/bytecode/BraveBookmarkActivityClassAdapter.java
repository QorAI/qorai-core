/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkActivityClassAdapter extends QoraiClassVisitor {
    static String sBookmarkActivityClassName =
            "org/chromium/chrome/browser/app/bookmarks/BookmarkActivity";
    static String sQoraiBookmarkActivityClassName =
            "org/chromium/chrome/browser/app/bookmarks/QoraiBookmarkActivity";

    public QoraiBookmarkActivityClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiBookmarkActivityClassName, "mBookmarkManagerCoordinator");
        makeProtectedField(sBookmarkActivityClassName, "mBookmarkManagerCoordinator");
    }
}
