/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiHelpAndFeedbackLauncherImplClassAdapter extends QoraiClassVisitor {
    static String sHelpAndFeedbackLauncherImplClassName =
            "org/chromium/chrome/browser/feedback/HelpAndFeedbackLauncherImpl";

    static String sQoraiHelpAndFeedbackLauncherImplClassName =
            "org/chromium/chrome/browser/feedback/QoraiHelpAndFeedbackLauncherImpl";

    public QoraiHelpAndFeedbackLauncherImplClassAdapter(ClassVisitor visitor) {
        super(visitor);

        redirectConstructor(
                sHelpAndFeedbackLauncherImplClassName, sQoraiHelpAndFeedbackLauncherImplClassName);
    }
}
