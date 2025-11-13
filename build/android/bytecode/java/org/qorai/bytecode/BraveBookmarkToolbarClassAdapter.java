/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkToolbarClassAdapter extends QoraiClassVisitor {
    static String sBookmarkToolbarClassName =
            "org/chromium/chrome/browser/bookmarks/BookmarkToolbar";
    static String sQoraiBookmarkToolbarClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkToolbar";

    public QoraiBookmarkToolbarClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sBookmarkToolbarClassName, sQoraiBookmarkToolbarClassName);
        deleteField(sQoraiBookmarkToolbarClassName, "mBookmarkModel");
        makeProtectedField(sBookmarkToolbarClassName, "mBookmarkModel");
    }
}
