/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiChromeContextMenuPopulatorAdapter extends QoraiClassVisitor {
    static String sController =
            "org/chromium/chrome/browser/contextmenu/ChromeContextMenuPopulator";
    static String sQoraiController =
            "org/chromium/chrome/browser/contextmenu/QoraiChromeContextMenuPopulator";

    public QoraiChromeContextMenuPopulatorAdapter(ClassVisitor visitor) {
        super(visitor);
        redirectConstructor(sController, sQoraiController);

        deleteMethod(sQoraiController, "getProfile");
        makePublicMethod(sController, "getProfile");

        deleteField(sQoraiController, "mItemDelegate");
        makeProtectedField(sController, "mItemDelegate");

        deleteField(sQoraiController, "mParams");
        makeProtectedField(sController, "mParams");
    }
}
