/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiDownloadMessageUiControllerImplClassAdapter extends QoraiClassVisitor {
    static String sDownloadMessageUiControllerImpl =
            "org/chromium/chrome/browser/download/DownloadMessageUiControllerImpl";

    static String sQoraiDownloadMessageUiControllerImpl =
            "org/chromium/chrome/browser/download/QoraiDownloadMessageUiControllerImpl";

    public QoraiDownloadMessageUiControllerImplClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sDownloadMessageUiControllerImpl, sQoraiDownloadMessageUiControllerImpl);
        changeMethodOwner(sDownloadMessageUiControllerImpl, "isVisibleToUser",
                sQoraiDownloadMessageUiControllerImpl);
    }
}
