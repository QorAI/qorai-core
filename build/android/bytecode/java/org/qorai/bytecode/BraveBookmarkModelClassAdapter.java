/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkModelClassAdapter extends QoraiClassVisitor {
    static String sQoraiBookmarkBridgeClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkBridge";
    static String sBookmarkModelClassName = "org/chromium/chrome/browser/bookmarks/BookmarkModel";
    static String sQoraiBookmarkModelClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkModel";

    public QoraiBookmarkModelClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sBookmarkModelClassName, sQoraiBookmarkBridgeClassName);
        redirectConstructor(sBookmarkModelClassName, sQoraiBookmarkModelClassName);
        deleteMethod(sQoraiBookmarkModelClassName, "importBookmarks");
        deleteMethod(sQoraiBookmarkModelClassName, "exportBookmarks");
    }
}
