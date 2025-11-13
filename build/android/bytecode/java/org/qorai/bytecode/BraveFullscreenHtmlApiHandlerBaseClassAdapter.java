/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiFullscreenHtmlApiHandlerBaseClassAdapter extends QoraiClassVisitor {
    static String sFullscreenHtmlApiHandlerBase =
            "org/chromium/chrome/browser/fullscreen/FullscreenHtmlApiHandlerBase";
    static String sQoraiFullscreenHtmlApiHandlerBase =
            "org/chromium/chrome/browser/fullscreen/QoraiFullscreenHtmlApiHandlerBase";

    public QoraiFullscreenHtmlApiHandlerBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sFullscreenHtmlApiHandlerBase, sQoraiFullscreenHtmlApiHandlerBase);
    }
}
