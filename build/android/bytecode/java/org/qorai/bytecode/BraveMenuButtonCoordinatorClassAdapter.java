/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMenuButtonCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sMenuButtonCoordinator =
            "org/chromium/chrome/browser/toolbar/menu_button/MenuButtonCoordinator";
    static String sQoraiMenuButtonCoordinator =
            "org/chromium/chrome/browser/toolbar/menu_button/QoraiMenuButtonCoordinator";

    public QoraiMenuButtonCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sMenuButtonCoordinator, sQoraiMenuButtonCoordinator);
    }
}
