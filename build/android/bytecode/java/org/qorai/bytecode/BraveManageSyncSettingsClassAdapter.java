/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

/**
 * Adapter, used to make some fields from upstream's ManageSyncSettings be public
 */
public class QoraiManageSyncSettingsClassAdapter extends QoraiClassVisitor {
    static String sManageSyncSettingsClassName =
            "org/chromium/chrome/browser/sync/settings/ManageSyncSettings";
    static String sQoraiManageSyncSettingsClassName =
            "org/chromium/chrome/browser/sync/settings/QoraiManageSyncSettings";

    QoraiManageSyncSettingsClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiManageSyncSettingsClassName, "mGoogleActivityControls");
        makeProtectedField(sManageSyncSettingsClassName, "mGoogleActivityControls");

        deleteField(sQoraiManageSyncSettingsClassName, "mSyncEncryption");
        makeProtectedField(sManageSyncSettingsClassName, "mSyncEncryption");

        deleteField(sQoraiManageSyncSettingsClassName, "mSyncEverything");
        makeProtectedField(sManageSyncSettingsClassName, "mSyncEverything");
    }
}
