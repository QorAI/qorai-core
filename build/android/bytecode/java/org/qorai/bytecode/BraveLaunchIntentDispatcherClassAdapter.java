/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiLaunchIntentDispatcherClassAdapter extends QoraiClassVisitor {
    static String sLaunchIntentDispatcherClassName = "org/chromium/chrome/browser/LaunchIntentDispatcher";
    static String sQoraiLaunchIntentDispatcherClassName = "org/chromium/chrome/browser/QoraiLaunchIntentDispatcher";

    public QoraiLaunchIntentDispatcherClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(sLaunchIntentDispatcherClassName, "isCustomTabIntent", sQoraiLaunchIntentDispatcherClassName);
    }
}
