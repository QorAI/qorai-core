/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.qorai.bytecode;

import org.objectweb.asm.ClassVisitor;

public class QoraiSearchEnginePreferenceClassAdapter extends QoraiClassVisitor {
    static String sSearchEngineSettingsClassName =
            "org/chromium/chrome/browser/search_engines/settings/SearchEngineSettings";

    static String sQoraiSearchEnginePreferenceClassName =
            "org/chromium/chrome/browser/search_engines/settings/QoraiSearchEnginePreference";

    public QoraiSearchEnginePreferenceClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteField(sQoraiSearchEnginePreferenceClassName, "mSearchEngineAdapter");
        makeProtectedField(sSearchEngineSettingsClassName, "mSearchEngineAdapter");

        deleteField(sQoraiSearchEnginePreferenceClassName, "mProfile");
        makeProtectedField(sSearchEngineSettingsClassName, "mProfile");

        makePublicMethod(sSearchEngineSettingsClassName, "createAdapterIfNecessary");
        addMethodAnnotation(sQoraiSearchEnginePreferenceClassName, "createAdapterIfNecessary",
                "Ljava/lang/Override;");
    }
}
