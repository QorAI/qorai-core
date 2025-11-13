/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiFullscreenVideoPictureInPictureControllerClassAdapter extends QoraiClassVisitor {
    static String sFullscreenVideoPictureInPictureController =
            "org/chromium/chrome/browser/media/FullscreenVideoPictureInPictureController";
    static String sQoraiFullscreenVideoPictureInPictureController =
            "org/chromium/chrome/browser/media/QoraiFullscreenVideoPictureInPictureController";

    public QoraiFullscreenVideoPictureInPictureControllerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(
                sFullscreenVideoPictureInPictureController,
                sQoraiFullscreenVideoPictureInPictureController);
        deleteField(sFullscreenVideoPictureInPictureController, "mDismissPending");
        changeMethodOwner(
                sFullscreenVideoPictureInPictureController,
                "dismissActivityIfNeeded",
                sQoraiFullscreenVideoPictureInPictureController);
    }
}
