/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiWebsiteClassAdapter extends QoraiClassVisitor {
    static String sWebsiteClassName = "org/chromium/components/browser_ui/site_settings/Website";
    static String sQoraiWebsiteClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiWebsite";

    public QoraiWebsiteClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sWebsiteClassName, sQoraiWebsiteClassName);

        makePrivateMethod(sWebsiteClassName, "setContentSetting");

        makePublicMethod(sQoraiWebsiteClassName, "setContentSetting");
        changeMethodOwner(sWebsiteClassName, "setContentSetting", sQoraiWebsiteClassName);
    }
}
