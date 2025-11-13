/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiNotificationManagerProxyImplClassAdapter extends QoraiClassVisitor {
    static String sNotificationManagerProxyImplClassName =
            "org/chromium/components/browser_ui/notifications/NotificationManagerProxyImpl";
    static String sQoraiNotificationManagerProxyImplClassName =
            "org/chromium/chrome/browser/notifications/QoraiNotificationManagerProxyImpl";

    public QoraiNotificationManagerProxyImplClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sNotificationManagerProxyImplClassName,
                sQoraiNotificationManagerProxyImplClassName);
    }
}
