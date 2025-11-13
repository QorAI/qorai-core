/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiMimeUtilsClassAdapter extends QoraiClassVisitor {
    static String sMimeUtilsClassName = "org/chromium/chrome/browser/download/MimeUtils";

    static String sQoraiMimeUtilsClassName = "org/chromium/chrome/browser/download/QoraiMimeUtils";

    public QoraiMimeUtilsClassAdapter(ClassVisitor visitor) {
        super(visitor);
        changeMethodOwner(sMimeUtilsClassName, "canAutoOpenMimeType", sQoraiMimeUtilsClassName);
    }
}
