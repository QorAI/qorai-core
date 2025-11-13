/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiFullscreenHtmlApiHandlerLegacyClassAdapter extends QoraiClassVisitor {
    static String sFullscreenHtmlApiHandlerLegacy =
            "org/chromium/chrome/browser/fullscreen/FullscreenHtmlApiHandlerLegacy";
    static String sQoraiFullscreenHtmlApiHandlerLegacy =
            "org/chromium/chrome/browser/fullscreen/QoraiFullscreenHtmlApiHandlerLegacy";

    public QoraiFullscreenHtmlApiHandlerLegacyClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sFullscreenHtmlApiHandlerLegacy, sQoraiFullscreenHtmlApiHandlerLegacy);
    }
}
