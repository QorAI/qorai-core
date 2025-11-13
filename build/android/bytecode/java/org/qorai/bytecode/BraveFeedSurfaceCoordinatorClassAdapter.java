/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiFeedSurfaceCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sFeedSurfaceCoordinatorClassName =
            "org/chromium/chrome/browser/feed/FeedSurfaceCoordinator";
    static String sQoraiFeedSurfaceCoordinatorClassName =
            "org/chromium/chrome/browser/feed/QoraiFeedSurfaceCoordinator";

    public QoraiFeedSurfaceCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiFeedSurfaceCoordinatorClassName, "mNtpHeader");
        makeProtectedField(sFeedSurfaceCoordinatorClassName, "mNtpHeader");

        deleteField(sQoraiFeedSurfaceCoordinatorClassName, "mRootView");
        makeProtectedField(sFeedSurfaceCoordinatorClassName, "mRootView");
    }
}
