/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiPictureInPictureActivityClassAdapter extends QoraiClassVisitor {
    static String sPictureInPictureActivityClassName =
            "org/chromium/chrome/browser/media/PictureInPictureActivity";
    static String sQoraiPictureInPictureActivityClassName =
            "org/chromium/chrome/browser/media/QoraiPictureInPictureActivity";

    public QoraiPictureInPictureActivityClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(
                sPictureInPictureActivityClassName, sQoraiPictureInPictureActivityClassName);
    }
}
