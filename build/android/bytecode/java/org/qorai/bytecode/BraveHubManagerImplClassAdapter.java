/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiHubManagerImplClassAdapter extends QoraiClassVisitor {
    static String sHubManagerImplClassName = "org/chromium/chrome/browser/hub/HubManagerImpl";
    static String sQoraiHubManagerImplClassName =
            "org/chromium/chrome/browser/hub/QoraiHubManagerImpl";

    public QoraiHubManagerImplClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(sHubManagerImplClassName, sQoraiHubManagerImplClassName);
    }
}
