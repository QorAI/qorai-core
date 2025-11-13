/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMediaSessionHelperClassAdapter extends QoraiClassVisitor {
    static String sMediaSessionHelperClassName =
            "org/chromium/components/browser_ui/media/MediaSessionHelper";

    static String sQoraiMediaSessionHelperClassName =
            "org/chromium/components/browser_ui/media/QoraiMediaSessionHelper";

    public QoraiMediaSessionHelperClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sMediaSessionHelperClassName, sQoraiMediaSessionHelperClassName);

        changeMethodOwner(
                sMediaSessionHelperClassName,
                "showNotification",
                sQoraiMediaSessionHelperClassName);
        changeMethodOwner(
                sMediaSessionHelperClassName,
                "createMediaSessionObserver",
                sQoraiMediaSessionHelperClassName);
    }
}
