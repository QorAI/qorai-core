/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiUndoBarControllerBaseClassAdapter extends QoraiClassVisitor {
    static String sUndoBarController =
            "org/chromium/chrome/browser/undo_tab_close_snackbar/UndoBarController";
    static String sQoraiUndoBarControllerBase =
            "org/chromium/chrome/browser/undo_tab_close_snackbar/QoraiUndoBarControllerBase";

    public QoraiUndoBarControllerBaseClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sUndoBarController, sQoraiUndoBarControllerBase);

        changeMethodOwner(sUndoBarController, "showUndoBar", sQoraiUndoBarControllerBase);
    }
}
