/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSearchBarCoordinatorClassAdapter extends QoraiClassVisitor {
    static String sSearchBarCoordinatorClassName =
            "org/chromium/chrome/browser/download/home/search/SearchBarCoordinator";
    static String sQoraiSearchBarCoordinatorClassName =
            "org/chromium/chrome/browser/download/home/search/QoraiSearchBarCoordinator";

    public QoraiSearchBarCoordinatorClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sSearchBarCoordinatorClassName, sQoraiSearchBarCoordinatorClassName);
    }
}
