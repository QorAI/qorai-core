/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiFeedSurfaceMediatorClassAdapter extends QoraiClassVisitor {
    static String sFeedSurfaceMediatorClassName =
            "org/chromium/chrome/browser/feed/FeedSurfaceMediator";
    static String sQoraiFeedSurfaceMediatorClassName =
            "org/chromium/chrome/browser/feed/QoraiFeedSurfaceMediator";

    public QoraiFeedSurfaceMediatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sFeedSurfaceMediatorClassName, sQoraiFeedSurfaceMediatorClassName);

        deleteField(sQoraiFeedSurfaceMediatorClassName, "mCoordinator");
        makeProtectedField(sFeedSurfaceMediatorClassName, "mCoordinator");

        deleteField(sQoraiFeedSurfaceMediatorClassName, "mSnapScrollHelper");
        makeProtectedField(sFeedSurfaceMediatorClassName, "mSnapScrollHelper");
    }
}
