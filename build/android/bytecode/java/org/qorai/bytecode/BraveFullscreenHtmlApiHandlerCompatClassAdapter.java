/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiFullscreenHtmlApiHandlerCompatClassAdapter extends QoraiClassVisitor {
    static String sFullscreenHtmlApiHandlerCompat =
            "org/chromium/chrome/browser/fullscreen/FullscreenHtmlApiHandlerCompat";
    static String sQoraiFullscreenHtmlApiHandlerCompat =
            "org/chromium/chrome/browser/fullscreen/QoraiFullscreenHtmlApiHandlerCompat";

    public QoraiFullscreenHtmlApiHandlerCompatClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sFullscreenHtmlApiHandlerCompat, sQoraiFullscreenHtmlApiHandlerCompat);
    }
}
