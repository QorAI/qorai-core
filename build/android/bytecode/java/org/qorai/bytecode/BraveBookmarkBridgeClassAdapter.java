/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiBookmarkBridgeClassAdapter extends QoraiClassVisitor {
    static String sBookmarkBridgeClassName = "org/chromium/chrome/browser/bookmarks/BookmarkBridge";
    static String sQoraiBookmarkBridgeClassName =
            "org/chromium/chrome/browser/bookmarks/QoraiBookmarkBridge";

    public QoraiBookmarkBridgeClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sBookmarkBridgeClassName, sQoraiBookmarkBridgeClassName);
        deleteField(sQoraiBookmarkBridgeClassName, "mNativeBookmarkBridge");
        makeProtectedField(sBookmarkBridgeClassName, "mNativeBookmarkBridge");
    }
}
