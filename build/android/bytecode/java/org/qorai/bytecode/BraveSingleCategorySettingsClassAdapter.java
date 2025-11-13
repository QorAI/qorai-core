/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSingleCategorySettingsClassAdapter extends QoraiClassVisitor {
    static String sSingleCategorySettingsClassName =
            "org/chromium/components/browser_ui/site_settings/SingleCategorySettings";
    static String sQoraiSingleCategorySettingsClassName =
            "org/chromium/components/browser_ui/site_settings/QoraiSingleCategorySettings";

    public QoraiSingleCategorySettingsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        changeSuperName(sSingleCategorySettingsClassName, sQoraiSingleCategorySettingsClassName);
        changeMethodOwner(
                sSingleCategorySettingsClassName,
                "onOptionsItemSelected",
                sQoraiSingleCategorySettingsClassName);
        changeMethodOwner(
                sSingleCategorySettingsClassName,
                "getAddExceptionDialogMessageResourceId",
                sQoraiSingleCategorySettingsClassName);
        changeMethodOwner(
                sSingleCategorySettingsClassName,
                "resetList",
                sQoraiSingleCategorySettingsClassName);
    }
}
