/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkManagerMediatorClassAdapter extends QoraiClassVisitor {
    static String sBookmarkManagerMediatorClassName =
            "org/chromium/chrome/browser/bookmarks/BookmarkManagerMediator";
    static String sQoraiBookmarkManagerMediatorClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkManagerMediator";

    public QoraiBookmarkManagerMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sBookmarkManagerMediatorClassName, sQoraiBookmarkManagerMediatorClassName);

        deleteField(sQoraiBookmarkManagerMediatorClassName, "mBookmarkModel");
        makeProtectedField(sBookmarkManagerMediatorClassName, "mBookmarkModel");
        deleteField(sQoraiBookmarkManagerMediatorClassName, "mContext");
        makeProtectedField(sBookmarkManagerMediatorClassName, "mContext");
    }
}
