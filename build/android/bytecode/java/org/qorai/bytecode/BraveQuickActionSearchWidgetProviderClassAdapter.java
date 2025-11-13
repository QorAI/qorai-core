/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiQuickActionSearchWidgetProviderClassAdapter extends QoraiClassVisitor {
    static String sQuickActionSearchWidgetProviderClassName =
            "org/chromium/chrome/browser/quickactionsearchwidget/QuickActionSearchWidgetProvider";
    static String sQoraiQuickActionSearchWidgetProviderClassName =
            "org/chromium/chrome/browser/quickactionsearchwidget/QoraiQuickActionSearchWidgetProvider"; // presubmit: ignore-long-line

    public QoraiQuickActionSearchWidgetProviderClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(
                sQuickActionSearchWidgetProviderClassName,
                "setWidgetEnabled",
                sQoraiQuickActionSearchWidgetProviderClassName);
    }
}
