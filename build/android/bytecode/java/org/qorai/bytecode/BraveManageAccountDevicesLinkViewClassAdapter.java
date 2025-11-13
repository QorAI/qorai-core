/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiManageAccountDevicesLinkViewClassAdapter extends QoraiClassVisitor {
    static String sManageAccountDevicesLinkView =
            "org/chromium/chrome/browser/share/send_tab_to_self/ManageAccountDevicesLinkView";
    static String sQoraiManageAccountDevicesLinkView =
            "org/chromium/chrome/browser/share/send_tab_to_self/QoraiManageAccountDevicesLinkView";

    public QoraiManageAccountDevicesLinkViewClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sManageAccountDevicesLinkView, sQoraiManageAccountDevicesLinkView);

        changeMethodOwner(
                sManageAccountDevicesLinkView,
                "getSharingAccountInfo",
                sQoraiManageAccountDevicesLinkView);
    }
}
